#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bitwriter.h"
#include "bitreader.h"
#include "node.h"
#include "pq.h"

typedef struct Code {
uint64_t code;
uint8_t code_length;
} Code;

uint32_t fill_histogram(FILE *fin, uint32_t *histogram){
    if (fin == NULL || histogram == NULL) {
        fprintf(stderr, "Error: Invalid input parameters in fill_histogram.\n");
        return 0;
    }

    // Clear all elements of the histogram array
    for (int i = 0; i < 256; ++i) {
        histogram[i] = 0;
    }

    // Read bytes from the input file and update the histogram
    uint32_t filesize = 0;
    int byte;
    while ((byte = fgetc(fin)) != EOF) {
        ++histogram[byte];
        ++filesize;
    }

    ++histogram[0x00];
    ++histogram[0xff];

    return filesize;
}

Node *create_tree(uint32_t *histogram, uint16_t *num_leaves){
    if (histogram == NULL || num_leaves == NULL) {
        fprintf(stderr, "Error: Invalid input parameters in create_tree.\n");
        return NULL;
    }

    // Create and fill a Priority Queue
    PriorityQueue *pq = pq_create();
    for (int i = 0; i < 256; ++i) {
        if (histogram[i] > 0) {
            Node *newNode = node_create((uint8_t)i, histogram[i]);
            enqueue(pq, newNode);
            (*num_leaves)++;
        }
    }

    // Run the Huffman Coding algorithm
    while (pq_size_is_1(pq) == 0) {
        Node *left = dequeue(pq);
        Node *right = dequeue(pq);

        // Create a new node with symbol = 0 and weight = left->weight + right->weight
        Node *newNode = node_create(0, left->weight + right->weight);
        newNode->left = left;
        newNode->right = right;

        // Enqueue the new node
        enqueue(pq, newNode);
    }

    // Dequeue the queue’s only entry and return it
    Node *root = dequeue(pq);

    // Free the Priority Queue
    pq_free(&pq);

    return root;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length){
    // Check if node or code_table is NULL
    if (node == NULL || code_table == NULL) {
        fprintf(stderr, "Error: Invalid input parameters in fill_code_table.\n");
        return;
    }

    if (node->left != NULL || node->right != NULL) {
        // Internal node: Recursive calls left and right
        // Append a 0 to code and recurse (don't need to append a 0; it's already there)
        fill_code_table(code_table, node->left, code, code_length + 1);

        // Append a 1 to code and recurse
        code |= (uint64_t)1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    } else {
        // Leaf node: Store the Huffman Code
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left == NULL) {
        // Leaf node
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    } else {
        // Internal node
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    }
}

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize, uint16_t num_leaves, Node *code_tree, Code *code_table){
    // Write the Huffman file header
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);

    // Write the Huffman tree
    huff_write_tree(outbuf, code_tree);

    // Rewind the input file
    fseek(fin, 0, SEEK_SET);

    // Compress the input file using Huffman codes
    int b;
    while (1) {
        b = fgetc(fin);
        if (b == EOF) {
            break;
        }

        // Get Huffman code and code length from code_table
        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;

        // Write bits to output buffer
        for (int i = 0; i < code_length; ++i) {
            bit_write_bit(outbuf, code & 1);
            code >>= 1;
        }
    }
}

int main(int argc, char *argv[]){
    char *infile = NULL;
    char *outfile = NULL;
    int opt;

    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch (opt) {
            case 'i':
                infile = optarg;
                break;
            case 'o':
                outfile = optarg;
                break;
            case '?':
                fprintf(stderr, "Usage: %s -i infile -o outfile\n", argv[0]);
                exit(EXIT_FAILURE);
            default:
                fprintf(stderr, "Unknown option: %c\n", optopt);
                exit(EXIT_FAILURE);
        }
    }

    // Check if required options are provided
    if (infile == NULL || outfile == NULL) {
        fprintf(stderr, "Usage: %s -i infile -o outfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    //BitReader *br = bit_read_open(infile);
    //br->underlying_stream is the FILE
    BitWriter *bw = bit_write_open(outfile);

    FILE *fin = fopen(infile, "rb");
        if (fin == NULL) {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }
 
    uint32_t histogram[256];
    uint16_t num_leaves = 0;
    uint32_t filesize = fill_histogram(fin, histogram);
    Node *code_tree = create_tree(histogram, &num_leaves);

    // Create and fill the code table
    Code code_table[256];
    fill_code_table(code_table, code_tree, 0, 0);

    // Compress the input file using Huffman codes
    huff_compress_file(bw, fin, filesize, num_leaves, code_tree, code_table);

    // Close the files and free memory
    fclose(fin);
    bit_write_close(&bw);
    node_free(&code_tree);

    return 0;
}

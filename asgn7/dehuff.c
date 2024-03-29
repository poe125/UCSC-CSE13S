#include "bitwriter.h"
#include "bitreader.h"
#include "node.h"
#include "pq.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>

typedef struct stack{
    Node *stack[64]; //this is a node pointer
    int top;
} Stack;

Stack * stack_create(int top_num) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = top_num;
    return s;
}

void stack_free(Stack **sp) {
    if (sp != NULL && *sp != NULL) {
        for(int i = 0; i <= (*sp)->top; i++) {
            node_free(&((*sp)->stack[i]));
        }
        free(*sp);
        *sp = NULL;
    }
}

bool stack_push(Stack *s, Node *n) {
    if (s->top == 63) {
        // Stack is full
        // printf("stack is full\n");
        return false;
    }
    s->stack[++s->top] = n;
    return true;
}

Node *stack_pop(Stack *s) {
    if (s->top == -1) {
        // Stack is empty
        //printf("stack pop: this is empty\n");
        return NULL;
    }
    //printf("this is not empty stack pop\n");
    return s->stack[s->top--];
}

bool stack_empty(Stack *s) {
    return s->top == -1;
}

bool stack_full(Stack *s) {
    return s->top == 63;
}

void dehuff_decompress_file(FILE *fout, BitReader *inbuf){
    uint8_t type1 = bit_read_uint8(inbuf);
    uint8_t type2 = bit_read_uint8(inbuf);
    uint32_t filesize = bit_read_uint32(inbuf);
    uint16_t num_leaves = bit_read_uint16(inbuf);

    assert(type1 == 'H');
    assert(type2 == 'C');
    uint8_t num_nodes = 2 * (uint8_t)num_leaves - 1;
    Stack *s = stack_create(-1);
    Node *n;
    for (int i = 0; i < num_nodes; i++) {
        uint8_t bit = bit_read_bit(inbuf);
   //      printf("inside num_nodes %d\n", i);
        if (bit == 1) {
            // printf("is bit 1\n");
            uint8_t symbol = bit_read_uint8(inbuf);
            //create a new node; top++
            n = node_create(symbol, 0);
        } else {
            // printf("is bit 0\n");
            //new node; top++
            n = node_create(0, 0);
            // printf("popping into right node\n");
            n->right = stack_pop(s);
            // printf("popping into left node\n");
            n->left = stack_pop(s);
        }
        stack_push(s, n);
    }
   // printf("before Node *code_tree\n");
    Node *code_tree;
    code_tree = stack_pop(s);
    // s->top--;
    for (int i = 0; i < (int)filesize; i++) {
        // printf("before node = code_tree\n");
        n = code_tree;
        while (1) {
            // printf("inside while loop\n");
            uint8_t bit = bit_read_bit(inbuf);
            // printf("bit read: %d\n", bit);
            if (bit == 0) {
                if (n->left == NULL) {
                    // printf("Error: NULL left node\n");
                    break;
                }
                // printf("left node\n");
                n = n->left;
            } else {
                if (n->right == NULL) {
                //     printf("Error: NULL right node\n");
                    break;
                }
                // printf("right node\n");
                n = n->right;
            }
            if (n->left == NULL && n->right == NULL) {
                // Leaf node
                // printf("leaf node\n");
                // printf("fout\n");
                fprintf(fout, "%c", n->symbol);
                // printf("fout\n");
                break;
            }
            // printf("inside while\n");
        }
//        printf("outside of loop\n");
    }
    // printf("outside of loop\n");
    node_free(&code_tree);
    stack_free(&s);
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

    FILE *fout = fopen(outfile, "wb");
    if (fout == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    BitReader *inbuf = bit_read_open(infile);

    dehuff_decompress_file(fout, inbuf);

    // printf("after dehuff\n");
    fclose(fout);
    bit_read_close(&inbuf);
    return 0;
}

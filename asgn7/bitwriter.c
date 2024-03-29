#include "bitwriter.h"
#include <stdio.h>
#include <stdlib.h>

struct BitWriter{
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename){
    BitWriter *bw = malloc(sizeof(BitWriter));
    if(bw == NULL){
        return NULL;
    }
    bw->underlying_stream = fopen(filename, "wb");
    if(bw->underlying_stream == NULL){
        free(bw);
        return NULL;
    }
    bw->byte = 0;
    bw->bit_position = 0;
    return bw;
}

void bit_write_close(BitWriter **pbuf){
    /*
    if *pbuf != NULL:
    if (*pbuf)->bit_position > 0:
    //(*pbuf)->byte contains at least one bit that has not yet been written 
    write the byte to the underlying_stream using fputc()
    close the underlying_stream
    free the BitWriter
    *pbuf = NULL
    */
    if (*pbuf != NULL) {
        if ((*pbuf)->bit_position > 0) {
            fputc((*pbuf)->byte, (*pbuf)->underlying_stream);
        }
        fclose((*pbuf)->underlying_stream);
        free(*pbuf);
        *pbuf = NULL;
    }    
}

void bit_write_bit(BitWriter *buf, uint8_t bit){
    /*
    if bit_position > 7:
    write the byte to the underlying_stream using fputc()
    clear the byte and bit_position fields of the BitWriter to 0
    set the bit at bit_position of the byte to the value of bit
    bit_position += 1
    */
    if (buf->bit_position > 7) {
        fputc(buf->byte, buf->underlying_stream);
        buf->byte = 0;
        buf->bit_position = 0;
    }

    buf->byte |= (bit & 1) << buf->bit_position;
    buf->bit_position++;
}

void bit_write_uint8(BitWriter *buf, uint8_t x){
//run bit_write_bit() 8 times
    for(int i=0; i<8; i++){
        bit_write_bit(buf, (x >> i) & 1);
    }
}

void bit_write_uint16(BitWriter *buf, uint16_t x){
//run bit_write_bit() 16 times
    for(int i=0; i<16; i++){
        bit_write_bit(buf, (x >> i) & 1);
    }
}

void bit_write_uint32(BitWriter *buf, uint32_t x){
//run bit_write_bit() 32 times
    for(int i=0; i<32; i++){
        bit_write_bit(buf, (x >> i) & 1);
    }
}

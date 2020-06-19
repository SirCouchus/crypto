//
//  main.c
//  cryptopals
//
//  Created by James Lambeth on 08/06/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// encoded hex string
const char hex[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
// base64 alphabet
const char base64[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'};

/*
 * 2.1. get base64 encoded size
 */
size_t base64_encoded_len(size_t byte_len)
{
    // payload increases by a third.
    size_t b64_len = 4 * (byte_len / 3);
    
    return b64_len;
}

/*
 * 2. translate each character to its base64 character
 */
char *byte_to_base64(char *bytes, size_t len){
    char *base64_encoded;
    size_t base64_len, i, j, value;
    
    base64_len = base64_encoded_len(len); // get size needed for base64 encoded string
    base64_encoded = malloc(base64_len+1); // allocate memory for base64 encoded string
    
    /*
     * the process here is:
     * - take each byte and add it to value, shifting each character
     * - break each byte down into 6 bits, and add it to base64_encoded string
     * - use '& 0x3F' to correctly switch bits since it is 6 bits of all 1s
     * - pad if necessary
     */
    for (i=0, j=0; i<len; i+=3, j+=4) {
        value = bytes[i];
        if(i+1 < len){
            // BITWISE OR; 1 if either bit is 1, 0 when both bits are zero
            value = value << 8 | bytes[i+1];
        } else {
            value = value << 8;
        }
        if(i+2 < len){
            value = value << 8 | bytes[i+2];
        } else {
            value = value << 8;
        }
        
        // update base64_encoded using base64 alphabet
        base64_encoded[j] = base64[(value >> 18) & 0x3F]; // BITWISE AND; each b64 block is 6 bits; 0x3F = 111111
        base64_encoded[j+1] = base64[(value >> 12) & 0x3F];
        if (i+1 < len) {
            base64_encoded[j+2] = base64[(value >> 6) & 0x3F];
        } else {
            base64_encoded[j+2] = '='; // pad if necessary
        }
        if (i+2 < len) {
            base64_encoded[j+3] = base64[value & 0x3F];
        } else {
            base64_encoded[j+3] = '=';
        }
    }
    
    printf("BASE64 ENCODED:\t%s\n", base64_encoded);
    return base64_encoded;
}

/*
 * 1. decode hex string
 */
void decode_hex_string(){
    const char *hex_pointer = hex;
    char hex_to_byte[strlen(hex)/2]; // 2 hex digits per byte
    
    for(unsigned i = 0; i < sizeof(hex_to_byte); i++){
        sscanf(hex_pointer, "%02hhx", &hex_to_byte[i]); //decode data from hex and insert it into hex_to_byte
        hex_pointer += 2;
    }
    printf("DECODED HEX:\t%s\n", hex_to_byte);
    byte_to_base64(hex_to_byte, sizeof hex_to_byte);
}

/*
 * 0. initiate
 */
int main(int argc, const char * argv[]) {
    decode_hex_string();
    return 0;
}

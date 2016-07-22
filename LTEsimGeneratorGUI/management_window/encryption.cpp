#include "management_window/encryption.h"

const char* crypt(const char* plaintext,int text_len,const char* key,int key_len,bool terminatingZero){
    int i, key_pos = 0;
    char* result = new char[text_len + (terminatingZero==1)];

    for(i=0; i<text_len; i++) {
        result[i] = plaintext[i] ^ key[key_pos];
        key_pos = ( key_pos + 1 ) % key_len;
    }

    if(terminatingZero) {
        result[i] = '\0';
    }

    return result;
}

//
//  main.cpp
//  xxtea_console
//
//  Created by xedi on 4/18/18.

#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include "xxtea.h"
#include "base64.h"

int main(int argc, const char * argv[]) {
    if (argc < 4) {
        printf("usage : xxtea target_text key mode\n");
        printf("mode : enc or dec\n");
        printf("key max length is 16 chars\n");
        printf("example encrypt: \n");
        printf("    xxtea_console.exe text_to_encypt 123 enc\n");
        printf("example decrypt: \n");
        printf("    xxtea_console.exe encrypted_text 123 dec\n");
        return 0;
    }
    const char *text = argv[1];
    const char *key =  argv[2];
    const char *mode = argv[3];
    size_t len;
    
    if (strcmp(mode, "enc")==0)
    {
        unsigned char *encrypt_data = (unsigned char*)xxtea_encrypt((void*)text, strlen(text), (void*)key, &len);
        char * base64_data = base64_encode(encrypt_data, len);
        printf("Encrypted text : %s\n", base64_data);
        
        free(encrypt_data);
        free(base64_data);
    }
    else
    {
        len = strlen(text);
        unsigned char * base64_data = base64_decode(text, &len);
        char *decrypt_data = (char*)xxtea_decrypt(base64_data, len, key, &len);
        if (decrypt_data!=nullptr)
        {
            printf("Decrypted text: %s\n", decrypt_data);
        }
        else
        {
            printf("Decrypt fail!\n");
        }
        free(decrypt_data);
    }
    
    return 0;
    return 0;
}

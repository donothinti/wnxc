#ifndef YXW_BASE64_H
#define YXW_BASE64_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

int base64_encode(char *in_str, int in_len, char *out_str);
int base64_decode(char *in_str, int in_len, char *out_str);

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zlib.h>
#include "yxw_base64.h"
//#include "yxw_gzip.h"
#define Ifile "1.txt"
#define Ofile "2.txt"
#define Tfile ""
#define DBG_LEVEL 10
#define DBGEX(level, ...) do {if (DBG_LEVEL >= level) {printf("[I]");printf("\033[34m");printf(__VA_ARGS__);printf("\033[0m");}}while(0);                                
#define DBG(...) do {if (DBG_LEVEL >= 1) {printf("[I][%s:%d]", __func__, __LINE__);printf("\033[34m");printf(__VA_ARGS__);printf("\033[0m");}}while(0);
#define DBG_ERR(...) do {if (DBG_LEVEL >= 1) {printf("[E][%s:%d]", __func__, __LINE__);printf("\033[31m");printf(__VA_ARGS__);printf("\033[0m");}}while(0);
#define DBG_WARN(...) do { if (DBG_LEVEL >= 1) {printf("[W][%s:%d]", __func__, __LINE__);printf("\033[33m");printf(__VA_ARGS__);printf("\033[0m");}}while(0);

int main(void)
{
	int file_len;
	char* file_content;
	FILE* fp;
//	{
		if(( fp = fopen( Ifile,"r")) == NULL)
			return -1;

		fseek(fp, 0L, SEEK_END);
		file_len = ftell(fp);

		fseek(fp, 0L, SEEK_SET);
		file_content = malloc(file_len);

		if(file_len != fread(file_content, 1, file_len, fp))
			printf("%d:%s", file_len, file_content);
		fclose(fp);
//	}
//	{
		int len = ((file_len - 1)/3 + 1) * 4 + 1;
		char* base_en = malloc(len);
		base64_encode(file_content, file_len, base_en);

		printf("%s\n",base_en);

		char* base_de = malloc(file_len);
		base64_decode(base_en, len, base_de);

		printf("base:%s\n", base_de);
		return -1;
//	}
	{
		int len = 0;
		int res = 0;
		uLong srcLen = file_len + 1;
		uLong destLen = compressBound(srcLen);
		char* ostream = malloc(destLen);

		res = compress(ostream, &destLen, file_content, file_len);

		if(res == Z_BUF_ERROR)
		{
			printf("Buffer was too small!\n");
			return -1;
		}

		if(res == Z_MEM_ERROR)
		{
			printf("Not enough memory for compression!\n");
			return -1;
		}
		
		len = ((destLen - 1)/3 + 1) * 4 + 1;

		char* base_en = malloc(len);
		base64_encode(ostream, destLen, base_en);

		char* base_de = malloc(destLen);
		base64_decode(base_en, len, base_de);

		printf("base:%s\n", base_de);

		char* o2stream = malloc(srcLen);
		uncompress(o2stream, &srcLen, base_de, destLen);

		if((fp = fopen(Ofile,"wb")) == NULL)
			return -1;

		fwrite(o2stream, 1, srcLen, fp);

		free(ostream);
		free(base_en);
		free(base_de);
		free(o2stream);
		free(fp);
	}

	free(file_content);
    return 0;
}

#include "yxw_base64.h"
int base64_encode(char *in_str, int in_len, char *out_str)
{
	BIO *b64, *bio;
	BUF_MEM *bptr = NULL;
	size_t size = 0;

	if (in_str == NULL || out_str == NULL)
		return -1;

	b64 = BIO_new(BIO_f_base64());
	bio = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bio);

	BIO_write(b64, in_str, in_len);
	BIO_flush(b64);

	BIO_get_mem_ptr(b64, &bptr);
	//        sprintf(out_str, "%d\0", bptr->data);
	memcpy(out_str, bptr->data, bptr->length);
	out_str[bptr->length] = '\0';
	size = bptr->length;

	BIO_free_all(b64);
	return size;
}

int base64_decode(char *in_str, int in_len, char *out_str)
{
	BIO *b64, *bio;
	BUF_MEM *bptr = NULL;
	int counts;
	int size = 0;

	if (in_str == NULL || out_str == NULL)
		return -1;

	printf("in_str: %s", in_str);

	b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

	bio = BIO_new_mem_buf(in_str, in_len);
	bio = BIO_push(b64, bio);

	size = BIO_read(bio, out_str, in_len);
	out_str[size] = '\0';

	printf("out_str:%s\n",out_str);

	BIO_free_all(bio);
	return size;
}

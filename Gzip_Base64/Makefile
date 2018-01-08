main:main.o yxw_base64.o
	gcc $^ -o $@ -lm -lz -lssl -lcrypto
%.o:%.c
	gcc -c $^
clean:
	rm -f *.o main

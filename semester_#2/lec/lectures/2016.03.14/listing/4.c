#include <stdio.h>
 #define BUF_SIZE 0x100
 int main(int arg, char *argv[]) {
 	char buf[BUF_SIZE];
 	int e, i;
 	FILE *f;
 	f = fopen ("proc/self/environ", "r");
 	while ((len = fread(buf, 1 ,BUD_SIZE, f))>0) {
 		for (i = 0; i < len; ++i) {
 			if (buf[i] == 0) {
 				buf[i] = 10;
 			}
 		}

 		buf [len] = 0;
 		printf("%s", buf);
 	}
 	fclose(f);
 	return 0;
 }
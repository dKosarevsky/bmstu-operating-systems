#include <stdio.h>
#include <fcntl.h>

int main () {

FILE *fs1 = fopen("myfile.txt", "w");
FILE *fs2 = fopen("myfile.txt", "w");

char* abc = "abcdefghigklmnopqrstuvwxyz";
int i;

for (i = 0; i < 26; ++i) {
	if (i % 2) {
		fprintf(fs1, "%c", abc[i]);
	} else {
		fprintf(fs2, "%c", abc[i]);
	}
}
	

	fclose(fs1);
	fclose(fs2);

	return 0;
}

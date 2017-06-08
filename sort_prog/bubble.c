#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <time.h>

#define MAX 200000

void bubble(char *name[], int right);

int main(int argc, char *argv[])
{
	
	char *word[MAX];
	char buf[20];
	int i = 0, j = 0, c;
	int flag = 0;
	FILE *fp;
	double dtime;
	int sec, msec;
	struct timeb timebf;

	if ((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Can't open %s file\n", argv[1]);
		exit(1);
	}
	

	
	while ((c = fgetc(fp)) != EOF) {
		if (flag == 1) {
			if (c == ' ' || c == '\n' || c == '\t') {
				buf[i++] = '\0';
				if ((word[j] = (char *)malloc(sizeof(char) * i)) == NULL) {
					fprintf(stderr, "Can't allocate memory!\n");
					exit(1);
				}
				strcpy(word[j++], buf);
				flag = 0;
				i = 0;
				continue;
			}
		}
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			buf[i++] = c;
			flag = 1;
		}
	}

	ftime(&timebf);
	sec = timebf.time;
	msec = timebf.millitm;

	bubble(word, j - 1);

	ftime(&timebf);
	sec = timebf.time - sec;
	msec = timebf.millitm - msec;
	msec += sec * 1000;
	dtime = (double)msec/1000;

	
	for (i = 0; i < j; i++)
		printf("%s\n", word[i]);

	printf("\n");

	printf("time  %f\n", dtime);

	fclose(fp);
	
	for (i = 0; i < j; i++)
		free(word[i]);

	return 0;
}

void bubble(char *word[], int right)
{
	int i, j;
	char *tmp;

	for (i = 0; i < right; i++) {
		for (j = right; i < j; j--) {
			if (strcasecmp(word[i], word[j]) > 0) {
				tmp = word[i];
				word[i] = word[j];
				word[j] = tmp;
			}
		}
	}

}


	

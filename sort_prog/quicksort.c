#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <time.h>

#define MAX 200000

void quicksort(char *word[], int left, int right);
void swap(char *word[], int i, int j);

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

	quicksort(word, 0, j - 1);

	ftime(&timebf);
	sec = timebf.time - sec;
	msec = timebf.millitm - msec;
	msec += sec * 1000;
	dtime = (double)msec/1000;
	
	for (i = 0; i < j; i++)
		printf("%s\n", word[i]);
	
	printf("\n");

	printf("total word %d\n", j);

	printf("time  %f\n", dtime);


	fclose(fp);
	
	for (i = 0; i < j; i++)
		free(word[i]);

	return 0;
}

void quicksort(char *word[], int left, int right)
{
    int i, j, somewhere;
	char *pivot;

    if (left < right) {
		somewhere = (right + left) / 2;
		pivot = word[somewhere];
		i = left;
		j = right;
		while (i < j) {
			while (strcasecmp(word[i], pivot) < 0)
				i++;
			while (strcasecmp(word[j], pivot) > 0)
				j--;
			if (i <= j) {
				swap(word, i, j);
				i++;
				j--;
			}
			
		}
		quicksort(word, left, j);
		quicksort(word, i, right);
	}

}

void swap(char *word[], int i, int j)
{
	char *tmp;

	tmp = word[i];
	word[i] = word[j];
	word[j] = tmp;
}


	

	

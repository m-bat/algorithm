#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int num, *p, i, j;

	srand(time(NULL));
	printf("Please input integer: ");
	scanf("%d", &num);
	p  = (int *)malloc(sizeof(int) * num);

	for (i = 0; i < num; i++) {
		p[i] = rand() % (num + 1);
		if (p[i] == 0) {
			i--;
			continue;
		}
		
		for (j = 0; j < i; j++) {
			if (p[j] == p[i]) {
				i--;
				break;
			}
		}
	}

	for(i = 0; i < num; i++)
		printf("%d ", p[i]);
	printf("\n");
	
	return 0;
}


			

	

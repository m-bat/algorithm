/*
１からnまでの自然数をnodeとする二分木の総数と構造を表示
またそのなかでAVL木の総数を調べ出力するプログラム
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int buf[MAX];

struct tnode
{
	int key, i;
	struct tnode *left;
	struct tnode *right;
};
struct tnode *root = NULL;


struct tnode *addnode(int v, struct tnode *t); 
struct tnode *addkey(int v, struct tnode *t);
void traverse(struct tnode *t);
void tree_print(struct tnode *t);
int *ramdam(int num, int *p);
void permutation(int num, int **p, int x, int total); /*順列のすべての組み合わせを配列に格納*/
int checkAVL(struct tnode *t); /*AVL木であるか探索する。*/
int max(int x, int y);

int main()
{
	int i, j, k = 0, v, num, total = 1, avlcount = 0;
	int **p;

	do {
	printf("Please input number: ");
	scanf("%d", &num);
	}while (num > 20);


	for (i = 1 ; i <= num; i++) 
		total *= i;

	if ((p = (int **)malloc(sizeof(int *) * total)) == NULL) {
		fprintf(stderr, "Can't aloocate memory\n");
		exit(1);
	}

	for (i = 0; i < total; i++)  {
		if ((p[i] = (int *)malloc(sizeof(int) * num)) == NULL) {
			fprintf(stderr, "Can't allocate memory\n");
			exit(1);
		}
	}

	for (i = 0; i < MAX; i++)
		buf[i] = 0;

	permutation(num, p, 0, total);
	
	while(k < total){
		root = NULL;
		for (j  = 0; j < num; j++) 
			root = addkey(p[k][j], root);

		for (i  = 0; i < num; i++)
			printf("%d ", p[k][i]);

		printf("\n");
		
		printf("sort : ");
		traverse(root);
		printf("\n");
		printf("structure of tree\n");

		if (checkAVL(root) != -1) {
			printf("This tree is AVL.\n\n");
			avlcount++;
		}
		 
		tree_print(root);
		printf("\n\n");
		
		free(root);
		k++;
	}

	printf("\n");
	printf("Total number of AVL: %d\n", avlcount);
	printf("Total number of  binary tree: %d\n", total);
	
	return 0;
}

int  *ramdam(int num, int *p)
{
	int i, j;
	if ((p = (int *)malloc(sizeof(int) * num)) == NULL) {
		fprintf(stderr, "Can't allocate Memory!\n");
		exit(1);
	}
	
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

	return p;
}

	
struct tnode *addnode(int v, struct tnode *t)
{
	if (t == NULL)
		{
			if ((t = (struct tnode *)malloc(sizeof(struct tnode))) == NULL) {
				fprintf(stderr, "Can't malloc Memory!\n");
				exit(1);
			}
			
			t -> key = v;
			t -> left = NULL;
			t -> right = NULL;

		}
	return t;
}

struct tnode *addkey(int v, struct tnode *t)
{
	if (t == NULL) 
		t = addnode(v, t);

	else {
		if (t -> key > v)
			t->left = addkey(v, t->left);
		else
			t->right = addkey(v, t->right);
	}
	
	return t;
}

void traverse(struct tnode *t)
{
	if (t != NULL)
		{
			traverse(t->left);
			printf("%d ", t->key);
			traverse(t->right);
		}
}

void tree_print(struct tnode *t)
{
    static int  height = 0;

    if(t->right != NULL){
        ++height;
        tree_print(t->right);
        --height;
    }
    printf("%*c%d\n", 5 * height, ' ', t->key);
    if(t->left != NULL){
        ++height;
        tree_print(t->left);
        --height;
    }
}

	
void permutation(int num, int **p, int x, int total)
{
	static int g = 0;
	int i, j;

	if (x > num - 1) {
		for (j = 0; j < num; j++) {
				p[g][j] = buf[j];
			}
		g++;
		return;
	}
	
		
	for (i = 1; i <= num; i++) {
		for (j = 0; j < x; j++) {
			if (buf[j] == i)
				break;
		}

		if (j == x) {
			buf[x] = i;
			permutation(num, p, x + 1, total);
		}
	}	
	return;
}

int checkAVL(struct tnode *t)
{	int left, right;
	if (t == NULL)
		return 0;

	left = checkAVL(t->left);

	if (left == -1)
		return left;

	right = checkAVL(t->right);

	if (right == -1)
		return right;

	if (abs(left - right) > 1)
		return -1;

	return max(left, right) + 1;
}

int max(int x, int y)
{
	if (x < y)
		return y;

	else
		return x;
}



   


	
	
	

	
	
	
	


	 



			
			

	
	
	
	

/*AVL木プログラム*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tnode
{
	int key;
	struct tnode *left;
	struct tnode *right;
	int height;
};

struct tnode *root = NULL;


struct tnode *addnode(int v, struct tnode *t);
struct tnode *addkey(int v, struct tnode *t);
void traverse(struct tnode *t);
void tree_print(struct tnode *t);/*一番左に表示されている数字をrootとして表示　
								   すなわち表示されている木構造全体を右へ90度回転すると
								   一般の木構造となる*/
int *ramdam(int num, int *p);/*ランダム列の表示*/
int Height(struct tnode *t);
int max(int x, int y);
struct tnode *LLrotate(struct tnode *t);
struct tnode *RRrotate(struct tnode *t);
struct tnode *LRrotate(struct tnode *t);
struct tnode *RLrotate(struct tnode *t);

int main()
{
	int i, num;
	int *p;

	srand(time(NULL));

	printf("Please input number: ");
	scanf("%d", &num);

	p = ramdam(num, p);
	
	for(i = 0; i < num; i++)
		printf("%d ", p[i]);
	printf("\n");
 
	for (i = 0; i < num; i++) {
		root = addkey(p[i], root);
	}
	printf("sort : ");
	traverse(root);
	printf("\n");
	printf("structure of tree\n");

	tree_print(root);

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
			t -> height = 0;
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
		if (t -> key > v) {
			t->left = addkey(v, t->left);
			if ((Height(t->left) - Height(t->right)) == 2) {
				if(v < t->left->key)
					t = LLrotate(t);
				else
					t = LRrotate(t);
			}
		}		
		else {
			t->right = addkey(v, t->right);
			if ((Height(t->right) - Height(t->left)) == 2) {
				if(v > t->right->key)
					t = RRrotate(t);
				else
					t = RLrotate(t);
			
			}
		}
	}

	
	t->height = max(Height(t->left),  Height(t->right)) + 1;
	
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

int Height(struct tnode *t)
{
	if (t == NULL)
		return -1;

	else
		return t->height;
}

int max(int x, int y)
{
	if (x < y)
		return y;
	else
		return x;
}

struct tnode *LLrotate(struct tnode *t)
{
	struct tnode *tmp;

	tmp = t->left;
	t->left = tmp->right;
	tmp->right = t;
	
	t->height = max(Height(t->left), Height(t->right)) + 1;
	tmp->height = max(Height(tmp->left),  t->height) + 1;
	
	return tmp;
}


struct tnode *RRrotate(struct tnode *t)
{
	struct tnode *tmp;

	tmp = t->right;
	t->right = tmp->left;
	tmp->left = t;
	
	t->height = max(Height(t->right), Height(t->left)) + 1;
	tmp->height = max(Height(tmp->right), t->height) + 1;
	
	return tmp;
}

struct tnode *LRrotate(struct tnode *t)
{
	t->left = RRrotate(t->left);
	return LLrotate(t);
}

struct tnode *RLrotate(struct tnode *t)
{
	t->right = LLrotate(t->right);
	return RRrotate(t);
}






	

	
	

	
	
	
	


	 



			
			

	
	
	
	

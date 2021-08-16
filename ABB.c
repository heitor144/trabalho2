#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 100000

typedef struct node Node;
Node *newNode(int item);
void inorder(Node *root);
Node *insert(Node *node, int key);
void inserir(Node *root, int k);
Node *pesquisar(Node *x, int k);
Node *minimo(Node *x);
Node *maximo(Node *x);
Node *sucessor(Node *x);
Node *excluir(Node *root, int key);
void inicializarAleatoriamente(int v[], int n);

int main()
{
    srand(time(NULL));

	Node *root = NULL;
	root = insert(root, rand());
	int i, A[TAM];
    double start, stop, elapsed;

	inicializarAleatoriamente(A,TAM);

	// ========================== INSERCAO - INICIO  ==========================//
	start = (double) clock() / CLOCKS_PER_SEC;
	for(i = 0; i < TAM; i++)
		inserir(root,A[i]);

	stop = (double) clock() / CLOCKS_PER_SEC;
    elapsed = stop - start;

    printf("\nABB: Tempo de insercao: %f", elapsed);
	// ========================== INSERCAO - FIM  ==========================//



	// ========================== BUSCA - INICIO  ==========================//
	start = 0;
    stop = 0;
	Node *resultado;

	start = (double) clock() / CLOCKS_PER_SEC;
	for(i = 0; i < TAM; i++){
		resultado = pesquisar(root, rand());
	}	

	stop = (double) clock() / CLOCKS_PER_SEC;
    elapsed = stop - start;
    printf("\n\nABB: Tempo de busca: %f", elapsed);
	// ========================== BUSCA - FIM  ==========================//



	// ========================== EXCLUSÃO - INICIO  ==========================//
	start = 0;
    stop = 0;

	start = (double) clock() / CLOCKS_PER_SEC;
	for(i = 0; i < TAM; i++){
		root = excluir(root, A[i]);
	}
	stop = (double) clock() / CLOCKS_PER_SEC;
	
    printf("\n\nABB: Tempo de exclusao: %f\n",elapsed);
	// ========================== EXCLUSÃO - FIM  ==========================//

	printf("\n\n");

	return 0;
}


struct node{
	int key;
	struct node *left, *right, *p;
};

// utilitario para criar um novo no com chave item
Node *newNode(int item){
	Node *temp = (Node *)malloc(sizeof(Node));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

// Utilitario para percorrer a arvore in-order
void inorder(Node *root){
	if (root != NULL){
		inorder(root->left);
		printf("%d \n", root->key);
		inorder(root->right);
	}
}

// Utilitario para inserir um novo no com uma dada chave em uma arvore binaria de busca
Node *insert(Node *node, int key)
{
	// se a arvore esta vazia, retorna um novo no
	if (node == NULL)
		return newNode(key);

	// caso contrario, desce pela arvore
	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);

	// retorna o ponteiro node (nao modificado)
	return node;
}

void inserir(Node *root, int k){
	Node *z = newNode(k);
	Node *y = NULL, *x = root;

	while (x != NULL){
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == NULL)
		root = z;
	
	else if (z->key < y->key)
		y->left = z;

	else
		y->right = z;

}

Node *pesquisar(Node *x, int k){
	while (x != NULL && k != x->key){
		if (k < x->key)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

Node *minimo(Node *x){
	while (x->left != NULL)
		x = x->left;

	return x;
}

Node *maximo(Node *x){
	while (x->right != NULL)
		x = x->right;

	return x;
}

Node *sucessor(Node *x){
	if (x->right != NULL)
		return minimo(x->right);
	Node *y = x->p;
	while (y != NULL && x == y->right){
		x = y;
		y = y->p;
	}

	return y;
}

Node *excluir(Node *root, int key){
	if (root == NULL)
		return root;

	if (key < root->key)
		root->left = excluir(root->left, key);

	else if (key > root->key)
		root->right = excluir(root->right, key);

	else{

		if (root->left == NULL){
			Node *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL){
			Node *temp = root->left;
			free(root);
			return temp;
		}
		Node *temp = minimo(root->right);
		root->key = temp->key;
		root->right = excluir(root->right, temp->key);
	}
	return root;
}

void inicializarAleatoriamente(int v[], int n){
	int i;
	for (i = 0; i < n; i++)
		v[i] = rand();

}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define TAM 100000

typedef struct ARVORE ARVORE;
ARVORE *rotacao_esquerda_avl(ARVORE *aux);
ARVORE *rotacao_direita_avl(ARVORE *aux);
ARVORE *balancemento_avl(ARVORE *aux);
ARVORE *inserir_avl(ARVORE *aux, int num);
int consultar_avl(ARVORE *aux, int num, int achou);
ARVORE *remover_avl(ARVORE *aux, int num);
ARVORE *atualiza(ARVORE *aux);
void inicializarAleatoriamente(int v[], int n);
void mostrar_emOrdem(ARVORE *aux);
ARVORE *desalocar(ARVORE* aux);


int main()
{
	srand(time(NULL));

	int i = 0, achou = 0;
	double start, stop, elapsed;
	int A[TAM];

	start = 0;
	stop = 0;
	int cont = 0;


	ARVORE *raiz = NULL;
	ARVORE *aux;

	inicializarAleatoriamente(A, TAM);

	// ========================== INSERCAO - INICIO  ==========================//
	start = (double)clock() / CLOCKS_PER_SEC;
	for (i = 0; i < TAM; i++)
		raiz = inserir_avl(raiz, A[i]);

	stop = (double)clock() / CLOCKS_PER_SEC;
	elapsed = stop - start;


	printf("\n\nAVL: Tempo de insercao = %f\n", elapsed);
	// ========================== INSERCAO - FIM  ==========================//


	// ========================== Busca - INICIO  ==========================//
	start = 0;
	stop = 0;

	start = (double)clock() / CLOCKS_PER_SEC;
	for (i = 0; i < TAM; i++)
		achou = consultar_avl(raiz, A[i], achou);

	stop = (double)clock() / CLOCKS_PER_SEC;
	elapsed = stop - start;
	printf("\n\nAVL: Tempo de busca = %f\n", elapsed);
	// ========================== Busca - FIM  ==========================//


	// ========================== EXCLUSÃO - INICIO  ==========================//
	start = 0;
	stop = 0;

	start = (double)clock() / CLOCKS_PER_SEC;
	desalocar(raiz);
	stop = (double)clock() / CLOCKS_PER_SEC;

	elapsed = stop - start;
	printf("\n\nAVL: Tempo de exclusao = %f\n", elapsed);
	// ========================== EXCLUSÃO - FIM  ==========================//

	printf("\n\n");

	return 0;
}

struct ARVORE
{
	int num, altd, alte;
	ARVORE *dir, *esq;
};



ARVORE *rotacao_esquerda_avl(ARVORE *aux)
{
	ARVORE *aux1, *aux2;
	aux1 = aux->dir;
	aux2 = aux1->esq;
	aux->dir = aux2;
	aux1->esq = aux;
	if (aux->dir == NULL)
		aux->altd = 0;
	else if (aux->dir->alte > aux->dir->altd)
		aux->altd = aux->dir->alte + 1;
	else
		aux->altd = aux->dir->altd + 1;

	if (aux1->esq->alte > aux1->esq->altd)
		aux1->alte = aux1->esq->alte + 1;
	else
		aux1->alte = aux1->esq->altd + 1;
	return aux1;
}

ARVORE *rotacao_direita_avl(ARVORE *aux)
{
	ARVORE *aux1, *aux2;
	aux1 = aux->esq;
	aux2 = aux1->dir;
	aux->esq = aux2;
	aux1->dir = aux;
	if (aux->esq == NULL)
		aux->alte = 0;
	else if (aux->esq->alte > aux->esq->altd)
		aux->alte = aux->esq->alte + 1;
	else
		aux->alte = aux->esq->altd + 1;

	if (aux1->dir->alte > aux1->dir->altd)
		aux1->altd = aux1->dir->alte + 1;
	else
		aux1->altd = aux1->dir->altd + 1;
	return aux1;
}

ARVORE *balancemento_avl(ARVORE *aux)
{
	int d, df;
	d = aux->altd - aux->alte;
	if (d == 2)
	{
		df = aux->dir->altd - aux->dir->alte;
		if (df >= 0)
		{
			aux = rotacao_esquerda_avl(aux);
		}
		else
		{
			aux->dir = rotacao_direita_avl(aux->dir);
			aux = rotacao_esquerda_avl(aux);
		}
	}
	else if (d == -2)
	{
		df = aux->esq->altd - aux->esq->alte;
		if (df <= 0)
		{
			aux = rotacao_direita_avl(aux);
		}
		else
		{
			aux->esq = rotacao_esquerda_avl(aux->esq);
			aux = rotacao_direita_avl(aux);
		}
	}
	return aux;
}

ARVORE *inserir_avl(ARVORE *aux, int num)
{
	ARVORE *novo;
	if (aux == NULL)
	{
		//novo = new ARVORE();
		novo = (ARVORE *)malloc(sizeof(ARVORE));
		novo->num = num;
		novo->alte = 0;
		novo->altd = 0;
		novo->esq = NULL;
		novo->dir = NULL;
		aux = novo;
	}
	else if (num < aux->num)
	{
		aux->esq = inserir_avl(aux->esq, num);
		if (aux->esq->altd > aux->esq->alte)
			aux->alte = aux->esq->altd + 1;
		else
			aux->alte = aux->esq->alte + 1;
		aux = balancemento_avl(aux);
	}
	else
	{
		aux->dir = inserir_avl(aux->dir, num);
		if (aux->dir->altd > aux->dir->alte)
			aux->altd = aux->dir->altd + 1;
		else
			aux->altd = aux->dir->alte + 1;
		aux = balancemento_avl(aux);
	}
	return aux;
}

int consultar_avl(ARVORE *aux, int num, int achou)
{
	if (aux != NULL && achou == 0)
	{
		if (aux->num == num)
			achou = 1;
		else if (num < aux->num)
			achou = consultar_avl(aux->esq, num, achou);
		else
			achou = consultar_avl(aux->dir, num, achou);
	}
	return achou;
}

ARVORE *remover_avl(ARVORE *aux, int num)
{
	ARVORE *p, *p2;
	if (aux->num == num)
	{
		if (aux->esq == aux->dir)
		{
			free(aux);
			return NULL;
		}
		else if (aux->esq == NULL)
		{
			p = aux->dir;
			free(aux);
			return p;
		}
		else if (aux->dir == NULL)
		{
			p = aux->esq;
			free(aux);
			return p;
		}
		else
		{
			p2 = aux->dir;
			p = aux->dir;
			while (p->esq != NULL)
			{
				p = p->esq;
			}
			p->esq = aux->esq;
			free(aux);
			return p2;
		}
	}
	else if (aux->num < num)
		aux->dir = remover_avl(aux->dir, num);
	else
		aux->esq = remover_avl(aux->esq, num);
	return aux;
}

ARVORE *atualiza(ARVORE *aux)
{
	if (aux != NULL)
	{
		aux->esq = atualiza(aux->esq);
		if (aux->esq == NULL)
			aux->alte = 0;
		else if (aux->esq->alte > aux->esq->altd)
			aux->alte = aux->esq->alte + 1;
		else
			aux->alte = aux->esq->altd + 1;

		aux->dir = atualiza(aux->dir);
		if (aux->dir == NULL)
			aux->altd = 0;
		else if (aux->dir->alte > aux->dir->altd)
			aux->altd = aux->dir->alte + 1;
		else
			aux->altd = aux->dir->altd + 1;

		aux = balancemento_avl(aux);
	}
	return aux;
}

void inicializarAleatoriamente(int v[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		v[i] = rand();

}

void mostrar_emOrdem(ARVORE *aux){
	if (aux != NULL){
		mostrar_emOrdem(aux->esq);
		printf("%d ", aux->num);
		mostrar_emOrdem(aux->dir);
	}
}

ARVORE *desalocar(ARVORE* aux){
	if(aux != NULL){
		aux->esq = desalocar(aux->esq);
		aux->dir = desalocar(aux->dir);
		free(aux);
	}
	
	return NULL;
}


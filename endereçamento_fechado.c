#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// constante repesenta o tamanho da tabela
#define P 10000

// constante representa o tamanho do vetor de números aleatórios não repetidos
#define N 60007


// tipo pessoa
typedef struct {
    int codigo;
} Pessoa;

// tipo nó usado na lista encadeada
typedef struct no {
    Pessoa pessoa;
    struct no *proximo;
} No;

// tipo lista com um ponteiro para o primeiro nó
typedef struct {
    No *inicio;
    int tam;
} Lista;

//tabela (vetor de ponteiros para listas)
Lista *tabela[P];

//--------------------------------- fim definições variáveis --------------------

//--------------------------------- funções meus tipos --------------------------

// cria e retorna um tipo pessoa
Pessoa criarPessoa(int x) {
    Pessoa p;
    p.codigo = x;
    return p;
}

// imprime uma pessoa
void imprimirPessoa(Pessoa p) {
    printf("\tcodigo: %d\n", p.codigo);
}

//-------------------------------- início funções lista -------------------------
// cria uma lista vazia e retorna seu endereço na memória
Lista* criarLista() {
    Lista *l = malloc(sizeof(Lista));
    l->inicio = NULL;
    l->tam = 0;
    return l;
}

/*
    inserir no início da lista
    PARÂMETROS
    p - nova pessoa a ser inserida
    *lista - endereço de uma lista encadeada.
*/
void inserirInicio(Pessoa p, Lista *lista) {
    No *no = malloc(sizeof(No));
    no->pessoa = p;
    no->proximo = lista->inicio;
    lista->inicio = no;
    lista->tam++;
}

// busca um elemento na lista
No* buscarNo(int mat, No *inicio) {

    while(inicio != NULL) {
        if(inicio->pessoa.codigo == mat)
            return inicio;
        else
            inicio = inicio->proximo;
    }
    return NULL;// codigo não encontrada
}

void imprimirLista(No *inicio) {
    while(inicio != NULL) {
        imprimirPessoa(inicio->pessoa);
        inicio = inicio->proximo;
    }
}
//---------------------------------- fim funções lista -------------------------

//--------------------------- início funções tabela hash -----------------------
// inicializa a tabela com uma lista vazia em cada posição do vetor
void inicializar(){
    int i;
    for(i = 0; i < P; i++)
        tabela[i] = criarLista();
}

// função de espalhamento
int funcaoEspalhamento(int mat){
    return (mat * 7) % P;
}

// cria uma pessoa e a insere na tabela
void inserTabela(int vetor[]){
    int i;
    for(i = 0; i < N; i++){
        Pessoa pes = criarPessoa(vetor[i]);
        int indice = funcaoEspalhamento(pes.codigo);
        inserirInicio(pes, tabela[indice]);
    }
}

// busca uma pessoa. Seu retorno é um endereço ou NULL
Pessoa* buscarPessoaTabela(int mat){
    int indice = funcaoEspalhamento(mat);
    No *no = buscarNo(mat, tabela[indice]->inicio);
    if(no)
        return &no->pessoa;
    else
        return NULL;
}

// imprimir tabela
void imprimirTabela(){
    int i;
    printf("\n---------------------TABELA-------------------------\n");
    for(i = 0; i < P; i++){
        printf("%d Lista tamanho: %d\n", i, tabela[i]->tam);
        imprimirLista(tabela[i]->inicio);
    }
    printf("---------------------FIM TABELA-----------------------\n");
}

// inicializa um vetor de 0 a N
void inicializarVetor(int vetor[]){
    int i;
    for(i = 0; i < N; i++){
        vetor[i] = i;
    }
}

// "embaralha" o vetor
void fisherShuffle(int vetor[]){
    int i, j, temp;
    i = N;
    while(i > 1){
        i = i - 1;
        j = rand() % i;
        temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }
}

int main() {

    srand(time(NULL));

    int op, mat, i, vetor[N];
    double start, stop, elapsed;
    Pessoa *p;

    inicializar();

    inicializarVetor(vetor);

    fisherShuffle(vetor);

    printf("Programa executando, aguarde...\n");

    start = (double) clock() / CLOCKS_PER_SEC;

    // insere todos os elementos presentes no vetor que foi "embaralhado" anteriormente
    inserTabela(vetor);

    // busca cada elemento que foi passado anteriormente para a tabela
    for(i = 0; i < N; i++){
        p = buscarPessoaTabela(vetor[i]);
    }

    stop = (double) clock() / CLOCKS_PER_SEC;
    elapsed = stop - start;

    imprimirTabela();

    printf("\nTempo de insercao e busca: %f.\n", elapsed);

    return 0;
}
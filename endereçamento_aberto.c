#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constante repesenta o tamanho da tabela
#define M 60007

// constante representa o tamanho do vetor de números aleatórios não repetidos
#define N 10000


// estrutura Pessoa com um numero
typedef struct{
    int numero;
}Pessoa;

// tabela hash do tipo Pessoa
Pessoa tabelaHash[M];

// inicializa a tabela com o valor de numero para cada pessoa de -1
void inicializarTabela(){
    int i;
    for(i = 0; i < M; i++)
        tabelaHash[i].numero = -1;
}

// função de espalhamento (resto da divisão da chave (vezes algum numero aleatorio ate 5) por M)
int gerarCodigoHash(int chave){
    return chave * 5 % M;
}

// função para ler e retornar uma pessoa
Pessoa lerPessoa(int x){
    Pessoa p;
    p.numero = x;
    return p;
}

// insere cada valor (único) do vetor na tabela Hash
void inserir(int vetor[]){
    int i;
    for(i = 0; i < N; i++){
        Pessoa pes = lerPessoa(vetor[i]);
        int indice = gerarCodigoHash(pes.numero);
        while(tabelaHash[indice].numero != -1)
        indice = gerarCodigoHash(indice + 1);
        tabelaHash[indice] = pes;
    }
}

Pessoa* buscar(int chave){
    int i = 0;
    while(i >= 0){
        if(tabelaHash[i].numero == chave)
            return &tabelaHash[i];
        else
            i++;
    }
    return NULL;
}

void imprimir(){
    int i;
    printf("\n------------------------TABELA---------------------------\n");
    for(i = 0; i < M; i++){
        if(tabelaHash[i].numero != -1)
            printf("%2d = %3d \n", i, tabelaHash[i].numero);
        else
            printf("%2d =\n", i);
    }
    printf("\n----------------------------------------------------------\n");
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

    int i, vetor[N];
    double start, stop, elapsed;
    Pessoa *p;

    inicializarTabela();

    inicializarVetor(vetor);

    fisherShuffle(vetor);

    printf("Programa executando, aguarde...\n");
    start = (double) clock() / CLOCKS_PER_SEC;
    
    // insere todos os elementos presentes no vetor que foi "embaralhado" anteriormente
    inserir(vetor);

    // busca cada elemento que foi passado anteriormente para a tabela
    for(i = 0; i < N; i++){
        p = buscar(vetor[i]);
    }

    stop = (double) clock() / CLOCKS_PER_SEC;
    elapsed = stop - start;

    imprimir();

    printf("\nTempo de insercao e busca: %f.\n", elapsed);

    return 0;
}
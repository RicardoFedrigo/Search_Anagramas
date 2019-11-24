#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Definiçoes 

#define MAIOR_PALAVRA_PT 29
#define HASH 29;
#define N_RELOCACAO 10



//--------------------------------FUNCOES HASH--------------------------------------------------

int converte_letras(char c){
    int valor_numero = 0;
    valor_numero = (int)c;
    return valor_numero;
}

int calcula_hash(char* palavra){

    int valor_hash = 0;

    for (int i = 0; palavra[i] != '\0'; i++)
    {
        valor_hash += converte_letras(palavra[i]);
    }
    
    return valor_hash % HASH;

}

//--------------------------------FUNCOES UTILITARIAS----------------------------------------------

void imprime_palavra(char* p){
     
    for (int i = 0; p[i] != '\0'; i++)
    {
        printf("%c",p[i]);
    }
    printf("\n");
}   


char* sort_palavras(char palavra[]){
    
    int len = strlen(palavra);
    char aux;

    for (int i = 0; i < len; i++){
        for (int j = (i+1); j < len; j++)
        {
            if (converte_letras(palavra[i]) > converte_letras(palavra[j]))
            {
                aux = palavra[i];
                palavra[i] = palavra[j];
                palavra[j] = aux;
            }
        }
    }
    return palavra;
}


//--------------------------------FUNCOES PALAVRA--------------------------------------------------

typedef struct Palavras
{
    char* palavra;
    struct Palavras* prox;

}Palavras;

Palavras* cria_p(){
    Palavras* palavra =(Palavras*)malloc(sizeof(Palavras));
    palavra->palavra = "";
    palavra->prox = 0;
    return palavra;
}

Palavras* encontra_ultimo(Palavras* p){
    
    Palavras* aux = p;
    p = p->prox;
    while (p != NULL)
    {
        aux = p;
        p = p->prox;
    }
    return aux;
}

void insere_palavra(Palavras* p,char* palavra){
    
    Palavras* nova_palavra = (Palavras*)malloc(sizeof(Palavras));
    
    nova_palavra->palavra =(char*)malloc((strlen(palavra)+1)*(sizeof(char)));
    strcpy(nova_palavra->palavra,palavra);     
    
    Palavras* aux = encontra_ultimo(p);
    aux->prox = nova_palavra;
    
}

//--------------------------------FUNCOES "NO DE PALAVRA"--------------------------------------------------
typedef struct Palavra_No
{
    int valor_hash;
    Palavras* palavras;
}PN;


PN* cria_pn(int valor_hash){
    
    PN* pn =(PN*)malloc(sizeof(PN));
    pn->palavras = cria_p();
    pn->valor_hash = valor_hash;
    return pn;

}

void insere_pn(PN* pn, char* palavra){
    
    if(pn->palavras->palavra == ""){
        
        char* new = (char*)malloc((strlen(palavra)+1)*(sizeof(char)));
        strcpy(new,palavra);
        pn->palavras->palavra = sort_palavras(new); 
    }
    
    insere_palavra((pn->palavras), palavra);
    
}


void imprime_pn(PN* pn){

    Palavras* p = pn->palavras;
    
    while (p)
    {
        imprime_palavra(p->palavra);
        p = p->prox;
    }
    

}   
//--------------------------------FUNCOES ESTRUTURA VETOR  VETOR--------------------------------------------------

typedef struct Vetor{
    unsigned int tamanho;
    unsigned int n_ocupados;
    PN vetores_pn[];
}V;

V* sort_vetor(V* vetor){

}
V* realoca_vetor(V* vetor){

    int novo_tamanho = vetor->tamanho + N_RELOCACAO;
    V* novo_vetor =(V*) malloc(sizeof(V));
    
    novo_vetor->tamanho = (novo_tamanho);
    novo_vetor->n_ocupados = vetor->n_ocupados;
    novo_vetor->vetores_pn[novo_tamanho];
    
    memcmp(&novo_vetor->vetores_pn,&vetor->vetores_pn,vetor->tamanho);
    free(vetor);
    
    return novo_vetor;

}

V* verifica_vetor( V* vetor){
    if (vetor->n_ocupados == vetor->tamanho)
    {
        realoca_vetor(vetor);

    }
    return 0;
}

V* cria_vetor(){

    V* vetor =(V*)malloc(sizeof(V));

    vetor->tamanho = N_RELOCACAO;
    vetor->n_ocupados = 0;
    vetor->vetores_pn[N_RELOCACAO];

    return vetor;
}

int posicao_vetor_hash(PN vetor[], int hash, int tamanho){
    
    int inf = 0;     
    int sup = tamanho-1;
    int meio;
    
    while (inf <= sup)
    {
         meio = (inf + sup)/2;
         if (hash == vetor[meio].valor_hash)
              return meio;
         if (hash < vetor[meio].valor_hash)
              sup = meio-1;
         else
              inf = meio+1;
    }
    return -1; 

}

void insere_vetor(V* vetor,char* palavra){
    
    int valor_hash = calcula_hash(palavra);
    int elemento = posicao_vetor_hash(vetor->vetores_pn,valor_hash,vetor->n_ocupados);
    


}

void imprime_vetor(V* vetor){

    for (int i = 0; i < vetor->n_ocupados; i++)
    {
        imprime_pn(&vetor->vetores_pn[i]);
    }
}

// _____________________________________________________________________________________________

int main(int argc, char const *argv[])
{
    
    V* vetor = cria_vetor();
    return 0;
}

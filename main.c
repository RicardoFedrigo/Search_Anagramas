#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Definiçoes 

#define MAIOR_PALAVRA_PT 29
#define HASH 29;
#define N_RELOCACAO 10


//--------------------------------FUNCOES TIPOS--------------------------------------------------

typedef struct Palavras
{
    char* palavra;
    struct Palavras* prox;

}Palavras;

typedef struct Palavra_No
{
    char* sorted_palavra;
    Palavras* palavras;
}PN;

typedef struct Guarda_PN 
{
   PN *pn;
   struct Guarda_PN *prox;
}GPN;

typedef struct Me_passa
{
    unsigned int valor_hash;
    GPN* gpn;
}MP;

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

void sort_mp(MP mp[],int size){

    MP aux;
    for (int i = 0; i < size; i++){
        for (int j = 1; j < size; j++)
        {
            if (mp[i].valor_hash > mp[j].valor_hash)
            {
                aux = mp[i];
                mp[i] = mp[j];
                mp[j] = aux;
            }
        }
    }
}
//--------------------------------FUNCOES PALAVRA--------------------------------------------------


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


PN* cria_pn(){
    
    PN* pn =(PN*)malloc(sizeof(PN));
    pn->sorted_palavra = 0;
    pn->palavras = cria_p();
    
    return pn;

}

PN* insere_pn(PN* pn, char* palavra){
    
    if(pn->sorted_palavra == 0){
        
        char* new = (char*)malloc((strlen(palavra)+1)*(sizeof(char)));
        strcpy(new,palavra);
        pn->sorted_palavra = sort_palavras(new); 
    }
    
    insere_palavra((pn->palavras), palavra);
    return pn;    
}

void imprime_pn(PN* pn){

    Palavras* p = pn->palavras->prox;
    
    printf("Palanvra do NO orgainzada: ");
    imprime_palavra(pn->sorted_palavra);
    while (p)
    {   
        imprime_palavra(p->palavra);
        p = p->prox;
    }
}
//--------------------------------GUARDA PN--------------------------------------------------


void insere_gpn(GPN *gpn,PN *pn)
{
    GPN* new =(GPN*)malloc(sizeof(GPN));
    GPN* aux = gpn;
    new->pn = pn;
    new->prox = gpn->prox;
    gpn->prox = new;
}

void imprime_gpn(GPN* gpn)
{
    GPN* aux = gpn->prox;

    while (aux)
    {
        imprime_pn(aux->pn);
        aux = aux->prox;
    }
    
}

PN* procura_anagrama(GPN* gpn,char* palavra)
{   
    GPN* aux = gpn->prox;
    char* new = (char*)malloc((strlen(palavra)+1)*(sizeof(char)));
    strcpy(new,palavra);
    sort_palavras(new);
    while (aux)
    {
        if (strcmp(aux->pn->sorted_palavra,new) == 0)
        {   
            return aux->pn;
        }
        aux = aux->prox;
    }
    return 0;
}

//--------------------------------FUNCOES ADM PALAVRAS IGUAIS--------------------------------------------------


MP* cria_mp(int valor)
{
    MP* mp =(MP*)malloc(sizeof(MP));
    GPN* gpn = (GPN*)malloc(sizeof(GPN));

    mp->gpn = gpn;
    mp->valor_hash = valor;
    return mp;
}

void insere_mp(MP* mp,PN* pn)
{
    insere_gpn(mp->gpn,pn);
}

void imprime_mp(MP *mp){
    printf("VALOR HASH: %d \n",mp->valor_hash);
    imprime_gpn(mp->gpn);
}
//_____________________________________________________________________________________

int main(int argc, char const *argv[])
{
    GPN* gpn = (GPN*)malloc(sizeof(GPN));
    PN* novo1 = cria_pn();
    insere_pn(novo1,"roma");
    insere_pn(novo1,"amor");
    insere_gpn(gpn,novo1);

    PN* novo2 = cria_pn();
    insere_pn(novo2,"teste");
    insere_pn(novo2,"estte");
    insere_gpn(gpn,novo2);

    PN* novo3 = cria_pn();
    insere_pn(novo3,"aranha");
    insere_pn(novo3,"cegonha");
    insere_pn(novo3,"vergonha");
    insere_gpn(gpn,novo3);

    MP* mp = cria_mp(10);
    insere_mp(mp,novo1);
    insere_mp(mp,novo2);
    insere_mp(mp,novo3);

    imprime_mp(mp);

    return 0;
}

#ifndef _PROCURA_ANAGRAMAS_H
#define _PROCURA_ANAGRAMAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Definiçoes 

#define MAIOR_PALAVRA_PT 
//#define HASH 130

#define HASH 8231
#define N_RELOCACAO 10


//----------------------------------------TIPOS--------------------------------------------------

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
    unsigned int valor_numero = 0;
    valor_numero = (int)c;
    valor_numero*=valor_numero;
    return (valor_numero);
}

int calcula_hash(char* palavra){

    unsigned int valor_hash = 0;
   
    for (int i = 0; palavra[i] != '\0'; i++)
    {
        valor_hash += converte_letras(palavra[i]);

    }
    return (valor_hash % HASH);
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

char *trim(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while(isspace((char)*(--endp)) && endp != frontp ) {}
    }

    if( frontp != str && endp == frontp )
            *str = '\0';
    else if( str + len - 1 != endp )
            *(endp + 1) = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
            while( *frontp ) { *endp++ = *frontp++; }
            *endp = '\0';
    }

    return str;
}

char* retorna_palavra_arrumada(char* palavra)
{
    char* new = (char*)malloc((strlen(palavra)+1)*(sizeof(char)));
    strcpy(new,palavra);
    sort_palavras(new);

    return new;
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
                
        pn->sorted_palavra = retorna_palavra_arrumada(palavra); 
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

    if (aux)
    {
        while (aux)
        {
            imprime_pn(aux->pn);
            aux = aux->prox;
        }
    
    }else{
        printf("NÃO A PALAVRAS NESSA POSIÇÃO \n");
        printf("\n");
    }
    
    
}

PN* procura_anagrama(GPN* gpn,char* palavra)
{   
    GPN* aux = gpn->prox;
    char* new = retorna_palavra_arrumada(palavra);
    while (aux)
    {
        if (!strcmp(aux->pn->sorted_palavra,new))
        {   
            return aux->pn;
        }
        aux = aux->prox;
    }

    free(new);
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


//--------------------------------REGRAS DE NEGOCIO------------------------------------

MP** cria_rn(){

    MP** mp =(MP** )malloc(HASH*sizeof(MP*));
    for (int i = 0; i < HASH; i++)
    {
        mp[i] = cria_mp(i);
    }

    return mp;
}

int compara_rn(GPN* gpn, char* palavra)
{
    PN* se_existir = procura_anagrama(gpn,palavra);

    if (se_existir)
    {
        char* new = retorna_palavra_arrumada(palavra);
        char* ponteiro_mp_hash = gpn->prox->pn->sorted_palavra;
        if (!strcmp(ponteiro_mp_hash,new))
        {
            return 1;
        }
    }
    return 0;

}

void insere_rn(MP** mp,char* palavra)
{
    unsigned int valor_hash = calcula_hash(palavra);
    
    if (mp[valor_hash]->valor_hash == valor_hash)
    {
        if (compara_rn(mp[valor_hash]->gpn,palavra))
        {   
            insere_pn(mp[valor_hash]->gpn->prox->pn,palavra);
        }else
        {
            PN* pn = cria_pn();
            insere_pn(pn,palavra);
            insere_mp(mp[valor_hash],pn);
        }
    }
}


PN* procura_anagramas_palavra(MP** mp, char* palavra)
{
    unsigned int valor_hash = calcula_hash(palavra);
    PN* pn = procura_anagrama(mp[valor_hash]->gpn,palavra);
    if (pn)
    {
        printf("Peso da palavra: %d \t ",valor_hash);
        printf("Palavra procurada: ");
        imprime_palavra(palavra);
        imprime_pn(pn);
        return pn;
    }
    
    printf("Palavra procurada não existe ");    
    return 0;
}

void imprime_rn(MP** mp)
{
    for (int i = 0; i < HASH; i++)
    {
        printf("Vetor na posicao [%d] :\n", i );
        imprime_mp(mp[i]);
    }
    
}
#endif
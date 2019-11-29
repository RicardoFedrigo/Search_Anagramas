#include "procura_anagramas.h"

MP** carrega_arquivo(){
    MP** mp = cria_rn();
    FILE *arq;
    char Linha[100];
    char *result;
    int i =1;

    arq = fopen("list_anagramas.txt", "rt");
    if (arq == NULL)  
    {
       printf("Problemas na abertura do arquivo\n");
       return 0;
    }
    while (!feof(arq))
    {
        result = fgets(Linha, 100, arq);
        if (result)
        {   
            printf("Adicionando %d : %s",i,result);
            printf("Peso: %d \t",calcula_hash(result));      
    	    insere_rn(mp,Linha);
            i++;
        }
    }
    printf("\n");
    return mp;
}
int main(int argc, char const *argv[])
{
    MP** mp = carrega_arquivo();  
    procura_anagramas_palavra(mp,"roma");
    imprime_gpn(mp[5452]->gpn);
//     imprime_rn(mp);
//     PN* pn = procura_anagramas_palavra(mp,"roma");
//     imprime_pn(pn);
  
    return 0;
}

#include "procura_anagramas.h"

int main(int argc, char const *argv[])
{
    MP** mp = cria_rn();
    insere_rn(mp,"TETES");
    insere_rn(mp,"amor");
    insere_rn(mp,"roma");
    insere_rn(mp,"mora");
    insere_rn(mp,"coisa");
    
    procura_anagramas_palavra(mp,"roma");

    imprime_rn(mp);
    printf("\n");
    printf("\n");
    printf("\n");

    PN* pn = procura_anagramas_palavra(mp,"roma");
    imprime_pn(pn);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLER 6250000 // 250M Ã© divisÃ­vel por 6.25M

int main(int argc, char *argv[])
{
    int percentagem = atoi(argv[2]); // Percentagem de similaridade desejada
    int tamanho = strlen(argv[1]); // Tamanho da sequência pesquisada
    float passoPercentual = 100./tamanho; // Percentagem de similaridade para cada match

    int tamanhos[25] = { 0,
                         248956422, // 1
                         242193529, // 2
                         198295559, // 3
                         190214555, // 4
                         181538259, // 5
                         170805979, // 6
                         159345973, // 7
                         145138636, // 8
                         138394717, // 9
                         133797422, // 10
                         135086622, // 11
                         133275309, // 12
                         114364328, // 13
                         107043718, // 14
                         101991189, // 15
                          90338345, // 16
                          83257441, // 17
                          80373285, // 18
                          58617616, // 19
                          64444167, // 20
                          46709983, // 21
                          50818468, // 22
                         156046895, // 23 F
                          57227415}; // 23 M


    char myseq[tamanho]; // Sequência a ser comparada
    strcpy(myseq,argv[1]); // A sequência entrada pelo utilizador

    int f,i,j,k,m;
    float similaridade, maior;

    printf("\nQuer buscar a sequência %s com %d%% de similaridade\n", myseq,percentagem);
    int num_cromossomas = 4;
    for (f=1; f < num_cromossomas; f++)
    {
        char nome[16];
        char cromossoma1[MAXLER]; // Ler blocos para memória

        sprintf(nome, "Cromossoma%d", f);
        FILE *fp = fopen(nome,"r");
        if (fp == NULL)
            return 0;

        for (m = 0; m < tamanhos[f]; m+=MAXLER)
        {
//            printf("Lendo %d caracteres a partir da posição %d do cromossoma %d...\n",maxler,m,f);
            for(i = 0; i < (MAXLER); i++)
            {
                char base = fgetc(fp);
                cromossoma1[i] = base;
            }

            for (j = 0; j < (MAXLER-tamanho); j++)
            {
                similaridade = 0;
                for (k=0; k<tamanho; k++)
                {
                    if (myseq[k] == cromossoma1[j+k])
                    {
                        similaridade += passoPercentual;
                    }
                }
                if (similaridade >= percentagem)
                {
                    printf("Cromossoma %d: Similaridade de %.0f%% na posicao %d: ",f,similaridade,j+m);
                    for (k=0; k<tamanho; k++)
                        printf("%c",cromossoma1[j+k]);
                    printf("\n");
                    //return 0; // se quiser encontrar só uma ocorrência...
                }
            }
        }
        fclose(fp);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[])
{
  int percentagem = atoi(argv[2]); // Percentagem de similaridade desejada
  int tamanho = strlen(argv[1]); // Tamanho da sequência pesquisada
  float passoPercentual = 100./tamanho; // Percentagem de similaridade para cada match
  int maxler = 8000000; // valor máximo de leitura em bloco
  char cromo[maxler]; // Lê blocos para memória
  char myseq[tamanho]; // Sequência a ser comparada
  strcpy(myseq,argv[1]); // A sequência entrada pelo utilizador
  int i,j,k,m,g,f;
  float similaridade, maior;

  printf("\nQuer buscar a sequência %s com %d%% de similaridade\n", myseq,percentagem);

  int tamanhos[25] = {0,
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

    for (f=1; f < 4; f++)
    {

        char nome[16];
        sprintf(nome, "Cromossoma%d", f);
        FILE *fp = fopen(nome,"r");
        if (fp == NULL)
        return 0;


        for (m = 0; m < tamanhos[f]; m+=maxler)
        {
          // printf("Lendo %d caracteres a partir da posição %d do ficheiro %d...\n",maxler,m,f);
          for(i = 0; i < (maxler); i++)
          {
            char base = fgetc(fp);
            cromo[i] = base;
          }

          for (j = 0; j < (maxler-tamanho); j++)
          {
            similaridade = 0;
            for (k=0; k<tamanho; k++)
            {
              if (myseq[k] == cromo[j+k])
              {
                similaridade += passoPercentual;
              }
            }
            if (similaridade >= percentagem)
            {
              printf("Cromosoma %d: Similaridade de %.0f%% na posicao %d: ",f,similaridade,j+m);
              for (k=0; k<tamanho; k++)
              printf("%c",cromo[j+k]);
              printf("\n");
              //return 0; // se quiser encontrar só uma ocorrência...
            }
          }
        }
        fclose(fp);
    }
      return 0;

  }

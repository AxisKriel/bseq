// Modificação do ficheiro original "bseq.c" seguindo instruções do moodle
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#define MAXLER 6250000 // 250M Ã© divisÃ­vel por 6.25M
#define NUMTHREADS 4

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

    int f,i,j,k,m,n;
    //float similaridade, maior;
    float maior;

    printf("\nQuer buscar a sequência %s com %d%% de similaridade\n", myseq,percentagem);
    int num_cromossomas = 4; // Número limite de cromossomas a ler
    for (f=1; f < num_cromossomas; f++)
    {
      char nome[16];
      //       while (tamanhos[f] % maxler != 0)
      //           maxler--;

      char cromossoma1[NUMTHREADS][MAXLER/NUMTHREADS]; // Ler blocos para memória

      sprintf(nome, "Cromossoma%d", f);
      FILE *fp = fopen(nome,"r");
      if (fp == NULL)
      return 0;

      for (m = 0; m < tamanhos[f]; m+=MAXLER)
      {
        //            printf("Lendo %d caracteres a partir da posição %d do cromossoma %d...\n",maxler,m,f);
        for (n = 0; n < NUMTHREADS-1; n++)
        {
          for(i = 0; i < (MAXLER/NUMTHREADS); i++)
          {
            char base = fgetc(fp);
            cromossoma1[n][i] = base;
          }
        }

        #pragma omp parallel default(none) private(j, k) \
        shared(f, m, cromossoma1, tamanho, myseq, passoPercentual, percentagem) \
        num_threads(NUMTHREADS)
        {
          for (j = 0; j < (MAXLER/NUMTHREADS-tamanho); j++)
          {
            int tid = omp_get_thread_num();
            float similaridade = 0;
            for (k=0; k<tamanho; k++)
            {
              if (myseq[k] == cromossoma1[tid][j+k])
              {
                similaridade += passoPercentual;
              }
            }
            if (similaridade >= percentagem)
            {
              int posicao = tid*MAXLER/NUMTHREADS+j+m;
              printf("Cromossoma %d: Similaridade de %.0f%% na posicao %d: ",f,similaridade,posicao);
              for (k=0; k<tamanho; k++)
              printf("%c",cromossoma1[tid][j+k]);
              printf("\n");
              //return 0; // se quiser encontrar só uma ocorrência...
            }
          }
        }
      }
      fclose(fp);
    }
    return 0;
  }

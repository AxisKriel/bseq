#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#define MAXLER 6250000 // 250M Ã© divisÃ­vel por 6.25M

int main(int argc, char *argv[])
{
    // Iniciar Open MPI
    MPI_Init(NULL, NULL);

    // Obtém número de processos
    int num_processos;
    MPI_Comm_size(MPI_COMM_WORLD, &num_processos);

    // Obtém rank do processo
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Obtém o nome da máquina
    char nome_maquina[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(nome_maquina, &name_len);

    // Identificação do host
    //printf("Host: %s\nRank: %d / %d processos\n",
    //        nome_maquina, rank, num_processos);

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

    if (rank == 0)
        printf("\nQuer buscar a sequência %s com %d%% de similaridade\n", myseq,percentagem);
    int num_cromossomas = 25;
    int f_start = 1 + rank * num_cromossomas/num_processos;
    int f_end = f_start + num_cromossomas/num_processos;
    for (f=f_start; f < f_end; f++)
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
                    //if (rank == 0)
                    //{
                        printf("[%s:%d] Cromossoma %d: Similaridade de %.0f%% na posicao %d: ",
                                nome_maquina,rank,f,similaridade,j+m);
                        for (k=0; k<tamanho; k++)
                            printf("%c",cromossoma1[j+k]);
                    printf("\n");
                    //}
                    //return 0; // se quiser encontrar só uma ocorrência...
                }
            }
        }
        fclose(fp);
    }
    MPI_Finalize();
    return 0;
}

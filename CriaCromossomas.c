#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int getBase()
{
    return rand()%4;
}

int main()
{
    time_t t;
    srand( (unsigned)time(&t) );
    int i,j;
    char nome[16], bases[] = {"ACGT"};
    int tamanhos[24] = {248956422, // 1
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
                         
    for (i=1; i < 25; i++)
    {
      int a = i;
      sprintf(nome, "Cromossoma%d", a);
      printf("A escrever ficheiro %s...\n",nome);

      FILE *fp = fopen(nome,"w");

      if (fp == NULL)
          return 0;
      for (j = 0; j < tamanhos[a-1]; j++)
      {
          if (j == 1000000*(a+1))
          {
              fputc('C',fp);
              fputc('o',fp);
              fputc('m',fp);
              fputc('p',fp);
              fputc('u',fp);
              fputc('t',fp);
              fputc('a',fp);
              fputc('c',fp);
              fputc('a',fp);
              fputc('o',fp);
              fputc('D',fp);
              fputc('e',fp);
              fputc('A',fp);
              fputc('l',fp);
              fputc('t',fp);
              fputc('o',fp);
              fputc('D',fp);
              fputc('e',fp);
              fputc('s',fp);
              fputc('e',fp);
              fputc('m',fp);
              fputc('p',fp);
              fputc('e',fp);
              fputc('n',fp);
              fputc('h',fp);
              fputc('o',fp);
              j += 25;
          } else
              fputc(bases[getBase()], fp);
      }
      fclose(fp);
    }
    return 0;
}
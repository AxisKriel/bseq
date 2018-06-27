# bseq
C.A.D. BSeq Project

## Enunciado
O grupo de alunos deverá entregar e demonstrar uma aplicação de busca de sequências nos 23 cromossomas do genoma humano. Os cromossomas estarão em ficheiros separados e podem ser gerados com o programa CriaCromossoma (com os tamanhos adequados...)..

A aplicação deve usar OpenMPI para executar em múltiplas máquinas (cada uma examinando um grupo diferente de cromossomas) e OpenMP para lançar pelo menos 4 threads em cada máquina para pesquisar dentro do mesmo cromossoma.

Na máquina que lançou a aplicação deverá ser reportado em que cromossomas a sequência aparece com o grau de similaridade desejado.

## Compilação / Testes
Utilização da aplicação `bseq` para procurar a sequência `AAAACCCCTTTTGGGG` em 24 cromossomas gerados aleatóriamente, mas com dimensões idênticas aos 23 pares de cromossomas do genoma humano, com uma taxa de similaridade de >88%. É utilizado o comando `time` de modo a verificar o tempo de execução da aplicação.

### bseq
```
gcc bseq.c -o bseq
time ./bseq AAAACCCCGGGGTTTT 88
```

### bseqMP
```
gcc bseqMP.c -o bseqMP -fopenmp
time ./bseqMP AAAACCCCGGGGTTTT 88
```

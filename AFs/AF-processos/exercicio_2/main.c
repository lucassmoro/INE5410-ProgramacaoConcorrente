#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>


//                          (principal)
//                               |
//              +----------------+--------------+
//              |                               |
//           filho_1                         filho_2
//              |                               |
//    +---------+-----------+          +--------+--------+
//    |         |           |          |        |        |
// neto_1_1  neto_1_2  neto_1_3     neto_2_1 neto_2_2 neto_2_3

// ~~~ printfs  ~~~
//      principal (ao finalizar): "Processo principal %d finalizado\n"
// filhos e netos (ao finalizar): "Processo %d finalizado\n"
//    filhos e netos (ao inciar): "Processo %d, filho de %d\n"

// Obs:
// - netos devem esperar 5 segundos antes de imprmir a mensagem de finalizado (e terminar)
// - pais devem esperar pelos seu descendentes diretos antes de terminar
void funcaofilho(void);
void funcaoneto(void);

int main(int argc, char** argv) {
    int filho1 = fork();
    if (filho1 == 0) funcaofilho();

    int filho2 = fork();
    if(filho2 == 0) funcaofilho();

    while(wait(NULL)>=0);
    printf("Processo principal %d finalizado\n", getpid());
    
    return 0;
}

void funcaofilho(void){
    printf("Processo %d, filho de %d\n",getpid(),getppid());
    fflush(stdout);

    int neto1 = fork();
    if(neto1 == 0) funcaoneto();

    int neto2 = fork();
    if(neto2 == 0) funcaoneto();

    int neto3 = fork();
    if(neto3 == 0) funcaoneto();

    while(wait(NULL)>=0);

    printf("Processo %d finalizado\n", getpid());
    fflush(stdout);
    exit(0);
}
void funcaoneto(void){
    printf("Processo %d, filho de %d\n",getpid(),getppid());
    fflush(stdout);

    sleep(5);
    printf("Processo %d finalizado\n", getpid());
    fflush(stdout);
    exit(0);
}
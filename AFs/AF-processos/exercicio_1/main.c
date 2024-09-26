#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
//       (pai)      
//         |        
//    +----+----+
//    |         |   
// filho_1   filho_2


// ~~~ printfs  ~~~
// pai (ao criar filho): "Processo pai criou %d\n"
//    pai (ao terminar): "Processo pai finalizado!\n"
//  filhos (ao iniciar): "Processo filho %d criado\n"

// Obs:
// - pai deve esperar pelos filhos antes de terminar!
void funcaofilho(void);
int main(int argc, char** argv) {
    int pid1, pid2;
    pid1 = fork();
    if(pid1==0) funcaofilho();

    pid2 = fork();
    if(pid2 == 0) funcaofilho();
    while(wait(NULL)>=0);    

    printf("Processo pai finalizado\n");
    fflush(stdout);
    // ....

    /*************************************************
     * Dicas:                                        *
     * 1. Leia as intruções antes do main().         *
     * 2. Faça os prints exatamente como solicitado. *
     * 3. Espere o término dos filhos                *
     *************************************************/
    
    
       
    return 0;
}
void funcaofilho(void){
    printf("Processo pai criou %d\n",getpid());
    fflush(stdout);

    printf("Processo filho %d criado\n",getpid());
    fflush(stdout);

    exit(0);
}
#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Prueba\n");

    int pid = fork(); //dos procesos concurrentes

    if(pid == 0){
        printf("Soy el proceso hijo\n");
        //sleep(10);
       // printf("ya termine hijo"); //10 segundos despues termina el proceso hijo
    } else{
        printf("Soy el proceso padre\n"); //la terminal se libera cuando el proceso padre se termina
        sleep(10);
        printf("ya termine padre\n");
    }

    return 0;
}
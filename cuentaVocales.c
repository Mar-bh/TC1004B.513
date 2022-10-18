#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

int main(){
    char c;
    char may;
    int totalV = 0; 
    int n = 0;
    do{
        n = read(STDIN_FILENO,&c,1); //solo se lee un caracter a la vez
        may = toupper(c);
        if(may == 'A' || may == 'E' || may == 'I' || may == 'O' || may == 'U'){
            totalV++;
        }

    } while( n != 0);
    printf("El total de vocales fue: %d \n", totalV );
    return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

int main(){
    char c;
    char may; 
    int n = 0;
    do{
        n = read(STDIN_FILENO,&c,1); //solo se lee un caracter a la vez
        may = toupper(c);
        write(STDOUT_FILENO,&may,1);
    } while( n != 0);
    return 0;
}
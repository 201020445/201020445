#include <stdio.h>
#include <stdlib.h>


char terminal[15] = "[MIA]@elder:~$ ";

int main()
{

    char comando[100];
    char opcion[1];

    do{
        printf(terminal);
        setbuf(stdin,NULL);
        scanf("%[^\n]",&comando);

        if(strcmp( comando, "clear")==0){
            system("clear");
        }else if(strcmp( comando, "exit")==0){
           return 0;
        }else{
            strcpy(comando,"");
            analizar(comando);

        }

      }while (opcion);
}

void analizar(char c[100]){

    char comando2[100];
    strcpy(comando2, c );
    printf(comando2);

    const char s[2] = " ";

    char *token;
    int contador = 1;

   // token = strtok(str2, s);

    while( token != NULL )
    {
        agregar(token,contador);
        token = strtok(NULL, s);
        contador++;
    }

}
void agregar(char *t,int c){

}

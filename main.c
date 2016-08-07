#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <string.h>

typedef struct{     //struct para identificar las palabras del comando escrito y la cantidad de palabras recibidas
    char comando[100];
    int numero;
    struct nodo* siguiente;
} nodo;

typedef struct{ //struct para
    char comando[100];
    char atributo[100];
    int numero;
    struct atributo* siguiente;
} atributo;

atributo *first = NULL;
atributo *last = NULL;

nodo *primero = NULL;
nodo *ultimo = NULL;

char terminal[15] = "[MIA]@elder:~$ ";

int main()
{
    char comando[100];
    char opcion[1];

    do{
        printf(terminal);
        setbuf(stdin,NULL);
        scanf("%[^\n]",&comando);

        if(strcmp( comando, "clear")==0 ||strcmp( comando, "limpiar")==0){
            system("clear");

         }else if(strcmp( comando, "exit")==0  || strcmp( comando, "salir")==0){
           return 0;
        }else{

            //printf(comando);

           analizar(comando);  //enviar cadena leida por el teclado
           nodo* aux = primero;  // inicializar lista de palabras leidas
           ejecutar(aux);  //ejecutar la lista cabecera XD

        }

      }while (opcion);
}

void analizar(char c[100]){
    int contador = 1;
    char comando2[100];
    char *token;

    strcpy(comando2, c );  //copiar el comando completo

    token = strtok(comando2, " "); //separar palabras con strtok los espacios en blanco

    while( token != NULL ){
        agregar(token,contador);   //enviar palabra por palabra y la cantidad enviada
        token = strtok(NULL, " ");
        contador++;
    }
}

void agregar(char* comando,int numero){     //agregar a la lista las palabras recibidas
    printf("%s %s %d palabra\n",terminal,comando,numero);

    nodo* nuevo = malloc(sizeof(nodo));     //espacio para lista de palabras
    nuevo->siguiente = NULL;

    strncpy(nuevo->comando, comando,100);

    nuevo->numero = numero;

    if(primero == NULL){     //primer dato si lista esta vacia
        primero = nuevo;
        ultimo  = nuevo;
    }
    else{                       //si lista no esta vacia
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
}

void ejecutar(nodo* comando){ //tomar datos de scanf desde lista

    int i;
    char nombreComando[100];
    char rutaScript[100];

    strcpy(nombreComando, comando->comando);

    for(i = 0; nombreComando[i]; i++)
        nombreComando[i] = tolower(nombreComando[i]); //convierte a minusculas

    if((strcmp( nombreComando, "exec" )==0))    //leer script.sh
    {
        nodo *auxiliar = comando->siguiente;
        strcpy(rutaScript, auxiliar->comando);

        printf(terminal);
        printf(rutaScript);
        printf(" cargado...\n");

        ejecutarScript(rutaScript);         //ejecutar script
        primero = NULL;
    }

}
void ejecutarScript(char ruta[100]){
    printf("%s %s\n",terminal,ruta);
}



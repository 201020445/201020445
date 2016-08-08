#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <string.h>


typedef struct{     //struct para identificar las palabras del comando escrito y la cantidad de palabras recibidas
    char comando[100];
    int numero;
    struct nodo* siguiente;
} nodo;

typedef struct{ //struct para manejar archivo de scripts
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
   // printf("%s %s %d palabra\n",terminal,comando,numero);

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

    if((strcmp( nombreComando, "exec" )==0))    //si ay archivo leer script.sh
    {
        nodo *auxiliar = comando->siguiente;
        strcpy(rutaScript, auxiliar->comando);

        printf(terminal);
        printf(rutaScript);
        printf(" cargado...\n");

        ejecutarScript(rutaScript);         //guardar script en lista enlazada
        primero = NULL;
    }else{
        seleccionComando(comando);     //si no hay que extraer archivo manipular lo que hay en la lista
    }

}
void seleccionComando(nodo* comando){
    int i;
    char nombreComando[200];
    char rutaScript[200];
    char nombreAtributo[200];

    strcpy(nombreComando, comando->comando);

    //printf(nombreComando);

   for(i = 0; nombreComando[i]; i++)
        nombreComando[i] = tolower(nombreComando[i]); // convierte a minusculas

    if((strcasecmp( nombreComando, "mkdisk" )==0) || (strcasecmp( nombreComando, "mkDisk" )==0)){
        printf("Crear Disco\n");

    }else if((strcasecmp( nombreComando, "rmdisk" )==0) || (strcasecmp( nombreComando, "rmDisk" )==0)){
        printf("eliminar disoco");

    }else if((strcasecmp( nombreComando, "fdisk" )==0) || (strcasecmp( nombreComando, "fDisk" )==0)){
        printf("crear particion");

    }else if((strcasecmp( nombreComando, "mkfs" )==0) || (strcasecmp( nombreComando, "mkfs" )==0)){
        printf("Formatear particion\n");

    }else if((strcasecmp( nombreComando, "mount" )==0) || (strcasecmp( nombreComando, "Mount" )==0)){
        printf("montar parcition");

    } else if((strcasecmp( nombreComando, "unmount" )==0) || (strcasecmp( nombreComando, "unMount" )==0)){
        printf("desmontar particion");
    }



}

char *substring(char *string, int position, int length){
    char *pointer;
    int c;

    pointer = malloc(length+1);

    if (pointer == NULL){
        printf("Ya no hay espacion el memoria\n");
        exit(1);
    }

    for (c = 0 ; c < length ; c++){
        *(pointer+c) = *(string+position-1);
         string++;
    }

    *(pointer+c) = '\0';

    return pointer;
}

void ejecutarScript(char ruta[100]){
    printf("%s %s\n",terminal,ruta);

    char rutas[250];
    char cadena[200];
    char* pointer;

    FILE* fichero;      //iniciar para leer el archivo de scripts

    strcpy(rutas,ruta);

    fichero = fopen(rutas, "r");  //leer el archivo y guardarlo en fichero

    if(fichero == NULL)  //si el archivo no existe
    {
        fputs ("Error el archivo no existe \n",stderr);
        return -1;
    }
    else{       //si el fichero existe

        while (!feof(fichero)){

            fgets(cadena, 200, fichero);

            if(strcasecmp( cadena, "\n" )!=0)     //si hay un salto de linea
            {
                pointer = substring( cadena, 1, 1);
                if(strcasecmp( pointer, "#") == 0)      //para reconocer los comentarios
                {

                }
                else{
                    pointer = substring( cadena, 1, strlen(cadena)-1);
                    strcpy(cadena, pointer);

                    analizar(cadena);       //analizar contenido del archivo

                    nodo* auxiliar = primero;   //inizializar lista
                    seleccionComando(auxiliar);  //ir al manejo de los datos de la lista
                    primero = NULL;
                }
            }
        }
    }
    fclose(fichero);        //serrar  el archivo

}




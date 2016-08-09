#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <dirent.h>


typedef struct{     //struct para identificar las palabras del comando escrito y la cantidad de palabras recibidas
    char comando[200];
    int numero;
    struct nodo* siguiente;
} nodo;

typedef struct{ //struct para manejar archivo de scripts
    char comando[200];
    char atributo[200];
    int numero;
    char name[100];
    struct atributo* siguiente;
} atributo;

typedef struct datosG{  //struct para eliminat datos
    char dato[1];
} datoG;

typedef struct particiones{   //struct para crear particiones
    char part_status[50];
    char part_type[50];
    char part_fit[50];
    int part_start;
    int part_size;
    char part_name[16];
    int part_cantidad;
    char part_id[20];
    int particionesHijas[50];
} particion;

typedef struct Master_Boot_Record{  //struct para mbr
    int mbr_tamano;
    char mbr_fecha_creacion[200];
    int mbr_disk_signature;
    particion mbr_particion_1;  //primaria
    particion mbr_particion_2;  //primaria
    particion mbr_particion_3;  //primaria
    particion mbr_particion_4;  //extendida
} mbr;

atributo *first = NULL;
atributo *last = NULL;

nodo *primero = NULL;
nodo *ultimo = NULL;

char terminal[15] = "[MIA]@elder:~$ ";

int main()
{
   menu();
}

void menu(){
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


void analizar(char c[200]){
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

    strncpy(nuevo->comando, comando,200);

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

    if((strcmp( nombreComando, "exec" )==0))    //reconocimiento de exec si ay archivo leer script.sh
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
char *substring(char *string, int position, int length){
    char *pointer;
    int c;

    pointer = malloc(length+1);

    if (pointer == NULL){
        printf("Ya no hay espacion en memoria\n");
        exit(1);
    }

    for (c = 0 ; c < length ; c++){
        *(pointer+c) = *(string+position-1);
         string++;
    }

    *(pointer+c) = '\0';

    return pointer;
}

void seleccionComando(nodo* comando){  //manejar los datos de la lista enlazada
    int i;
    char nombreComando[200];
    char rutaScript[200];
    char nombreAtributo[200];

    strcpy(nombreComando, comando->comando);   //pasar atributos a nombreComando

    //printf(nombreComando);

 if((strcasecmp( nombreComando, "Mkdisk" )==0) || (strcasecmp( nombreComando, "mkdisk" )==0))
    {
        printf("Creando disco...\n");
        nodo* auxiliar = comando->siguiente;
        while(auxiliar != NULL){

            strcpy(nombreAtributo, auxiliar->comando);
            char *path=substring(nombreAtributo, 1,7);

            if(strcasecmp(path,"-path=\"")==0){
                char nuevoPath[200];
                strcpy(nombreAtributo,auxiliar->comando);
                nodo* aux = auxiliar->siguiente;
                strcat(nombreAtributo," ");
                strcat(nombreAtributo,aux->comando);
            }
            splitAtributo(nombreAtributo);  //manejar comandos seguidos de mkdisk
            auxiliar = auxiliar->siguiente;
        }
        atributo* auxiliarFirst= first;
        mkdisk(auxiliarFirst);
        first = NULL;


    }else if((strcasecmp( nombreComando, "rmdisk" )==0) || (strcasecmp( nombreComando, "rmDisk" )==0)){
        printf("eliminar disoco");

    }else if((strcasecmp( nombreComando, "fdisk" )==0) || (strcasecmp( nombreComando, "fDisk" )==0)){
        printf("crear particion");

    }else if((strcasecmp( nombreComando, "mkfs" )==0)){
        printf("Formatear particion\n");

    }else if((strcasecmp( nombreComando, "mount" )==0)){
        printf("montar parcition");

    } else if((strcasecmp( nombreComando, "umount" )==0)){
        printf("desmontar particion");
    }
}

void separarPath(char str[200]){  //manejar direccion para crear disco
    printf("manejo de direccion para crear disco");

}
void mkdisk(atributo* arreglo){  //crear el disco con los parametros obtenidos
    int sizes;
    int boolSizes = 0;
    char unit[200];
    char  nombre[100];
    int boolUnit  = 0;
    int errorUnit = 1;
    char path[200];
    int boolPath = 0;
    char nombreComando [200];
    int bytes;
    int contador=1;
    int error = 0;

    char rutaArchivo[250];

    datoG g;

    if(arreglo!=NULL)
    {
        atributo* auxiliar = arreglo;
        while(auxiliar != NULL)
        {
            strcpy(nombreComando, auxiliar->comando);

            int i;
            for(i = 0; nombreComando[i]; i++)
                nombreComando[i] = tolower(nombreComando[i]); //minusculas

            if(strcasecmp( nombreComando, "-size" )==0)
            {
                sizes = atoi(auxiliar->atributo);
                boolSizes = 1;
            }
            else if(strcasecmp( nombreComando, "+unit" )==0)
            {
                strcpy(unit, auxiliar->atributo);
                boolUnit = 1;
            }
            else if(strcasecmp( nombreComando, "-name" )==0)
            {
                strcpy(nombre, auxiliar->name);

            }

            else if(strcasecmp( nombreComando, "-path" )==0)
            {
                char* pointer = substring(auxiliar->atributo,1,1);
                strcpy(path, auxiliar->atributo);
                char *p = substring(path,1,1);

                char* pathNuevo;
                if(strcasecmp(p,"\"")==0){
                    pathNuevo = substring(path,2,strlen(path)-2);
                    strcpy(path,pathNuevo);

                    char str2[200];
                    strcpy( str2, path );
                    const char s[2] = "/";
                    char *token;
                    int contador = 1;

                    token = strtok(str2, s);

                    while( token != NULL )
                    {
                        token = strtok(NULL, s);
                        contador++;
                    }

                    char str3[200];
                    strcpy( str3, path );
                    const char s2[2] = "/";
                    char *token2;
                    int contador2 = 1;

                    token2 = strtok(str3, s2);
                    char directorio[200];
                    while( token2 != NULL )
                    {
                        if(contador2 != (contador-1)){
                            strcat(directorio,"/");
                            strcat(directorio,token2);
                        }
                        token2 = strtok(NULL, s2);
                        contador2++;
                    }
                    strcat(directorio,"/");

                    int result;
                    result = mkdir(directorio, 0777);
                     if (result == 0)
                       printf("DIRECTORIO CREADO %s\n",directorio);
                     else
                       printf("DIRECTORIO NO CREADO %s\n",directorio);

                }
                boolPath = 1;
            }
            else
            {
                char *pointer = substring(nombreComando,strlen(nombreComando),strlen(nombreComando));
                if(strcasecmp(pointer,"\"")==0){
                    error = 0;
                }else{
                    error = 1;
                }

            }
            auxiliar = auxiliar->siguiente;
        }

        if(error == 1 || boolPath == 0 || boolSizes == 0 || sizes<=0 )
        {
            printf("ERROR AL CREAR DISCO: %s\n",path);
        }
        else
        {
            if((strcasecmp( unit, "k" )==0) || (strcasecmp( unit, "K" )==0))
            {
                bytes = sizes*1024;
                errorUnit = 0;
            }
            else if((strcasecmp( unit, "m" )==0) || (strcasecmp( unit, "M" )==0))
            {
                bytes = sizes*1024*1024;
                errorUnit = 0;
            }

            if(boolUnit == 0)
            {
                bytes = sizes*1024*1024;
                errorUnit = 0;
            }
            else if(errorUnit == 1)
            {
                printf("ERROR AL CREAR DISCO: %s\n",path);
            }

            if(errorUnit == 0)
            {
                mbr mbrInicio;
                particion parti;
                FILE* archivo = fopen(path, "wb+");
                contador = 1;
                if(archivo == NULL)
                {
                    fputs ("Error al leer el archivo ",stderr);
                   // return -1;
                }
                else
                {
                    time_t tiempo = time(0);
                    struct tm *tlocal = localtime(&tiempo);
                    char hora[128];
                    strftime(hora,128,"%d/%m/%y %H:%M:%S",tlocal);
                    // printf("Hora: %s\n",hora);

                    fseek(archivo, 0, SEEK_SET);
                    strcpy(parti.part_status, "Inactiva");
                    strcpy(parti.part_type, "");
                    strcpy(parti.part_fit, "");
                    parti.part_start = sizeof(mbr);
                    parti.part_size = 0;
                    strcpy(parti.part_name, "");
                    parti.part_cantidad = 0;
                    strcpy(parti.part_id, "");
                    int hijas[50];
                    int i;
                    for(i=0;i<50;i++){
                        parti.particionesHijas[i] = 0;
                    }
                    //parti.particionesHijas = hijas;

                    mbrInicio.mbr_tamano = bytes;
                    strcpy(mbrInicio.mbr_fecha_creacion, hora);
                    mbrInicio.mbr_disk_signature = 1;
                    mbrInicio.mbr_particion_1 = parti;
                    mbrInicio.mbr_particion_2 = parti;
                    mbrInicio.mbr_particion_3 = parti;
                    mbrInicio.mbr_particion_4 = parti;
                    fseek(archivo, 0, SEEK_SET);
                    fwrite(&mbrInicio, sizeof(mbr), 1, archivo);

                    while(contador<=bytes)
                    {
                        fwrite(&g, sizeof(datoG), 1, archivo);
                        contador = contador + 1 ;
                    }
                    printf("CREANDO DISCO: %s\n",path);
                  separarPath(path);
                }
                fclose(archivo);
            }
        }
    }
}



void splitAtributo(char str[200]){ //separar atributo para despues de comando principal
  char str2[200];
    strcpy( str2, str );
    const char s[2] = "::";
    char *token;
    int contador = 1;
    char comando[10];
    char atributos[200];

    token = strtok(str2, s);

    while( token != NULL )
    {
        if(contador == 1)
        {
            strcpy(comando, token);
        }
        else if(contador == 2)
        {

            strcpy(atributos, token);
        }
        token = strtok(NULL, s);
        contador++;
    }

    agregarAtributo(comando, atributos, 1);  //agregar los atributos encontrados en lista simple de atributos
}
void agregarAtributo(char* comando, char* attribute, int numero){

     atributo* nuevo = malloc(sizeof(atributo));
    nuevo->siguiente = NULL;
    strncpy(nuevo->comando, comando,200);
    strncpy(nuevo->atributo, attribute,200);
    nuevo->numero = numero;
    if(first == NULL)
    {
        first = nuevo;
        last  = nuevo;
    }
    else
    {
        last->siguiente = nuevo;
        last = nuevo;
    }
}

void ejecutarScript(char ruta[100]){  //ejectuar ruta para localizar con exec
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
                    printf(cadena," comentario\n");
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




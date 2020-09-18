#include "ksamp.h"
#include "parteB.h"
#include "parteC.h"
#include "parteD.h"

int main(int argc, char **argv)
{
	unsigned int c;
	opterr = 0;
	short int flagC = 0;
	short int flagD = 0;

	while((c = getopt (argc, argv, "sl:"))!=-1){
		switch(c){
			case 's':
				if(argc==2){
					flagC = 1;
					break;
				}
				else{
					printf("Las opciones validas son -s , -l a b , siendo a y b numeros enteros.\n");
					return 0;
				}
			case 'l':
				if(argc == 4){
					flagC = 1;
					flagD = 1;
					break;
				}
				else{
					printf("Las opciones validas son -s , -l a b , siendo a y b numeros enteros.\n");
					return 0;
				}
			default:
				printf("Las opciones validas son -s ó -l a b , siendo a y b numeros enteros\n");
				return 0;
		}
	}

	//La cabecera y la parte B se imprimen siempre.
	cabecera();
	parteB();

	if(flagC)
		parteC();
	if(flagD){
		unsigned int *a=&(unsigned int){0}, *b=&(unsigned int){0};
		sscanf(argv[2], "%u", a);
		sscanf(argv[3], "%u", b);
		parteC();
		parteD(*a,*b);
	}

	return 0;
}

/**
 * Llama a las funciones que imprimen la cabecera del programa
 */
void cabecera(){
	printf("\n");
	printHostName();
	printFechaHora();
	return;
}

/**
 * Obtiene el nombre del equipo.
 */
void printHostName(){
	FILE *fd;
	char name[150];                                  //esta longitud que puse es arbitraria... simplemente no creo que exista un nombre de equipo mas largo que ese
	fd = fopen("/proc/sys/kernel/hostname","r");
	fscanf(fd, "%100s", name);					        //como el archivo solo contiene el nombre del equipo, leo esa unica cadena y la almaceno en name
	printf("Nombre de la maquina: %s \n", name);
	fclose(fd);
	return;
}

/**
 * Imprime la fecha y la hora actuales.
 */
void printFechaHora(){
	char fecha[30]; //defino 30 como longitudes arbitrarias de fecha y hora
	char hora[30];
	char matched[BUFFSIZE];
	matchear("/proc/driver/rtc", matched, "rtc_date");
	sscanf(matched, "rtc_date : %15s", fecha);            //con esta funcion extraigo lo que haya en matched despues de "rtc_date : "
	matchear("/proc/driver/rtc", matched, "rtc_time");
	sscanf(matched, "rtc_time : %15s", hora);
	printf("Fecha: %s   -   Hora: %s \n", fecha, hora);
	return;
}

/**
 * Coloca en matched una linea que comienza con la cadena matchStr, recortada de una linea extraida de un archivo de texto.
 * @param filename El archivo en el que se va a buscar.
 * @param matched Almacena la linea que comienza con la cadena matchStr.
 * @param matchStr Cadena a buscar.
 */
void matchear(char* filename, char* matched, char* matchStr){
	char buffer[BUFFSIZE]; //defino de forma arbitraria que la linea no va a tener mas caracteres que BUFFSIZE, total la funcion fgets que utilizo para leer la linea deja de leer una vez que encuentra LF o EOF
	char* match = NULL;
	FILE* fd;
	fd = fopen(filename,"r");

	while(feof(fd) == 0){
		fgets(buffer, BUFFSIZE, fd);           //esta funcion es la que extrae una linea del archivo
		match = strstr(buffer, matchStr);      //esta funcion busca en la linea extraida la cadena matchStr, y devuelve el recorte de la linea desde el comienzo de matchStr
		if(match!=NULL) break;
	}

	fclose(fd);
	strcpy(matched,match);
	return;
}

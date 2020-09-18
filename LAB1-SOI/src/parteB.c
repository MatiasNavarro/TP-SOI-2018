#include "ksamp.h"
#include "parteB.h"

/**
 * Llama a las funciones que imprimen lo solicitado en la parte B del trabajo práctico.
 */
void parteB(){
    printf("\n----------Información del Equipo----------\n");
	printCPUInfo();
	printKernelVersion();
	printNumFilesystemsSuport();
	printUpTime();
	return;
}

/**
 * Imprime la información del CPU.
 */
void printCPUInfo(){
	char matched[BUFFSIZE];
	char tipoCPU[100];  // defino longitudes arbitrarias para el tipo y nombre del cpu
	char modeloCPU[100];
	
	matchear("/proc/cpuinfo", matched, "vendor_id"); //la misma cosa que en printFechaHora
	sscanf(matched, "vendor_id : %255[^\n]c", tipoCPU); //[^x] hace que se lea hasta que se encuentre x.
	
	matchear("/proc/cpuinfo", matched, "model name");
	sscanf(matched, "model name : %255[^\n]c", modeloCPU);
	
	printf("\nTipo de procesador: %s \nModelo: %s\n", tipoCPU, modeloCPU);
	return;
}

/**
 * Imprime la version del kernell.
 */
void printKernelVersion(){
	FILE *fd; 
	char kernelVersion[60];        //longitud arbitraria para el nombre del kernel
	fd = fopen("/proc/version","r"); 
	fscanf(fd, "%60[^(]s", kernelVersion);					//[^x] hace que se lea hasta que se encuentre x.
	printf("Version del Kernel: %s \n", kernelVersion); 
	fclose(fd);
	return;
}

/**
 * Imprime el numero de sistemas de archivos soportados por el kernell.
 */
void printNumFilesystemsSuport(){
	int n = 0;
	//int dato = 0;
	FILE *fd;
	fd = fopen("/proc/filesystems","r");
	
	while(feof(fd) == 0){
	    int dato = fgetc(fd); //lectura de cada caracter en ascii
		if(dato == 10) n++; // en ascii el 10 es salto de linea... como en el archivo los filesystems soportados estan tabulados, cada salto de linea es uno mas
	}
	
	fclose(fd);
	printf("Cantidad de sistemas de archivos soportados por el kernel: %d \n", n+1); 
	return;
}

/**
 * Imprime el tiempo transcurrido desde que se inición el SO, con formato DD HH:MM:SS
 */
void printUpTime(){
	FILE *fd; 
	float time;
	char hms[20];
	fd = fopen("/proc/uptime","r"); 
	fscanf(fd, "%f", &time);
	secToDayHourMinSec(time, hms);
	printf("Tiempo transcurrido desde que se inicio el SO: %s \n", hms); 
	fclose(fd);
	return;
}

/**
 * Convierte un numero de segundos a formato DD HH:MM:SS
 * @param secs Segundos a convertir
 * @param buf Tiempo en formato DD HH:MM:SS
 */
void secToDayHourMinSec (float secs, char* buf){
	unsigned int d, h, m;
	float s;
    
	d = (int) (secs / 86400);
	secs = secs - (long) (d * 86400);
	h = (int) (secs / 3600);
	secs = secs - (long) (h * 3600);
	m = (int) (secs / 60);
	secs = secs - (long) (m * 60);
	s = secs;
	if (d > 0)
		sprintf (buf, "%2ud %2u:%02u:%02.2f", d, h, m, secs);
	else
		sprintf (buf, "%2u:%02u:%02.2f", h, m, s);
	return;
}

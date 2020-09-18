#include "ksamp.h"
#include "parteD.h"

/**
 * Llama a las funciones que imprimen lo solicitado en la parte D del trabajo práctico.
 * @param a Indica cada cuantos segundos se vuelve a evaluar lo solicitado
 * @param b Indica durante cuantos segundos debe hacerse. luego b/a indica cuantos ciclos de a segundos deben realizarse
 */ 
void parteD(int a, int b){	
	int i;
	i=b/a;
	printf("-------------------------------------\n");
	while(i>0){
		pedidosHDD();
		memInfo();
		loadAvg();
		i--;
		sleep(a);
		printf("-------------------------------------\n");
	}
	return;
}

/**
 * Imprime la cantidad de pedidos a disco realizados
 */
void pedidosHDD(){
	char matched[BUFFSIZE];
	unsigned int lecturas, escrituras, pedidos;
		
	matchear("/proc/diskstats", matched, "sda");
	sscanf(matched, "sda %u", &lecturas);
	sscanf(matched, "sda %*u %*u %*u %*u %u", &escrituras);
	pedidos = escrituras + lecturas;
	printf("Cantidad de pedidos al disco: %u\n", pedidos);	
	return;
}

/**
 * Imprime la informacion de la memoria
 */
void memInfo(){
	char matched[BUFFSIZE];
	unsigned int memTotal, memFree;
		
	matchear("/proc/meminfo", matched, "MemTotal");
	sscanf(matched, "MemTotal: %u", &memTotal);	
	matchear("/proc/meminfo", matched, "MemFree");
	sscanf(matched, "MemFree: %u", &memFree);	
	printf("Memoria total: %u MB\n", memTotal/1024);
	printf("Memoria disponible: %u MB\n", memFree/1024);
	return;
}

/**
 * Imprime lista de promedios de carga de un minuto
 */
void loadAvg(){
	FILE *fd;
	float load;			
	fd = fopen("/proc/loadavg","r");
	fscanf(fd,"%f", &load);			
	printf("Promedio de carga de un minuto: %f\n", load);
	fclose(fd);
	return;
}

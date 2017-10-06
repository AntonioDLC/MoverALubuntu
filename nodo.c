#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "commons/config.h"
#include "../../shared/configuraciones.h"

#define PATH_CONFIG "nodo.conf"
#define PATH_DATANODO "datanode"

int main(void) {
	t_config *nodoConf = config_create(PATH_CONFIG);
	
	iniciarDataNodo(nodoConf);
	iniciarWorker(nodoConf);

	return 0;
}

void iniciarDataNodo(t_config * nodoConf){
	char ** argv = malloc(sizeof(char*)*2);
	argv[0] = malloc(strlen(PATH_DATANODO));
	
	strcpy(argv[0], PATH_DATANODO);	
	argv[1] = obtener_configuracion_nodo(t_config *config);
	
	execv("PATH_DATANODO", argv);
	
	puts("ERRRROOOOR");
	return -1;
}

void iniciarWorker(t_config * nodoConf){
	
}

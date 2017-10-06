#include <sys/mman.h>
#include "shared/sockets.h"
#include "comandosFS.h"

void borrarEstado(char*path){
	puts("Borrar estado");
}

void copiarAYamaFs(char *yamaDest, char *origen, fileSysADM* fileSysCerebro]){
	int tTotal = tamanioArchivo(origen);
	int fd = open("data.bin", O_RDWR);
	char *data = mmap(NULL, tTotal*getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	enviarANodos(yamaDest, data, tTotal, fileSysCerebro);
}

void enviarANodos( char *yamaDest, char *data, int tTotal, fileSysADM *fileSysCerebro){
	tPaquete paquete = crearPaquete(1, 1024, data);
	int i = 0;
	t_list nodos = fileSysCerebro->nodos;
	t_log * pLogger = fileSysCerebro->pLogger;
	
	while(i*1024 < tTotal){
		enviarAlNodo(nodos, i, pLogger);
		enviarAlNodo(nodos, i+1, pLogger);
		i++;
		memcpy(paquete->payload, data+i*1024, 1024);
	}
}

void enviarAlNodoI(t_list *nodos, int i, t_log *pLogger){
	enviarPaquete(list_get(nodos, i)->socketFS, &paquete, pLogger, "Envio de paquete de archivo");
}

/*
 ============================================================================
 Name        : Filesystem.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#include "shared/sockets.h"
#include "estructurasFS.h"
#include "consolaFS.h"
#include "montarFS.h"

void atenderYama(t_fileSysADM * fileSysCerebro);
void esperarNodos(t_fileSysADM * fileSysCerebro);

int main(int argc, char* argv[]) {

	if( argc > 2){
		puts("Demasiados parametros.");
		return -1;
	}

	if( argc ==  2 && !strcmp( argv[1], "--clean") )
		borrarEstado(PATH_FILESYS_CONFIG);

	 /* en mi resumen de googleDrive de FileSystem, montarFielSys
	  * serian las acciones de Inicia que retorna un puntero a algo
	  * que contenga toda la info necesaria para administrar el File System
	  */

	t_fileSysADM* fileSysCerebro = montarFileSys(PATH_FILESYS_CONFIG);

	esperarNodos(fileSysCerebro);

	/*los siguientes hilos son hechos para que en una terminal se pueda
	 * manejar el filesystem como usuario con la consola mientras el proceso
	 * tambien se encarga de atender al YAMA
	 */
	pthread_t hilo_Consola, hilo_Esclavo;

	pthread_create(&hilo_Consola, NULL, (void*)consola_FileSys, fileSysCerebro);

	pthread_create(&hilo_Esclavo, NULL, (void*)atenderYama, fileSysCerebro);

	pthread_join(hilo_Consola, NULL);
	pthread_join(hilo_Esclavo, NULL);

	desconectarseDe(fileSysCerebro->listener);
	
	return EXIT_SUCCESS;
}

void atenderYama(t_fileSysADM * fileSysCerebro){

}

void esperarNodos(t_fileSysADM * fileSysCerebro){
	fd_set *nodos = malloc(sizeof(fd_set));
	fileSysCerebro->listener = crearSocketEscucha(PUERTO_FS, fileSysCerebro->logger);
	FD_SET(fileSysCerebro->listener, nodos);
	int rta, contador = 0;
	
	do{
		rta = getConnection(nodos, maxSock, fileSysCerebro->listener, mensaje, NULL, fileSysCerebro->pLogger);
		if(mensaje != -1 ){
			contador++;
		}
	}while(contador < fileSysCerebro->cantNodos);
}

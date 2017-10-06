/*
 * datanode.C
 *
 *  Created on: 6/9/2017
 *      Author: utnso
 */
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../../shared/configuraciones.h"
#include "../../shared/protocolo.h"
#include "serializar.h"

#define BLOQUE_SIZE 1048576

int main( int argc, void* argv[]){ /* el primer argumento con el que se llama es el puntero a su config,
									el segundo es el tamaño en bytes del data.bin*/
	t_configuracion_nodo * confDataNode = argv[1];
	t_log * logDataNode = malloc(sizeof(t_log));
	int tTotal = argv[2], i = 0, nro_bloque;
	t_Mensaje tipoMensaje;
	char * payload;

	/*what*/
	int fd = open("data.bin", O_RDWR), socketFS;
	char *data = mmap(NULL, tTotal*getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	socketFS = connectToServer(confDataNode->ip_fs, confDataNode->puerto_fs, logDataNode);

	while( recibirPaquete(socketFS, &tipoMensaje, &payload, logDataNode, "Recibir peticion del FS") != 0){
		tPaquete bloque;
		bloque.type = tipoMensaje;
		deserializar(payload,"%h", &nro_bloque);
		bloque.length = BLOQUE_SIZE;
	
		switch(tipoMensaje){
			case GET_BLOQUE:
				bloque.payload = (char*)(data + nro_bloque*BLOQUE_SIZE);
				for(i=0; i < BLOQUE_SIZE; i += MAX_BUFFER)
					enviarPaquete(socketFS, &bloque, logDataNode, "Envío parcial de bloque al FS");
				break;
			case SET_BLOQUE:
				for(i=0; i < BLOQUE_SIZE; i += MAX_BUFFER)
					recibirPaquete(socketFS, bloque.type, &(bloque.payload), logDataNode, "Recepción parcial de bloque a escribir");
				strcpy(data + nro_bloque*BLOQUE_SIZE, bloque.payload);
				break;
	}
	
	puts("Desconectado del FS");
	
	return 0;
}

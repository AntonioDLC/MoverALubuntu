#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_


#include <stdlib.h>
#include <stdint.h> //para los "int8_t"
#include <string.h>


#define MAX_BUFFER 1024


typedef struct {
	int8_t  type;
	int16_t length;
} __attribute__ ((__packed__)) tHeader;

typedef struct {
	int8_t  type;
	int16_t length;
	char    payload[MAX_BUFFER];
} __attribute__ ((__packed__)) tPaquete;

/*
 * Formato del tipo del paquete:
 * 		[emisor]_[mensaje]
 * Emisor:
 * 		Y : YAMA
 * 		M : MASTER
 * 		W : WORKER
 * 		D : DATANODE
 * 		F : FILESYSTEM
 *
 */
typedef enum {
	/* Mensajes del MASTER */
	M_HANDSHAKE,



	/* Mensajes de YAMA */
	Y_HANDSHAKE,



	/* Mensajes de WORKER */
	W_HANDSHAKE,



	/* Mensajes de DATANODE */
	D_HANDSHAKE,
	ENVIAR_BLOQUE,
	CONFIRM_SET,



	/* Mensajes de FILESYSTEM */
	F_HANDSHAKE,
	GET_BLOQUE,
	SET_BLOQUE,


	/* Mensajes comunes */
	DESCONEXION,

} tMensaje;








#endif /* PROTOCOLO_H_ */

#ifndef _CONSOLA_FS_
#define _CONSOLA_FS_

#include "estructurasFS.h"

#define FORMATEAR "format"
#define REMOVE "rm"
#define OPCION_DIR "-d"
#define OPCION_NODO "-n"
#define OPCION_BLOQUE "-b"
#define RENOMBRAR "rename"
#define MOVER "mv"
#define MOSTRAR_TEXTO "cat"
#define CREAR_DIR "mkdir"
#define COPIAR_DE "cpfrom"
#define COPIAR_A "cpto"
#define COPIAR_BLOQUE "cpblock"
#define MD5 "md5"
#define LISTAR_CONTENIDO_DIR "ls"
#define MOSTRAR_INFO "info"
#define SALIR_DE_FS "salir"

void consola_FileSys(t_fileSysADM * fileSysCerebro);
void atenderComando(char ** argv, t_fileSysADM * fileSysCerebro);
char ** obtenerParametros( char * comando);
void liberarArgv(char ** argv);

#endif

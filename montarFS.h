#ifndef _MONTAR_FS_
#define _MONTAR_FS_

#include <commons/config.h>
#include <commons/collections/list.h>
#include "estructurasFS.h"

t_fileSysADM *montarFileSys(char*path);
void montarArchivos(char *archFolder, fileSysADM *fileSysCerebro);
void montarDirectorios(char *pathDir, fileSysADM *fileSysCerebro);
void montarNodos(t_config *nodoConf, fileSysADM *fileSysCerebro);
t_nodo *crearNodo(char *id, int cantBloquesTotal, int cantBloquesLibres);
t_list *obtenerBloques(t_config *fileInfo);
char * enHome(char *relativePath);

#endif

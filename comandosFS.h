#ifndef _COMANDOS_FS_
#define _COMANDOS_FS_

#include "estructurasFS.h"

void enviarAlNodoI(t_list *nodos, int i, t_log *pLogger);
void enviarANodos(char *yamaDest, char *data, int tTotal, fileSysADM *fileSysCerebro);
void copiarAYamaFs(char *yamaDest, char *origen, fileSysADM* fileSysCerebro]);
void borrarEstado(char*path);

#endif

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "montarFS.h"

t_fileSysADM * montarFileSys(char* path){
	t_fileSysADM* cerebroDelFS = malloc(sizeof(fileSysADM));
	t_config *fileSysConfig = config_create(path);

	char *pathArchivos = enHome(config_get_string_value(fileSysConfig, "PATH_ARCHIVOS"));
	char *pathNodos = enHome(config_get_string_value(fileSysConfig, "PATH_NODOS"));
	char *pathDirectorios = enHome(config_get_string_value(fileSysConfig, "PATH_DIRECTORIOS"));

	t_config *nodosConfig = config_create(pathNodos);

	montarDirectorios(pathDirectorios, fileSysCerebro);
	montarArchivos(pathArchivos, fileSysCerebro);
	montarNodos(nodosConfig, fileSysCerebro);
	// extraer info de configs y guardar todo en el cerebro
	
	free(pathArchivos);
	free(pathNodos);

	return cerebroDelFS;
}

char * enHome(char * relPath){
	char* pathHome = getenv("HOME");
	char *finalPath = calloc(strlen(relPath)+strlen(pathHome)+1,1);

	strcpy(finalPath, pathHome);
	strcat(finalPath, relPath);

	return finalPath;

}

void montarNodos(t_config *nodoConf, fileSysADM *fileSysCerebro){
	char ** idNodos = config_get_array_value(nodoConf,"NODOS");
	int i = 0;
	t_list nodosCargados = fileSysCerebro->nodos;
	t_nodo *nodoACargar;
	char *keyNodo = malloc(20);
	while(idNodos[i]] != NULL){
		strcpy(keyNodo, idNodos[i]]);
		nodoACargar = crearNodo(idNodos[i], config_get_int_value(nodoConf,strcat(keyNodo,"Total")), config_get_int_value(nodoConf, strcat(keyNodo,"Libre")));
		list_add(nodosCargados, nodoACargar);
		fileSysCerebro->cantNodos++;
	}
	fileSysCerebro->size = config_get_int_value(nodoConf,"TAMANIO");
	fileSysCerebro->espacioLibreTotal = config_get_int_value(nodoConf,"LIBRE");
	free(keyNodo);
}

t_nodo *crearNodo(char *id, int cantBloquesTotal, int cantBloquesLibres){
	t_nodo *pNodo = malloc(sizeof(t_nodo));
	
	pNodo->id = malloc(strlen(id)+1);
	strcpy(pNodo->id,id);
	
	pNodo->cantBloquesTotal = cantBloquesTotal;
	pNodo->cantBloquesLibres = cantBloquesLibres;
	pNodo->socketFS = -1;
	
	return pNodo;
}

void montarDirectorios(char *pathDir, fileSysADM *fileSysCerebro){
	FILE* fDir = fopen(pathDir,"r");
	t_list dirs = fileSysCerebro->directorios;
	fileSysCerebro->cantDir = 0;
	
	while(!feof(fDir)){
		t_directorio dir;
		fread(&dir, sizeof(dir), 1, fDir);
		list_add(dirs, dir);
		fileSysCerebro->cantDir++;
	}
}

void montarArchivos(char *archFolder, fileSysADM *fileSysCerebro){
	int i = 1;
	int longFoldPath = strlen(archFolder);
	char *pathCompleto = malloc(longFoldPath+100);
	strcpy(pathCompleto, archFolder);
	char *pathParcial = pathCompleto + longFoldPath;
	t_list *archivos = fileSysCerebro->archivos;
	t_infoArchivo *arch = malloc(sizeof(t_infoArchivo));
	DIR *dp;
	struct dirent *ep;
	t_config *fileInfo;
	
	while( i <= fileSysCerebro->cantDir){
		sprintf(pathParcial, "/%d", i);
		dp = opendir(pathCompleto);
		if(dp!=NULL){
			while(ep = readdir(dp)){
				arch->indexDirPadre = i;
				arch->nombre = malloc(strlen(ep->d_name));
				strcpy(arch->nombre, ep->d_name);
				strcpy(pathParcial+strlen(pathParcial), arch->nombre);
				fileInfo = config_create(pathCompleto);
				arch->size = config_get_int_value(fileInfo, "TAMANIO");
				arch->tipo = config_get_int_value(fileInfo, "TIPO");
				arch->estado = DISPONIBLE;
				arch->bloques = obtenerBloques(fileInfo);
				closedir(dp);
				list_add(archivos, arch);
			}
		}else
			return -1;
	}
	
	free(archInf);
	free(pathCompleto);
}

t_list *obtenerBloques(t_config *fileInfo){
	t_list *bloques = list_create();
	t_bloque *bloque;
	char * keyBloque = malloc(100), **dupla;
	int i = 0, j = 0, offset;
	
	offset = sprintf(keyBloque, "%s%d", "BLOQUE", i);
	sprintf(keyBloque+offset, "%s%d","COPIA", j);
	while(config_has_property(fileInfo, keyBloque)){
		while( config_has_property(fileInfo, keyBloque)){
			bloque = malloc(sizeof(t_bloque));
			
			bloque->posEnArch = i;
			dupla = config_get_array_value(fileInfo, keyBloque);
			bloque->id = malloc(strlen(dupla[0]));
			strcpy(bloque->id, dupla[0]);
			bloque->posEnNodo = dupla[1];

			list_add(bloques, bloque);

			j++;
			sprintf(keyBloque+offset, "%s%d","COPIA", j);
		}
		sprintf(keyBloque+offset, "%s", "BYTES");
		
		while(j >= 0){
			bloque = list_get(bloques, i+j); /* ESTO DEPENDE DEL ORDEN EN QUE SE GUARDARON LOS BLOQUES EN 
												EL WHILE DE MAS ARRIBA */
			bloque->finBloque = config_get_int_value(fileInfo, keyBloque);
		}
		
		i++;
		offset = sprintf(keyBloque, "%s%d", "BLOQUE", i);
	}
	
	return bloques;
}

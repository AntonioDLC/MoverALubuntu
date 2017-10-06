#ifndef _STRUCTS_FS_
#define _STRUCTS_FS_

#define PUERTO_FS 8080
#define PATH_FILESYS_CONFIG "fileSys.conf"

typedef char* t_nombreNodo;
typedef enum{TEXTO, BINARIO} t_tipoArchivo;
typedef enum{DISPONIBLE,BLOQUEADO} t_estado;

typedef struct t_bloque{
			int posEnArch;
			t_nombreNodo id;
			int posEnNodo;
			int finBloque;
		}t_bloque;

typedef struct t_infoArchivo{ /* ARCHIVOS */
			char* nombre;
			int size;
			t_tipoArchivo tipo;
			int indexDirPadre;
			t_estado estado;
			t_list *bloques;
		}t_infoArchivo;

typedef struct t_directorio{ /* DIRECTORIOS */
			int index;
			char nombre[256];
			int padre;
		}t_directorio;

typedef struct t_nodo{ /* NODOS */
			char * id;
			int cantBloquesTotal;
			int cantBloquesLibres;
			int socketFS;
		}t_nodo;

typedef struct t_fileSysADM{
			t_list *directorios; /* "TABLA" DE DIRECTORIOS */
			int cantDir;
			t_list *archivos;
			t_list *nodos;
			int cantNodos;
			int espacioLibreTotal;
			t_log *pLogger;
			int listener;
			int tamanio;
		}t_fileSysADM;

#endif

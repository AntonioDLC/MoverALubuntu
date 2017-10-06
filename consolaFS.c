#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#include "comandosFS.h"
#include "consolaFS.h"

void consola_FileSys(t_fileSysADM * fileSysCerebro){
	char *comando = malloc(1), *pesp, **argv = malloc(sizeof(char*));
	
	*argv = NULL;

	do{
		free(comando);
		liberarArgv(argv);

		comando = readline("yamafs:");

		argv = obtenerParametros(comando);

		atenderComando(argv, fileSysCerebro); /* argv[0] pasa a almacenar una copia del comando propiamente dicho*/

	}while(strcmp(SALIR_DE_FS, argv[0]));
}

void liberarArgv(char ** argv){
	int i = 0;

	while( argv[i] )
		free(argv[i++]);

	free(argv);
}

void atenderComando(char ** argv, t_fileSysADM * fileSysCerebro){
	char* comando = argv[0];

		printf("Hacé de cuenta que ");
	if(!strcmp(comando,FORMATEAR)){
		printf("formateé el FileSytem");
	}else if(!strcmp(comando,REMOVE )){
		if( argv[2] == NULL){
			printf("borré el archivo %s", argv[1]);
		}else if(!strcmp(argv[1],OPCION_DIR)){
			printf("borré el directorio %s solo si estaba vacío", argv[2]);
		}else if(!strcmp(argv[1],OPCION_NODO)){
			printf("eliminé el nodo %s solo si no estaba trabajando", argv[2]);
		}else if(!strcmp(argv[1], OPCION_BLOQUE)){
			printf("eliminé la copia %d del bloque nro %d del archivo %s", atoi(argv[4]), atoi(argv[3]), argv[2]);
		}
	}else if(!strcmp(comando,RENOMBRAR )){
		printf("cambié el nombre de %s por %s", argv[1], argv[2]);
	}else if(!strcmp(comando,MOVER )){
		printf("moví el archivo de %s a %s", argv[1], argv[2]);
	}else if(!strcmp(comando,MOSTRAR_TEXTO )){
		printf("te acabo de mostrar el contenido de %s", argv[1]);
	}else if(!strcmp(comando,CREAR_DIR )){
		printf("creé el directorio %s", argv[1]);
	}else if(!strcmp(comando,COPIAR_DE )){
		printf("copié el archivo de %s a %s", argv[1], argv[2]);
	}else if(!strcmp(comando,COPIAR_A )){
		copiarAYamaFs(argv[2], argv[1], fileSysCerebro]);
		printf("copié el archivo de %s a %s", argv[2], argv[1]);
	}else if(!strcmp(comando,COPIAR_BLOQUE )){
		printf("dupliqué el bloque %d, del archivo %s, en el nodo %s", atoi(argv[2]), argv[1], argv[3]);
	}else if(!strcmp(comando,MD5 )){
		printf("hice... MD5... lo que sea que eso implique.\nO sea posta, ¿qué demonios es el MD5?");
	}else if(!strcmp(comando,LISTAR_CONTENIDO_DIR )){
		printf("listé el contenido del directorio %s", argv[1]?argv[1]:"actual");
	}else if(!strcmp(comando,MOSTRAR_INFO)){
		printf("te mostré el tamaño, los bloques y la ubicación del archivo %s", argv[1]);
	}else
		printf("... ehhh. No tengo idea de lo que me pediste.");
	putchar('\n');
}

char ** obtenerParametros( char * comando){
	char **argv = malloc(sizeof(char*));
	char *c = NULL, *cprev = comando;
	int i = 0, lpar;

	while( (c = strchr(cprev,' ')) != NULL){
		lpar = (int)(c-cprev);
		argv[i] = calloc(sizeof(char),lpar+1);
		strncpy(argv[i],cprev, lpar);
		cprev = ++c; i++;
		argv = realloc(argv,sizeof(char*)*(i+1));
	}
	argv[i] = malloc(strlen(cprev)+1);
	strcpy(argv[i],cprev); // copia el último parámetro (el único al que no le sigue un espacio)
	argv = realloc(argv,sizeof(char*)*(i+2));
	argv[i+1] = NULL; //el último puntero lo setea en NULL

	return argv;
}

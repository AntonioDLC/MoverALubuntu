#ifndef CONFIGURACIONES_H_
#define CONFIGURACIONES_H_

#define PATH_CONFIG_MASTER "../Master/src/config.cfg"
#define PATH_CONFIG_YAMA "../YAMA/src/config.cfg"
#define PATH_CONFIG_NODO "../Nodo/src/conf.cfg"
#include <commons/config.h>


typedef struct{
	int puerto_yama;
	char *ip_yama;
	int puerto_worker;
	char *ip_worker;
}t_configuracion_master;

typedef struct{
	int puerto_fs;
	char *ip_fs;
	int retardo_planificacion;
	char *algoritmo_planificacion;
}t_configuracion_yama;

typedef struct{
	char *ip_fs;
	int puerto_fs;
	char *nombre_nodo;
	int puerto_datanode;
	int puerto_worker;
	char *path_databin;

}t_configuracion_nodo;


t_configuracion_master *obtener_configuracion_master(t_config *config);
t_configuracion_yama *obtener_configuracion_yama(t_config *config);
t_configuracion_nodo *obtener_configuracion_nodo(t_config *config);


#endif /* CONFIGURACIONES_H_ */

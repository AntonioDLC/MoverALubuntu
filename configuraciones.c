/*
 * configuraciones.c
 *
 *  Created on: 14/8/2017
 *      Author: utnso
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include "configuraciones.h"




t_configuracion_master *obtener_configuracion_master(t_config *config){

	t_configuracion_master *configuracion=malloc(sizeof(t_configuracion_master));

	if (config_has_property(config,"IP_YAMA")){
		configuracion->ip_yama=string_duplicate(config_get_string_value(config,"IP_YAMA"));

	}

	if (config_has_property(config,"PUERTO_YAMA")) {
		configuracion->puerto_yama = config_get_int_value(config, "PUERTO_YAMA");
		}


config_destroy(config);
return configuracion;
}

t_configuracion_yama *obtener_configuracion_yama(t_config *config){

	t_configuracion_yama *configuracion=malloc(sizeof(t_configuracion_master));
	if (config_has_property(config,"FS_PUERTO")) {
			configuracion->puerto_fs = config_get_int_value(config, "FS_PUERTO");

		}

	if (config_has_property(config,"FS_IP")){
		configuracion->ip_fs=string_duplicate(config_get_string_value(config,"FS_IP"));

	}


	if (config_has_property(config,"RETARDO_PLANIFICACION")) {
		configuracion->retardo_planificacion = config_get_int_value(config, "RETARDO_PLANIFICACION");
		}

	if (config_has_property(config,"ALGORITMO_BALANCEO")){
		configuracion->algoritmo_planificacion=string_duplicate(config_get_string_value(config,"ALGORITMO_BALANCEO"));

		}
	config_destroy(config);
	return configuracion;
}

	t_configuracion_nodo*obtener_configuracion_nodo(t_config *config){

		t_configuracion_nodo *configuracion=malloc(sizeof(t_configuracion_master));
		if (config_has_property(config,"PUERTO_FILESYSTEM")) {
			configuracion->puerto_fs = config_get_int_value(config, "PUERTO_FILESYSTEM");

			}

		if (config_has_property(config,"IP_FILESYSTEM")){
			configuracion->ip_fs=string_duplicate(config_get_string_value(config,"IP_FILESYSTEM"));

		}
		if (config_has_property(config,"NOMBRE_NODO")){
			configuracion->nombre_nodo=string_duplicate(config_get_string_value(config,"ALGORITMO_BALANCEO"));

			}


		if (config_has_property(config,"PUERTO_DATANODE")) {
						configuracion->puerto_datanode = config_get_int_value(config, "PUERTO_DATANODE");

					}
		if (config_has_property(config,"PUERTO_WORKER")) {
			configuracion->puerto_worker= config_get_int_value(config, "PUERTO_WORKER");

			}

		if (config_has_property(config,"PATH_DATABIN")){
			configuracion->path_databin=string_duplicate(config_get_string_value(config,"PATH_DATABIN"));

		}

config_destroy(config);
return configuracion;
}

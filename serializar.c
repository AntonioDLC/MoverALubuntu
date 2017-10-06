#include "serializar.h"

int serializar(void* buffer, const char* format, ...){
	va_list objs;
	int i = 0, buffIndex = 0;
	va_start(objs, format);

	while(format[i] != '\0'){
		if( format[i] == '%'){
			i++;
			if( format[i] == 'h'){
					short obj = (short)va_arg( objs, int );
					obj = htons(obj);
					memcpy(buffer+buffIndex, &obj, sizeof(obj));
					buffIndex+= sizeof(short);
			}else if( format[i] == 'c' ){
					char obj = (char)va_arg(objs, int);
					memcpy(buffer+buffIndex, &obj, sizeof(obj));
					buffIndex+= sizeof(char);
			}else if(format[i] == 's'){
					char *obj = va_arg(objs, char*);
					int longStr = strlen(obj);
					memcpy(buffer+buffIndex,obj, longStr+1);
					buffIndex+= longStr+1;
			}else{
					va_end(objs);
					return -1;
			} /* FIN DE DETECCION DE CARACTER POST-'%' */
		} /* FIN DEL IF '%' */

		i++;
	} /* FIN DEL WHILE RECORRE-CADENA */

	va_end(objs);

	return buffIndex;
}

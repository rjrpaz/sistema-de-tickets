#include <shadow.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "conf.h"

char *getenv();

int main()
{
    char *http_referer, *usuario, *password, *fechaapertura, *horaapertura;
    char *tipodispositivo, *tecnico, *descripcion, *clienteID;
    char *command;

    uncgi();

    http_referer = getenv("HTTP_REFERER");
    usuario = getenv("WWW_usuario");
    password = getenv("WWW_password");
    clienteID = getenv("WWW_clienteID");
    fechaapertura = getenv("WWW_fechaapertura");
    horaapertura = getenv("WWW_horaapertura");
    tipodispositivo = getenv("WWW_tipodispositivo");
    tecnico = getenv("WWW_tecnico");
    descripcion = getenv("WWW_descripcion");

    /*********************\
    * Chequeo del referer *
    \*********************/


    /********************\
    * Chequeo de Usuario *
    \********************/
/*
    if ((chequeo_pass("root", rpass)) != 0)
    {
		html_error("Password de administraci&oacute;n incorrecto");
    }
*/


    /*********************************\
    * Chequeo de la Fecha de Apertura *
    \*********************************/

	if ((fechaapertura == NULL) || ((strcmp(fechaapertura,"")) == 0))
	{
		html_error("No ingres&oacute; la fecha de apertura del Ticket. Este es un dato necesario ...");
	}


    /********************************\
    * Chequeo de la Hora de Apertura *
    \********************************/

	if ((horaapertura == NULL) || ((strcmp(horaapertura,"")) == 0))
	{
		html_error("No ingres&oacute; la hora de apertura del Ticket. Este es un dato necesario ...");
	}


    /****************************************\
    * Chequeo de la Descripcion del Problema *
    \****************************************/

	if ((descripcion == NULL) || ((strcmp(descripcion,"")) == 0) || ((strcmp(descripcion,"Ingrese aquí una descripción del problema")) == 0))
	{
		html_error("No ingres&oacute; la descripci&oacute;n del problema al cual este Ticket hace Referencia,<BR>o bien no modific&oacute; el mensaje por defecto.<BR>Este es un dato necesario ...");
	}


    /************************************************\
    * Crea una nueva entrada en la tabla de Clientes *
    \************************************************/

	command = malloc(strlen("/root/tickets/AltaTicket ") + strlen(clienteID) + strlen(tipodispositivo) + strlen(descripcion) + strlen(fechaapertura) + strlen(horaapertura) + strlen(tecnico) + 33);
	sprintf(command,"/root/tickets/AltaTicket -i %s -t \"%s\" -d \"%s\" -f \"%s\" -H \"%s\" -T \"%s\"", clienteID, tipodispositivo, descripcion, fechaapertura, horaapertura, tecnico);
	printf("Comando: %s\n", command);
	system(command);
	free(command);

    /*****************************************\
    * Redirecciona para dar de alta el Ticket *
    \*****************************************/

    printf("Location: apertura3a.html?usuario=%s&password=%s\n\n", usuario, password);
	exit (0);	
}

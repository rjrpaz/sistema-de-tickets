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
    char *http_referer, *usuario, *password, *apellido, *nombre, *direccion;
    char *codigopostal, *telefono, *fax, *email, *ciudad, *provincia, *contacto;
    char *command;

    uncgi();

    http_referer = getenv("HTTP_REFERER");
    usuario = getenv("WWW_usuario");
    password = getenv("WWW_password");
    apellido = getenv("WWW_apellido");
    nombre = getenv("WWW_nombre");
    direccion = getenv("WWW_direccion");
    codigopostal = getenv("WWW_codigopostal");
    telefono = getenv("WWW_telefono");
    fax = getenv("WWW_fax");
    email = getenv("WWW_email");
    ciudad = getenv("WWW_ciudad");
    provincia = getenv("WWW_provincia");
    contacto = getenv("WWW_contacto");

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


    /************************************************\
    * Crea una nueva entrada en la tabla de Clientes *
    \************************************************/

	command = malloc(strlen("/root/tickets/AltaCliente ") + strlen(apellido) + strlen(nombre) + strlen(direccion) + strlen(codigopostal) + strlen(telefono) + strlen(fax) + strlen(email) + strlen(ciudad) + strlen(provincia) + 60);
	sprintf(command,"/root/tickets/AltaCliente -a \"%s\" -n \"%s\"", apellido, nombre);
	if ((strcmp(direccion,"")) != 0)
	{
		sprintf(command,"%s -d \"%s\"", command, direccion);
	}
	if ((strcmp(codigopostal,"")) != 0)
	{
		sprintf(command,"%s -c \"%s\"", command, codigopostal);
	}
	if ((strcmp(telefono,"")) != 0)
	{
		sprintf(command,"%s -t \"%s\"", command, telefono);
	}
	if ((strcmp(fax,"")) != 0)
	{
		sprintf(command,"%s -f \"%s\"", command, fax);
	}
	if ((strcmp(email,"")) != 0)
	{
		sprintf(command,"%s -e %s", command, email);
	}
	if ((strcmp(ciudad,"")) != 0)
	{
		sprintf(command,"%s -C \"%s\"", command, ciudad);
	}
	if ((strcmp(provincia,"")) != 0)
	{
		sprintf(command,"%s -p \"%s\"", command, provincia);
	}
	system(command);
	free(command);

    /*****************************************\
    * Redirecciona para dar de alta el Ticket *
    \*****************************************/

    printf("Location: apertura2a.html?apellido=%s&nombre=%s\n\n", apellido, nombre);
	exit (0);	
}

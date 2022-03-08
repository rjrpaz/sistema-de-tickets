#include <shadow.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "conf.h"
#include "db.h"

char *getenv();

int main()
{
    char *http_referer, *usuario, *password, *apellido, *nombre, *command;
	char *dispositivos, *tecnicos, buffer[256];
	int ClienteID, con, i;
	time_t hora;
	struct tm *hora_texto;
	cliente_reg cliente;
	cliente_reg *ptr_cliente;

    uncgi();

    http_referer = getenv("HTTP_REFERER");
    usuario = getenv("WWW_usuario");
    password = getenv("WWW_password");
    apellido = getenv("WWW_apellido");
    nombre = getenv("WWW_nombre");

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

	
    /************************\
    * Obtiene ID del Cliente *
    \************************/

    /**********************************\
    * Forma para dar de alta el ticket *
    \**********************************/

    printf("Content-type: text/html\n\n");
    puts("<HTML>");
    puts("<HEAD>\n<TITLE>Apertura Ticket - Paso 3 de 4</TITLE>\n</HEAD>");
    puts("<BODY>");
    puts("Paso 3 de 4");
    puts("<HR>");

    puts("Debe almacenar alg&uacute;n <B>driver</B> a la Base de Datos?:<BR>");

    puts("<FORM METHOD=GET ACTION=\"apertura3b.html\">");
    printf("<INPUT NAME=\"usuario\" VALUE=\"%s\" TYPE=\"hidden\">\n",usuario);
    printf("<INPUT NAME=\"password\" VALUE=\"%s\" TYPE=\"hidden\">\n",password);

	puts("<TABLE>");
    puts("<TR><TD><INPUT TYPE=\"submit\" NAME=\"opcion\" VALUE=\"Si\"></TD>");
    puts("<TD><INPUT TYPE=\"submit\" NAME=\"opcion\" VALUE=\"No\"></TD></TR>");
	puts("</TABLE>");
	puts("</FORM>");
    puts("</HTML>");
}

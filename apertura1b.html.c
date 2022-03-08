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
    cliente_reg cliente;
    cliente_reg *ptr_cliente;

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

    /*********************\
    * Chequeo de Apellido *
    \*********************/

	if ((apellido == NULL) || ((strcmp(apellido,"")) == 0))
	{
		html_error("No ingres&oacute; el apellido. Este es un dato necesario ...");
	}


    /********************\
    * Chequeo del Nombre *
    \********************/

	if ((nombre == NULL) || ((strcmp(nombre,"")) == 0))
	{
		html_error("No ingres&oacute; el nombre. Este es un dato necesario ...");
	}

		
    printf("Content-type: text/html\n\n");
    puts("<HTML>");
    puts("<HEAD>\n<TITLE>Apertura Ticket - Paso 1 de 4</TITLE>\n</HEAD>");
    puts("<BODY>");
    puts("Paso 1 de 4");
    puts("<HR>");

    /*******************************************\
    * Chequea si el cliente existia previamente *
    \*******************************************/

	ptr_cliente = &cliente;

	if ((getclientebyname(nombre, apellido, ptr_cliente)) != 0)
	{
    	puts("<H1>Atenci&oacute;n:</H1>");
    	puts("Ya existe un Cliente con ese Nombre, y estos son sus datos");
    	puts("<TABLE>");

    	printf("<TR><TD>Apellido: </TD><TD>%s</TD></TR>", cliente.Apellido);
    	printf("<TR><TD>Nombre: </TD><TD>%s</TD></TR>", cliente.Nombre);
    	printf("<TR><TD>ID: </TD><TD>%d</TD></TR>", cliente.ClienteID);
    	printf("<TR><TD>Direcci&oacute;n: </TD><TD>%s</TD></TR>", cliente.Direccion);
    	printf("<TR><TD>C&oacute;digo Postal: </TD><TD>%s</TD></TR>", cliente.CodigoPostal);
    	printf("<TR><TD>Tel&eacute;fono: </TD><TD>%s</TD></TR>", cliente.Telefono);
    	printf("<TR><TD>FAX: </TD><TD>%s</TD></TR>", cliente.Fax);
    	printf("<TR><TD>E-mail: </TD><TD>%s</TD></TR>", cliente.Email);
    	printf("<TR><TD>Ciudad: </TD><TD>%s</TD></TR>", cliente.Ciudad);
    	printf("<TR><TD>Provincia: </TD><TD>%s</TD></TR>", cliente.Provincia);

		puts("</TABLE>");
	}
	else
	{
	    /**************************************\
    	* Confirmacion de los datos ingresados *
    	\**************************************/

    	puts("<H1>Confirmaci&oacute;n de los Datos Ingresados</H1>\n");
    	puts("(Si estos datos no son correctos, vuelva hacia atr&aacute;s con su navegador)\n");
    	puts("<H2>Estos son los datos ingresados: </H2>\n");
	
    	puts("<FORM METHOD=GET ACTION=\"apertura1c.html\">");
    	printf("<INPUT NAME=\"usuario\" VALUE=\"%s\" TYPE=\"hidden\">\n", usuario);
    	printf("<INPUT NAME=\"password\" VALUE=\"%s\" TYPE=\"hidden\">\n", password);
   		printf("<INPUT NAME=\"apellido\" VALUE=\"%s\" TYPE=\"hidden\">\n", apellido);
    	printf("<INPUT NAME=\"nombre\" VALUE=\"%s\" TYPE=\"hidden\">\n", nombre);
    	printf("<INPUT NAME=\"direccion\" VALUE=\"%s\" TYPE=\"hidden\">\n", direccion);
    	printf("<INPUT NAME=\"codigopostal\" VALUE=\"%s\" TYPE=\"hidden\">\n", codigopostal);
    	printf("<INPUT NAME=\"telefono\" VALUE=\"%s\" TYPE=\"hidden\">\n", telefono);
    	printf("<INPUT NAME=\"fax\" VALUE=\"%s\" TYPE=\"hidden\">\n", fax);
    	printf("<INPUT NAME=\"email\" VALUE=\"%s\" TYPE=\"hidden\">\n", email);
    	printf("<INPUT NAME=\"ciudad\" VALUE=\"%s\" TYPE=\"hidden\">\n", ciudad);
    	printf("<INPUT NAME=\"provincia\" VALUE=\"%s\" TYPE=\"hidden\">\n", provincia);
    	printf("<INPUT NAME=\"contacto\" VALUE=\"%s\" TYPE=\"hidden\">\n", contacto);

		puts("<TABLE>\n");
    	printf("<TR><TD>Apellido: </TD><TD><B>%s</B></TD></TR>\n", apellido);
    	printf("<TR><TD>Nombre: </TD><TD><B>%s</B></TD></TR>\n", nombre);
    	printf("<TR><TD>Direcci&oacute;n: </TD><TD><B>%s</B></TD></TR>\n", direccion);
    	printf("<TR><TD>C&oacute;digo Postal: </TD><TD><B>%s</B></TD></TR>\n", codigopostal);
    	printf("<TR><TD>Tel&eacute;fono: </TD><TD><B>%s</B></TD></TR>\n", telefono);
    	printf("<TR><TD>FAX: </TD><TD><B>%s</B></TD></TR>\n", fax);
    	printf("<TR><TD>E-mail: </TD><TD><B>%s</B></TD></TR>\n", email);
    	printf("<TR><TD>Ciudad: </TD><TD><B>%s</B></TD></TR>\n", ciudad);
    	printf("<TR><TD>Provincia: </TD><TD><B>%s</B></TD></TR>\n", provincia);
    	printf("<TR><TD>Apellido del Contacto: </TD><TD><B>%s</B></TD></TR>\n", contacto);

    	puts("<TR><TD COLSPAN=2><INPUT TYPE=\"submit\" VALUE=\"Confirmar\"></TD></TR>\n");
		puts("</TABLE>\n");
		puts("</FORM>\n");
	}
    puts("</BODY>");
    puts("</HTML>");

}

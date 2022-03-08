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
    char *http_referer, *usuario, *password;

    uncgi();

    http_referer = getenv("HTTP_REFERER");
    usuario = getenv("WWW_usuario");
    password = getenv("WWW_password");

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
    /*************************************\
    * Busqueda de un cliente ya existente *
    \*************************************/

    printf("Content-type: text/html\n\n");
    puts("<HTML>");
    puts("<HEAD>\n<TITLE>Apertura Ticket - Paso 1 de 4</TITLE>\n</HEAD>");
    puts("<BODY>");
    puts("Paso 1 de 4<BR>");
    puts("<HR>");

    puts("<H1>Identificar Cliente</H1>");
    puts("Si el cliente ya existe, realice una b&uacute;squeda: <BR>");

    puts("<FORM METHOD=GET ACTION=\"busqueda.html\">");
    puts("<TABLE>\n<TR>");
    puts("<TD><INPUT TYPE=\"text\" NAME=\"query\" SIZE=\"40\"></TD>");
    puts("<TD><SELECT NAME=\"campo\" SIZE=\"1\">");
	puts("<OPTION SELECTED>Nombre");
	puts("<OPTION>Direcci&oacute;n");
	puts("</SELECT>");
	puts("</TD>");
    puts("</TR>");
    puts("<TR>");
    puts("<TD COLSPAN=2><INPUT TYPE=\"submit\" VALUE=\"Buscar\">");
    puts("<INPUT TYPE=\"reset\" VALUE=\"Limpiar\"></TD></TR>");
	puts("</TABLE>");
	puts("</FORM>");

    /*****************************************************\
    * Form para el ingreso de los datos del nuevo cliente *
    \*****************************************************/

    puts("<HR>");
    puts("Si el cliente no existe, ingrese los datos: <BR>");
    puts("<H2>Datos del Cliente:</H2>");
	puts("(Los datos marcados con (*) no deben dejarse en blanco)");

    puts("<FORM METHOD=GET ACTION=\"apertura1b.html\">");
    printf("<INPUT NAME=\"usuario\" SIZE=\"16\" VALUE=\"%s\" TYPE=\"hidden\" >\n",usuario);
    printf("<INPUT NAME=\"password\" SIZE=\"16\" VALUE=\"%s\" TYPE=\"hidden\" >\n",password);
	puts("<TABLE>");
    puts("<TR><TD>(*) Apellido: </TD><TD><INPUT NAME=\"apellido\" SIZE=\"40\"></TD></TR>");
    puts("<TR><TD>(*) Nombre: </TD><TD><INPUT NAME=\"nombre\" SIZE=\"60\"></TD></TR>");
    puts("<TR><TD>Direcci&oacute;n: </TD><TD><INPUT NAME=\"direccion\" SIZE=\"60\"></TD></TR>");
    puts("<TR><TD>C&oacute;digo Postal: </TD><TD><INPUT NAME=\"codigopostal\" SIZE=\"10\"></TD></TR>");
    puts("<TR><TD>Tel&eacute;fono: </TD><TD><INPUT NAME=\"telefono\" SIZE=\"16\"></TD></TR>");
    puts("<TR><TD>FAX: </TD><TD><INPUT NAME=\"fax\" SIZE=\"16\"></TD></TR>");
    puts("<TR><TD>E-mail: </TD><TD><INPUT NAME=\"email\" SIZE=\"60\"></TD></TR>");
    puts("<TR><TD>Ciudad: </TD><TD><INPUT NAME=\"ciudad\" SIZE=\"60\" VALUE=\"C&oacute;rdoba\"></TD></TR>");
    puts("<TR><TD>Provincia: </TD><TD><INPUT NAME=\"provincia\" SIZE=\"60\" VALUE=\"C&oacute;rdoba\"></TD></TR>");
    puts("<TR><TD>Apellido del Contacto: </TD><TD><INPUT NAME=\"contacto\" SIZE=\"40\"></TD></TR>");

    puts("<TR><TD><INPUT TYPE=\"submit\" VALUE=\"Agregar\"></TD>");
    puts("<TD><INPUT TYPE=\"reset\" VALUE=\"Limpiar\"></TD></TR>");
	puts("</TABLE>");
	puts("</FORM>");
	puts("</BODY>");

    puts("</HTML>");
}

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
    puts("Paso 1 de 4");
    puts("<HR>");

    puts("<H1>Identificar Cliente</H1>\n");
    puts("Si el cliente ya existe, realice una b&uacute;squeda: <BR>\n");

    puts("<FORM METHOD=GET ACTION=\"busqueda.html\">");
    puts("<TABLE>\n<TR>\n");
    puts("<TD><INPUT TYPE=\"text\" NAME=\"query\" SIZE=\"40\"></TD>\n");
    puts("<TD><SELECT NAME=\"campo\" SIZE=\"1\">\n");
	puts("<OPTION SELECTED>Nombre\n");
	puts("<OPTION>Direcci&oacute;n\n");
	puts("</SELECT>\n");
	puts("</TD>\n");
    puts("</TR>\n");
    puts("<TR>\n");
    puts("<TD><INPUT TYPE=\"submit\" VALUE=\"Buscar\">\n");
    puts("<INPUT TYPE=\"reset\" VALUE=\"Limpiar\"></TD>\n");
    puts("</TR>\n");
	puts("</TABLE>\n");
	puts("</FORM>\n");

    /*****************************************************\
    * Form para el ingreso de los datos del nuevo cliente *
    \*****************************************************/

    puts("<HR>");
    puts("Si el cliente no existe, ingrese los datos: <BR>\n");
    puts("<H2>Datos del Cliente:</H2>");

    puts("<FORM METHOD=GET ACTION=\"apertura2de4.html\">");
    printf("<INPUT NAME=\"usuario\" SIZE=\"16\" VALUE=\"%s\" TYPE=\"hidden\" >\n",usuario);
    printf("<INPUT NAME=\"password\" SIZE=\"16\" VALUE=\"%s\" TYPE=\"hidden\" >\n",password);
	puts("<TABLE>\n");
    puts("<TR><TD>Apellido: </TD><TD><INPUT NAME=\"apellido\" SIZE=\"40\"></TD></TR>\n");
    puts("<TR><TD>Nombre: </TD><TD><INPUT NAME=\"nombre\" SIZE=\"60\"></TD></TR>\n");
    puts("<TR><TD>Direcci&oacute;n: </TD><TD><INPUT NAME=\"direccion\" SIZE=\"60\"></TD></TR>\n");
    puts("<TR><TD>C&oacute;digo Postal: </TD><TD><INPUT NAME=\"codigopostal\" SIZE=\"10\"></TD></TR>\n");
    puts("<TR><TD>Tel&eacute;fono: </TD><TD><INPUT NAME=\"telefono\" SIZE=\"16\"></TD></TR>\n");
    puts("<TR><TD>FAX: </TD><TD><INPUT NAME=\"fax\" SIZE=\"16\"></TD></TR>\n");
    puts("<TR><TD>E-mail: </TD><TD><INPUT NAME=\"email\" SIZE=\"60\"></TD></TR>\n");
    puts("<TR><TD>Ciudad: </TD><TD><INPUT NAME=\"ciudad\" SIZE=\"60\" VALUE=\"C&oacute;rdoba\"></TD></TR>\n");
    puts("<TR><TD>Provincia: </TD><TD><INPUT NAME=\"provincia\" SIZE=\"60\" VALUE=\"C&oacute;rdoba\"></TD></TR>\n");
    puts("<TR><TD>Apellido del Contacto: </TD><TD><INPUT NAME=\"contacto\" SIZE=\"40\"></TD></TR>\n");

    puts("<TD><INPUT TYPE=\"submit\" VALUE=\"Agregar\"></TD>\n");
    puts("<TD><INPUT TYPE=\"reset\" VALUE=\"Limpiar\"></TD>\n");
	puts("</TABLE>\n");
	puts("</FORM>\n");

/*
    puts("<TABLE WIDTH=\"80%\">");
	puts("<TR>");
	puts("<TD ALIGN=\"left\"><H2>Tipo de Acceso:</H2></TD>");
    puts("<TD ALIGN=\"left\"><H2>El usuario posee Hosting?:</H2></TD>");
    puts("<TD ALIGN=\"left\"><H2>Cuota mensual en tiempo:</H2></TD>");
	puts("</TR>");


	puts("<TR>");
	puts("<TD>");
    puts("<INPUT TYPE=\"radio\" NAME=\"login\" VALUE=\"Internet Full\" CHECKED>Internet Full<BR>");
    puts("<INPUT TYPE=\"radio\" NAME=\"login\" VALUE=\"Correo Electronico\">Correo Electr&oacute;nico<BR>");
	puts("</TD>");

    puts("<TD ALIGN=\"left\">");
    puts("<INPUT TYPE=\"radio\" NAME=\"hosting\" VALUE=\"Posee Hosting\">Si<BR>");
    puts("<INPUT TYPE=\"radio\" NAME=\"hosting\" VALUE=\"No Posee Hosting\" CHECKED>No<BR>");
	puts("</TD>");

    puts("<TD ALIGN=\"left\">");
    puts("<INPUT TYPE=\"radio\" NAME=\"mquota\" VALUE=\"No Chequear Cuotas\" CHECKED>No Chequear Cuotas<BR>");
    puts("<INPUT TYPE=\"radio\" NAME=\"mquota\" VALUE=\"15 Horas\">15 Horas<BR>");
    puts("<INPUT TYPE=\"radio\" NAME=\"mquota\" VALUE=\"6 Horas\">6 Horas<BR>");
    puts("<INPUT TYPE=\"radio\" NAME=\"mquota\" VALUE=\"Sin conexion\">Sin Conexi&oacute;n<BR>");
    puts("</TD>");
	puts("</TR>");
	puts("</TABLE>");

    puts("<HR>");

    puts("<P><INPUT TYPE=SUBMIT VALUE=Agregar> <INPUT TYPE=RESET VALUE=Limpiar>");
    puts("</FORM>");
*/
    puts("</HTML>");
}

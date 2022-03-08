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
    char *fechaapertura, *horaapertura, *tipodispositivo, *tecnico;
	char *descripcion, *clienteID;
	char *dispositivos, buffer[256];
	int con, i;
	time_t hora;
	struct tm *hora_texto;

    uncgi();

    http_referer = getenv("HTTP_REFERER");
    usuario = getenv("WWW_usuario");
    password = getenv("WWW_password");
    clienteID = getenv("WWW_clienteID");
    apellido = getenv("WWW_apellido");
    nombre = getenv("WWW_nombre");
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

	
    /**********************************\
    * Forma para dar de alta el ticket *
    \**********************************/

    printf("Content-type: text/html\n\n");
    puts("<HTML>");
    puts("<HEAD>\n<TITLE>Apertura Ticket - Paso 2 de 4</TITLE>\n</HEAD>");
    puts("<BODY>");
    puts("Paso 2 de 4");
    puts("<HR>");


    /**************************************\
    * Confirmacion de los Datos Ingresados *
    \**************************************/

    puts("<H1>Confirmaci&oacute;n de los Datos Ingresados </H1>");
    puts("(Si estos datos no son correctos, vuelva hacia atr&aacute;s con su navegador)");
    puts("<H2>Estos son los datos ingresados:</H2>");
	puts("(Los datos marcados con <B>(*)</B> no deben dejarse en blanco)\n");

    puts("<FORM METHOD=GET ACTION=\"apertura2c.html\">");
    printf("<INPUT NAME=\"usuario\" VALUE=\"%s\" TYPE=\"hidden\">\n",usuario);
    printf("<INPUT NAME=\"password\" VALUE=\"%s\" TYPE=\"hidden\">\n",password);
    printf("<INPUT NAME=\"clienteID\" VALUE=\"%s\" TYPE=\"hidden\">\n",clienteID);
    printf("<INPUT NAME=\"fechaapertura\" VALUE=\"%s\" TYPE=\"hidden\">\n",fechaapertura);
    printf("<INPUT NAME=\"horaapertura\" VALUE=\"%s\" TYPE=\"hidden\">\n",horaapertura);
    printf("<INPUT NAME=\"tipodispositivo\" VALUE=\"%s\" TYPE=\"hidden\">\n",tipodispositivo);
    printf("<INPUT NAME=\"tecnico\" VALUE=\"%s\" TYPE=\"hidden\">\n",tecnico);
    printf("<INPUT NAME=\"descripcion\" VALUE=\"%s\" TYPE=\"hidden\">\n",descripcion);
	puts("<TABLE>");
    printf("<TR><TD>Fecha de Apertura: </TD><TD>%s</TD></TR>\n", fechaapertura);
    printf("<TR><TD>Hora de Apertura: </TD><TD>%s</TD></TR>\n", horaapertura);
    printf("<TR><TD>Tipo de Dispositivo: </TD><TD>%s</TD></TR>\n", tipodispositivo);
    printf("<TR><TD>T&eacute;cnico a Cargo: </TD><TD>%s</TD></TR>\n", tecnico);
    printf("<TR><TD>Descripci&oacute;n de la Falla: </TD><TD>%s</TD></TR>\n", descripcion);
	puts("<TR><TD COLSPAN=2><INPUT TYPE=\"submit\" VALUE=\"Confirmar\"></TD></TR>");
	puts("</TABLE>");
	puts("</FORM>");
	puts("</BODY>");
    puts("</HTML>");
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "conf.h"

char *getenv();

int main()
{
    char command[256];
    char *http_referer, *usuario, *password, *operacion, *url, *cadena;
    int con, i;

    uncgi();   

    http_referer = getenv("HTTP_REFERER"); 
    usuario = getenv("WWW_usuario"); 
    password = getenv("WWW_password"); 
    operacion = getenv("WWW_operacion"); 

    if ((http_referer != NULL) && ((strcmp(http_referer,"https://www.rivertech.com.ar:666/tickets/index.html")) == 0))
    {
/*
		if ((chequeo_pass(usuario, password)) != 0)
		{
	    	html_error("Password de Administraci&oacute;n incorrecto");
		}
*/
		if (operacion == NULL)
		{
	    	html_error ("Opci&oacute;n Vacia");
		}

		if (operacion != NULL)
		{
			if ((strcmp(operacion, "apertura")) == 0)
			{
		    	printf("Location: https://%s:666/tickets/apertura1a.html?usuario=%s&password=%s\n\n",SERVER, usuario, password);
			}
/*
			if ((strcmp(operacion, "del")) == 0)
			{
		    	printf("Location: https://%s:666/system/htdeluser.html?rpass=%s&dominio=%s\n\n",SERVER, rpass, dominio);
			}
*/
	    	exit (0);
		}
	} 
	else
	{
		/****************************************************\
		* Presentacion de la pagina HTML pricipal de tickets *
		\****************************************************/

		puts("Content-type: text/html\n\n");
		puts("<HTML>\n<HEAD>\n<TITLE>Sistema de Tickets</TITLE>\n</HEAD>");
		puts("<BODY>\n<H1>Sistema de Tickets</H1>");
		puts("<P>Ingrese usuario y password, y seleccione una operaci&oacute;n:</P>");
		puts("<FORM METHOD=POST ACTION=\"/tickets/index.html\">");
		puts("<TABLE>");
		puts("<TR><TD>Usuario: </TD><TD><input name=\"usuario\" size=\"16\" type=\"text\"></TD></TR>");
		puts("<TR><TD>Password: </TD><TD><input name=\"password\" size=\"16\" type=\"password\"></TD></TR>");
		puts("</TABLE>");
		puts("<HR>\n<TABLE BORDER=0>\n<TR>\n<TH>\n<H2>Operaci&oacute;n:</H2>");
		puts("<SELECT NAME=\"operacion\">");
		puts("<OPTION VALUE=\"apertura\">Apertura Ticket");
		puts("<OPTION VALUE=\"cierre\">Cierre Ticket");
		puts("<OPTION VALUE=\"modificacion\">Modificaci&oacute;n Ticket");
		puts("<OPTION VALUE=\"borrado\">Borrado Ticket");
		puts("</SELECT>\n<TH>");

		/***************************************************\
		* Cola de la pagina HTML pricipal de Administracion *
		\****************************************************/

		puts("</TR>\n</TABLE>\n<HR><P>");
		puts("<INPUT TYPE=SUBMIT VALUE=Continuar><INPUT TYPE=RESET VALUE=Vaciar>");
		puts("</FORM>\n</HTML>");
    }
}

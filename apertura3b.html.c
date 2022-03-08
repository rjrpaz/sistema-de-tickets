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
    char *http_referer, *usuario, *password, *opcion, *command;
	char *so, *dispositivos, buffer[256];
	int con, i;
	time_t hora;
	struct tm *hora_texto;

    uncgi();

    http_referer = getenv("HTTP_REFERER");
    usuario = getenv("WWW_usuario");
    password = getenv("WWW_password");
    opcion = getenv("WWW_opcion");

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

	
	if ((strcmp(opcion, "Si")) == 0)
	{
    	/**********************************\
    	* Forma para dar de alta el ticket *
    	\**********************************/

		printf("Content-type: text/html\n\n");
		puts("<HTML>");
		puts("<HEAD>\n<TITLE>Apertura Ticket - Paso 3 de 4</TITLE>\n</HEAD>");
		puts("<BODY>");
		puts("Paso 3 de 4");
		puts("<HR>");
		puts("<H1>Complete la Informaci&oacute;n del Driver</H1>");

		puts("<FORM ACTION=\"apertura3c.html\" ENCTYPE=\"multipart/form-data\" METHOD=\"POST\">");
		printf("<INPUT NAME=\"usuario\" VALUE=\"%s\" TYPE=\"hidden\">\n",usuario);
		printf("<INPUT NAME=\"password\" VALUE=\"%s\" TYPE=\"hidden\">\n",password);
		puts("<TABLE>");


		/*******************************************************************\
		* Obtiene informacion sobre los dispositivos en la tabla de Drivers *
		\*******************************************************************/

		mysql_init(&mysql);

		if(!mysql_real_connect(&mysql,DBHOST,DBUSER,DBPASS,DBBASE,0,NULL,0)) 
		{
			html_error("Error al intentar conectarse a la Base de Datos\n");
		}
	
		command = malloc(strlen(LISTAR_DISPOSITIVOS_DRIVERS));
		strcpy(command,LISTAR_DISPOSITIVOS_DRIVERS);
		con = mysql_query(&mysql, command);
	
		res = mysql_store_result(&mysql);
	        		
		if ((mysql_num_rows(res)) != 0)
		{	
			puts("<TR><TD>Tipo de Dispositivo:</TD>");
			puts("<TD><SELECT NAME=\"tipodispositivo\">");

			while (row = mysql_fetch_row(res))
			{
				dispositivos = row[1]+6;
			
				i = strcspn(dispositivos, ",");
				while (i != (strlen(dispositivos)))
				{
					strncpy(buffer, dispositivos, i-1);
					buffer[i-1] = '\0';

					printf("<OPTION VALUE=\"");
					printf("%s", buffer);
					printf("\">");
					printf("%s\n", buffer);

					dispositivos = dispositivos + strlen(buffer) + 3;
					i = strcspn(dispositivos, ",");
				}
				strncpy(buffer, dispositivos, strlen(dispositivos)-2);
				buffer[i-2] = '\0';

				printf("<OPTION VALUE=\"");
				printf("%s", buffer);
				printf("\">");
				printf("%s\n", buffer);
			}
			puts("</SELECT></TD></TR>");
		}
	
		free (command);
		mysql_free_result(res);


		/***********************************\
    	* Genera el listado de los Tecnicos *
    	\***********************************/

		command = malloc(strlen(LISTAR_SO_DRIVERS));
		strcpy(command,LISTAR_SO_DRIVERS);
		con = mysql_query(&mysql, command);
	
		res = mysql_store_result(&mysql);
	        		
		if ((mysql_num_rows(res)) != 0)
		{	
			puts("<TR><TD>Sistema Operativo:</TD>");
			puts("<TD><SELECT NAME=\"so\">");

			while (row = mysql_fetch_row(res))
			{
				so = row[1]+6;
			
				i = strcspn(so, ",");
				while (i != (strlen(so)))
				{
					strncpy(buffer, so, i-1);
					buffer[i-1] = '\0';

					printf("<OPTION VALUE=\"");
					printf("%s", buffer);
					printf("\">");
					printf("%s\n", buffer);

					so = so + strlen(buffer) + 3;
					i = strcspn(so, ",");
				}
				strncpy(buffer, so, strlen(so)-2);
				buffer[i-2] = '\0';

				printf("<OPTION VALUE=\"");
				printf("%s", buffer);
				printf("\">");
				printf("%s\n", buffer);
			}
			puts("</SELECT></TD></TR>");
		}
	
		free (command);
		mysql_free_result(res);

		mysql_close(&mysql);


		puts("<TR><TD>Archivo de Driver:</TD>");
		puts("<TD><INPUT NAME=\"driver\" TYPE=\"file\"></TD></TR>");

    	puts("<TR><TD><INPUT TYPE=\"submit\" VALUE=\"Agregar\"></TD>");
    	puts("<TD><INPUT TYPE=\"reset\" VALUE=\"Limpiar\"></TD></TR>");

		puts("</TABLE>");
		puts("</FORM>");
		puts("</BODY>");

    	puts("</HTML>");
/*
    puts("<TR><TD COLSPAN=2>(*) Descripci&oacute;n de la Falla: <BR>");
	puts("<TEXTAREA ROWS=\"4\" COLS=\"60\" NAME=\"descripcion\">Ingrese aqu&iacute; una descripci&oacute;n del problema</TEXTAREA></TD></TR>");

    puts("<TR><TD><INPUT TYPE=\"submit\" VALUE=\"Agregar\"></TD>");
    puts("<TD><INPUT TYPE=\"reset\" VALUE=\"Limpiar\"></TD></TR>");


*/

	}
	
	else if ((strcmp(opcion, "No")) == 0)
	{
	}
	else
	{
		html_error("Ha habido un error. No ingres&o ninguna de las dos<BR>opciones posibles. Por favos, consulte al Webmaster.");
	}

/*
    puts("<H2>Estos son los datos ingresados:</H2>");
	puts("(Los datos marcados con <B>(*)</B> no deben dejarse en blanco)\n");

	puts("<TABLE>");
    printf("<TR><TD>Fecha de Apertura: </TD><TD>%s</TD></TR>\n", fechaapertura);
    printf("<TR><TD>Hora de Apertura: </TD><TD>%s</TD></TR>\n", horaapertura);
    printf("<TR><TD>Tipo de Dispositivo: </TD><TD>%s</TD></TR>\n", tipodispositivo);
    printf("<TR><TD>T&eacute;cnico a Cargo: </TD><TD>%s</TD></TR>\n", tecnico);
    printf("<TR><TD>Descripci&oacute;n de la Falla: </TD><TD>%s</TD></TR>\n", descripcion);
	puts("<TR><TD COLSPAN=2><INPUT TYPE=\"submit\" VALUE=\"Confirmar\"></TD></TR>");
	puts("</BODY>");
*/
}

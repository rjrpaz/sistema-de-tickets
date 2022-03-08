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

	ptr_cliente = &cliente;
    i = getclientebyname(nombre, apellido, ptr_cliente);
	if (i == 0)
	{
		html_error ("No se pudo determinar el n&uacute;mero de ID del Cliente");
	}
	else if (i == -1)
	{
		html_error ("Existe m&aacute;s de un cliente con ese nombre<BR>. Por favor, contacte al DBA para corregir la situaci&oacute;n");
	}


    /**********************************\
    * Forma para dar de alta el ticket *
    \**********************************/

    printf("Content-type: text/html\n\n");
    puts("<HTML>");
    puts("<HEAD>\n<TITLE>Apertura Ticket - Paso 2 de 4</TITLE>\n</HEAD>");
    puts("<BODY>");
    puts("Paso 2 de 4");
    puts("<HR>");

    puts("Ingrese los datos del Ticket: <BR>\n");
    puts("<H2>Datos del Ticket:</H2>");
	puts("(Los datos marcados con (*) no deben dejarse en blanco)\n");

    puts("<FORM METHOD=GET ACTION=\"apertura2b.html\">");
    printf("<INPUT NAME=\"usuario\" SIZE=\"16\" VALUE=\"%s\" TYPE=\"hidden\">\n",usuario);
    printf("<INPUT NAME=\"password\" SIZE=\"16\" VALUE=\"%s\" TYPE=\"hidden\">\n",password);
	puts("<TABLE>\n");
    printf("<TR><TD>Apellido del Cliente: </TD><TD>%s</TD></TR>\n", cliente.Apellido);
    printf("<TR><TD>Nombre del Cliente: </TD><TD>%s</TD></TR>\n", cliente.Nombre);
    printf("<TR><TD>ID del Cliente: </TD><TD>%d</TD></TR>\n", cliente.ClienteID);
    printf("<INPUT NAME=\"clienteID\" SIZE=\"16\" VALUE=\"%d\" TYPE=\"hidden\">\n",cliente.ClienteID);


    /****************************\
    * Obtiene la hora y la fecha *
    \****************************/

	hora = time((time_t *)NULL);
	hora_texto = localtime(&hora);

    printf("<TR><TD>(*) Fecha Apertura: </TD><TD><INPUT NAME=\"fechaapertura\" SIZE=\"10\" VALUE=\"%d-%d-%d\"></TD></TR>", hora_texto->tm_year + 1900, hora_texto->tm_mon, hora_texto->tm_mday);
    printf("<TR><TD>(*) Hora Apertura: </TD><TD><INPUT NAME=\"horaapertura\" SIZE=\"8\" VALUE=\"%02d:%02d:%02d\"></TD></TR>", hora_texto->tm_hour, hora_texto->tm_min, hora_texto->tm_sec);


	mysql_init(&mysql);

	if(!mysql_real_connect(&mysql,DBHOST,DBUSER,DBPASS,DBBASE,0,NULL,0)) 
	{
		html_error("Error al intentar conectarse a la Base de Datos\n");
	}
	
    /**********************************************************\
    * Genera el listado correspondiente al tipo de Dispositivo *
    \**********************************************************/

	command = malloc(strlen(LISTAR_DISPOSITIVOS));
	strcpy(command,LISTAR_DISPOSITIVOS);
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

	command = malloc(strlen(LISTAR_TECNICOS));
	strcpy(command,LISTAR_TECNICOS);
	con = mysql_query(&mysql, command);
	
	res = mysql_store_result(&mysql);
	        		
	if ((mysql_num_rows(res)) != 0)
	{	
		puts("<TR><TD>T&eacute;cnico a Cargo:</TD>");
		puts("<TD><SELECT NAME=\"tecnico\">");

		while (row = mysql_fetch_row(res))
		{
			tecnicos = row[1]+6;
			
			i = strcspn(tecnicos, ",");
			while (i != (strlen(tecnicos)))
			{
				strncpy(buffer, tecnicos, i-1);
				buffer[i-1] = '\0';

				printf("<OPTION VALUE=\"");
				printf("%s", buffer);
				printf("\">");
				printf("%s\n", buffer);

				tecnicos = tecnicos + strlen(buffer) + 3;
				i = strcspn(tecnicos, ",");
			}
			strncpy(buffer, tecnicos, strlen(tecnicos)-2);
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

    puts("<TR><TD COLSPAN=2>(*) Descripci&oacute;n de la Falla: <BR>");
	puts("<TEXTAREA ROWS=\"4\" COLS=\"60\" NAME=\"descripcion\">Ingrese aqu&iacute; una descripci&oacute;n del problema</TEXTAREA></TD></TR>");

    puts("<TR><TD><INPUT TYPE=\"submit\" VALUE=\"Agregar\"></TD>");
    puts("<TD><INPUT TYPE=\"reset\" VALUE=\"Limpiar\"></TD></TR>");
	puts("</TABLE>");
	puts("</FORM>");
	puts("</BODY>");

    puts("</HTML>");
}

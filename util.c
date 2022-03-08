#include "conf.h"
#include "db.h"

char * command;
int con;

struct spwd *sp;
char *crypt();

/**********************************\
* Imprime Mensaje de Error en HTML *
\**********************************/

int html_error(char mensaje[256])
{
	puts("Content-type: text/html\n");
	puts("<HTML>");
	puts("<TITLE>Error Inesperado</TITLE>");
	puts("<BODY>");
	printf("<H1>Error ...!</H1>\n");	
	printf("%s\n", mensaje);	
	puts("</BODY>");
	puts("</HTML>");
	exit (1);
}



/***************************************\
* Chequeo de password de Administracion *
\***************************************/

int chequeo_pass(char *usuario, char *password)
{
	sp=getspnam(usuario);

	if ((password == NULL) || (strcmp(sp->sp_pwdp,crypt(password,sp->sp_pwdp))))
	{
		return(1);
	}
	return(0);
}


/*****************************************************\
* Obtiene Registro de cliente segun nombre y apellido *
* Devuelve los siguientes valores:                    *
* 1: Si esta todo OK                                  *
* 0: Si no obtuvo ningun registro                     *
* -1: Si obtuvo mas de un registro                    *
\*****************************************************/

int getclientebyname(char *nombre, char *apellido, cliente_reg *cli)
{

	cli->ClienteID = 0;
	cli->ContactoID = 0;
	strcpy(cli->Nombre, "");
	strcpy(cli->Apellido, "");
	strcpy(cli->Direccion, "");
	strcpy(cli->CodigoPostal, "");
	strcpy(cli->Telefono, "");
	strcpy(cli->Fax, "");
	strcpy(cli->Email, "");
	strcpy(cli->Ciudad, "");
	strcpy(cli->Provincia, "");

	mysql_init(&mysql);	

	if(!mysql_real_connect(&mysql,DBHOST,DBUSER,DBPASS,DBBASE,0,NULL,0))
	{
		html_error("Error al intentar conectarse a la Base de Datos\n");
		exit (1);
	}

	command = malloc (strlen (OBTENER_REG_POR_NOMBRE) + strlen(nombre) + strlen(apellido));
	sprintf(command, OBTENER_REG_POR_NOMBRE, nombre, apellido);
	con = mysql_query(&mysql, command);
	res = mysql_store_result(&mysql);
	if ((mysql_num_rows(res)) == 1)
	{
		while (row = mysql_fetch_row(res))
		{
			cli->ClienteID = atoi(row[0]);
			cli->ContactoID = atoi(row[1]);
			strcpy(cli->Nombre, row[2]);
			strcpy(cli->Apellido, row[3]);
			strcpy(cli->Direccion, row[4]);
			strcpy(cli->CodigoPostal, row[5]);
			strcpy(cli->Telefono, row[6]);
			strcpy(cli->Fax, row[7]);
			strcpy(cli->Email, row[8]);
			strcpy(cli->Ciudad, row[9]);
			strcpy(cli->Provincia, row[10]);
			return(1);
		}
	}
	else if ((mysql_num_rows(res)) == 0)
	{
		return(0);
	}
	else
	{
		return(-1);
	}

	free (command);
}


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql.h>
#include<getopt.h>
#include "conf.h"
#include "db.h"

void procesar_opciones(int argc, char *argv[]);
void usage(void);

int clienteID = 0;
char tipodispositivo[255] = "";
char descripcion[255] = "";
char fechaapertura[16] = "";
char horaapertura[16] = "";
char tecnico[100] = "";


int main(int argc, char *argv[])
{

    char *salt;
    char *passwd;
    char *encpass;
    char *command;
    int con;
    int command_length;
    char *username;
    char *truncated;
    char *usuario;
    char *realm;
    char *crypt();
    char *crypt_pass;
    int dom_id, quisio_gid;

	procesar_opciones(argc, argv);

    mysql_init(&mysql);

    if (!(mysql_real_connect(&mysql,DBHOST,DBUSER,DBPASS,DBBASE,0,NULL,0)))
	{
		printf("Error al Conectarse con la Base de Datos\n");
		fprintf(stderr, "%s\n", mysql_error(&mysql));
		exit(1);
    }

    command = (char *) malloc(strlen(INSERT_TICKET) + sizeof(int) + strlen(tipodispositivo) + strlen(descripcion) + strlen(fechaapertura) + strlen(horaapertura) + strlen(tecnico));
    sprintf(command, INSERT_TICKET, clienteID, tipodispositivo, descripcion, fechaapertura, horaapertura, tecnico);

    con = mysql_query(&mysql, command);
    free(command);

    res = mysql_store_result(&mysql);

    if ((mysql_affected_rows(&mysql)) != 1)
    {
		fprintf(stderr, "%s\n", mysql_error(&mysql));
    }

    mysql_free_result(res);
    mysql_close(&mysql);
    exit (0);
}

void procesar_opciones(int argc, char *argv[])
{
	int c;

	if (argc == 1)
	{
		usage();
		exit(1);
	}

	while ((c = getopt(argc, argv, "i:t:d:f:H:T:h")) != EOF)
	{
		switch (c)
		{
			case 'i':
				clienteID = atoi(optarg);
				break;
			case 't':
				strcpy(tipodispositivo, optarg);
				break;
			case 'd':
				strcpy(descripcion, optarg);
				break;
			case 'f':
				strcpy(fechaapertura, optarg);
				break;
			case 'H':
				strcpy(horaapertura, optarg);
				break;
			case 'T':
				strcpy(tecnico, optarg);
				break;
			case 'h':
			default:
				usage();
				exit(1);
		}
	}
	
	argc -= optind;
	argv += optind;
	
	if (argc > 1)
	{
		usage();
		exit(1);
	}
}

void usage(void)
{
	puts("uso: AltaCliente [OPCIONES]");
	puts("OPCIONES:");
	puts("\t-i <ID del Cliente>");
	puts("\t-t \"<Tipo de Dispositivo>\"");
	puts("\t-d \"<Descripcion del Problema>\"");
	puts("\t-f \"<Fecha Apertura>\"");
	puts("\t-H \"<Hora Apertura>\"");
	puts("\t-T \"<Tecnico a Cargo>\"");
	puts("\t-h \tPresenta este menu de ayuda");
}

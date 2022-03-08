#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql.h>
#include<getopt.h>
#include "conf.h"
#include "db.h"

void procesar_opciones(int argc, char *argv[]);
void usage(void);

int contactoID = 0;
char apellido[40], nombre[60];
char direccion[255] = "";
char codigopostal[10] = "";
char telefono[16] = "";
char fax[16] = "";
char email[100] = "";
char ciudad[50] = ""; 
char provincia[30] = "";


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
		printf("Error Connecting To Database\n");
		fprintf(stderr, "%s\n", mysql_error(&mysql));
		exit(1);
    }

    command = (char *) malloc(strlen(INSERT_CLIENTE) + sizeof(int) + strlen(apellido) + strlen(nombre) + strlen(direccion) + strlen(codigopostal) + strlen(telefono) + strlen(fax) + strlen(email) + strlen(ciudad) + strlen(provincia));
    sprintf(command, INSERT_CLIENTE, contactoID, nombre, apellido, direccion, codigopostal, telefono, fax, email, ciudad, provincia);

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

	while ((c = getopt(argc, argv, "i:a:n:d:c:t:f:e:C:p:h")) != EOF)
	{
		switch (c)
		{
			case 'i':
				contactoID = atoi(optarg);
				break;
			case 'a':
				strcpy(apellido, optarg);
				break;
			case 'n':
				strcpy(nombre, optarg);
				break;
			case 'd':
				strcpy(direccion, optarg);
				break;
			case 'c':
				strcpy(codigopostal, optarg);
				break;
			case 't':
				strcpy(telefono, optarg);
				break;
			case 'f':
				strcpy(fax, optarg);
				break;
			case 'e':
				strcpy(email, optarg);
				break;
			case 'C':
				strcpy(ciudad, optarg);
				break;
			case 'p':
				strcpy(provincia, optarg);
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
	puts("\t-i \"<ID del Contacto>\"");
	puts("\t-a \"<apellido>\"");
	puts("\t-n \"<nombre>\"");
	puts("\t-d \"<direccion>\"");
	puts("\t-c \"<codigo postal>\"");
	puts("\t-t \"<telefono>\"");
	puts("\t-f \"<fax>\"");
	puts("\t-e <e-mail>");
	puts("\t-C \"<ciudad>\"");
	puts("\t-p \"<provincia>\"");
	puts("\t-h \tPresenta este menu de ayuda");
}

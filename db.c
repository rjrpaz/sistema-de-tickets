#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "conf.h"
#include "trim.h"
#include "db.h"
#include <pwd.h>
#include <shadow.h>
#include <sys/time.h>

char command[256];
int con;

void exiterr(int exitcode)
{
    fprintf(stderr, "%s\n", mysql_error(&mysql));
    exit (exitcode);
}


char * crypt_make_salt()
{
    struct timeval tv;
    static char result[40];

    result[0] = '\0';
    strcpy(result, "$1$"); 

    gettimeofday(&tv, (struct timezone *) 0);
    strcat(result, l64a(tv.tv_usec));
    strcat(result, l64a(tv.tv_sec + getpid() + clock()));

    if (strlen(result) > 3 + 8)  
	result[11] = '\0';

    return result;
}


int chkuser(char *dominio, char *name)
{
    int valor;

    mysql_init(&mysql);

    if(!mysql_real_connect(&mysql,DBHOST,DBUSER,DBPASS,DBBASE,0,NULL,0)) 
    {
	printf("Error Connecting To Database\n");
	exit(1);
    }

    sprintf(command,"SELECT u_id FROM usuarios,dominios WHERE usuarios.username = '%s' AND dominios.dom_name = '%s' AND usuarios.dom_id = dominios.dom_id", name, dominio);
    con = mysql_query(&mysql, command);

    res = mysql_store_result(&mysql);

    row = mysql_fetch_row(res);
    if (row)
	valor = 1;
    else
	valor = 0;

    mysql_free_result(res);
    mysql_close(&mysql);
    return(valor);
}

#include <pwd.h>
#include <shadow.h>
#include <string.h>
#include <stdlib.h>

#define DBHOST "localhost"
#define DBUSER "root"
#define DBPASS "informatica"
#define DBBASE "rivertech"

#ifndef SERVER
#define SERVER "www.rivertech.com.ar"
#endif

#ifndef SERVERBIN
#define SERVERBIN "www.rivertech.com.ar/tickets"
#endif

#define DOMINIO_POR_DEFECTO "www.rivertech.com.ar"

#define INSERT_CLIENTE "INSERT INTO Clientes (ContactoID, Nombre, Apellido, Direccion, CodigoPostal, Telefono, Fax, Email, Ciudad, Provincia) VALUES(%d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"

#define INSERT_TICKET "INSERT INTO Tickets (ClienteID, TipoDispositivo, Descripcion, Estado, FechaApertura, HoraApertura, Tecnico) VALUES(%d, '%s', '%s', 'Abierto', '%s', '%s', '%s')"

#define OBTENER_REG_POR_NOMBRE "SELECT * FROM Clientes WHERE Nombre = '%s' AND Apellido = '%s'"

#define LISTAR_DISPOSITIVOS "SHOW columns FROM Tickets LIKE 'TipoDispositivo'"

#define LISTAR_TECNICOS "SHOW columns FROM Tickets LIKE 'Tecnico'"

#define LISTAR_DISPOSITIVOS_DRIVERS "SHOW columns FROM Drivers LIKE 'TipoDispositivo'"

#define LISTAR_SO_DRIVERS "SHOW columns FROM Drivers LIKE 'SistemaOperativo'"



#define SELECT_PASSWD "SELECT password FROM usuarios, dominios WHERE usuarios.username = '%s' AND usuarios.dom_id = dominios.dom_id AND dominios.domname = '%s'"
#define SELECT_DOM_ID "SELECT dom_id FROM dominios WHERE dom_name = '%s'"
#define SELECT_U_ID "SELECT u_id FROM usuarios WHERE username = '%s'"

#define INSERT_USUARIO "INSERT INTO usuarios (g_id, username, password, dom_id, tipo_acceso, hosting) VALUES(%d, '%s', '%s', %d, '%s', '%s')"
#define DELETE_USUARIO "DELETE FROM usuarios WHERE username = '%s' AND dom_id = %d"

#define INSERT_QUOTA "INSERT INTO cuotas (u_id, dom_id, mensual) VALUES(%d, %d, %d)"
#define DELETE_QUOTA "DELETE FROM cuotas WHERE u_id = %d AND dom_id = %d"


#define ACCT_IN "INSERT INTO login (login, start_record) VALUES ('%s',SYSDATE())"
#define ACCT_OUT "INSERT INTO logout (login, duration, ip_address, input_packets, output_packets, end_record) VALUES ('%s',%s,'%s',%s,%s,SYSDATE())"

#define STOP 1
#define START 0

typedef struct
{
	int ClienteID;
	int ContactoID;
	char Nombre[60];
	char Apellido[40];
	char Direccion[256];
	char CodigoPostal[10];
	char Telefono[16];
	char Fax[16];
	char Email[100];
	char Ciudad[50];
	char Provincia[30];
} cliente_reg;


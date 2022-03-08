# Usuario para conectarse a MySQL Server
MYSQLUSER=root

# Password para conectarse a MySQL Server
MYSQLPASSWORD=informatica

# Archivos ejecutables de MySQL
MYSQLBIN=/usr/local/bin

# Ubicacion de los archivos de cabecera de MySQL
MYSQLINCDIR=/usr/local/include/mysql

# Ubicacion de las librerias compartidas de MySQL
MYSQLLIBDIR=/usr/local/lib/mysql

PERL=/usr/bin/perl

# Ubicacion de las paginas de Tickets
HOMEADMDIR=/usr/local/apache-ssl/tickets
ADMDIR=/root/tickets
CGIADMDIR=/usr/local/apache-ssl/tickets

# Variable necesarias para uncgi
SCRIPT_BIN=$(CGIADMDIR)
DESTDIR=/usr/local/apache-ssl/cgi-bin
NOQUERY=-DNO_QUERY_OK
UNCGIFLAGS=-DSCRIPT_BIN='"$(SCRIPT_BIN)"' $(NOQUERY) -DLIBRARY

LDFLAGS=-lmysqlclient

CRYPTFLAGS=-lcrypt
CFLAGS=-DCRYPT

PROGS=uncgi.o util.o index.html apertura1a.html apertura1b.html apertura1c.html AltaCliente apertura2a.html apertura2b.html apertura2c.html AltaTicket apertura3a.html apertura3b.html apertura3c.html

CC=gcc

all: $(PROGS)

uncgi.o:	uncgi.c
	$(CC) -c uncgi.c $(CFLAGS) $(UNCGIFLAGS)

util.o:		util.c
	$(CC) -c util.c $(CFLAGS)

index.html.o:	index.html.c
	$(CC) -c index.html.c $(CFLAGS)

index.html:	index.html.o uncgi.o
	$(CC) -o index.html index.html.o uncgi.o util.o -L$(MYSQLLIBDIR) $(LDFLAGS)
	
apertura1a.html.o:	apertura1a.html.c
	$(CC) -c apertura1a.html.c $(CFLAGS)

apertura1a.html:	apertura1a.html.o uncgi.o
	$(CC) -o apertura1a.html apertura1a.html.o uncgi.o util.o $(LDFLAGS) -L$(MYSQLLIBDIR)

apertura1b.html.o:	apertura1b.html.c
	$(CC) -c apertura1b.html.c $(CFLAGS)

apertura1b.html:	apertura1b.html.o uncgi.o
	$(CC) -o apertura1b.html apertura1b.html.o uncgi.o util.o $(LDFLAGS) -L$(MYSQLLIBDIR)

apertura1c.html.o:	apertura1c.html.c
	$(CC) -c apertura1c.html.c $(CFLAGS)

apertura1c.html:	apertura1c.html.o uncgi.o
	$(CC) -o apertura1c.html apertura1c.html.o uncgi.o util.o $(LDFLAGS) -L$(MYSQLLIBDIR)

AltaCliente.o:	AltaCliente.c
	$(CC) -c AltaCliente.c $(CFLAGS) -I$(MYSQLINCDIR)

AltaCliente:	AltaCliente.o
	$(CC) -o AltaCliente AltaCliente.o -L$(MYSQLLIBDIR) $(LDFLAGS)
	
apertura2a.html.o:	apertura2a.html.c
	$(CC) -c apertura2a.html.c $(CFLAGS)

apertura2a.html:	apertura2a.html.o uncgi.o
	$(CC) -o apertura2a.html apertura2a.html.o uncgi.o util.o $(LDFLAGS) -L$(MYSQLLIBDIR)

apertura2b.html.o:	apertura2b.html.c
	$(CC) -c apertura2b.html.c $(CFLAGS)

apertura2b.html:	apertura2b.html.o uncgi.o
	$(CC) -o apertura2b.html apertura2b.html.o uncgi.o util.o $(LDFLAGS) -L$(MYSQLLIBDIR)

apertura2c.html.o:	apertura2c.html.c
	$(CC) -c apertura2c.html.c $(CFLAGS)

apertura2c.html:	apertura2c.html.o uncgi.o
	$(CC) -o apertura2c.html apertura2c.html.o uncgi.o util.o $(LDFLAGS) -L$(MYSQLLIBDIR)

AltaTicket.o:	AltaTicket.c
	$(CC) -c AltaTicket.c $(CFLAGS) -I$(MYSQLINCDIR)

AltaTicket:	AltaTicket.o
	$(CC) -o AltaTicket AltaTicket.o -L$(MYSQLLIBDIR) $(LDFLAGS)
	
apertura3a.html.o:	apertura3a.html.c
	$(CC) -c apertura3a.html.c $(CFLAGS)

apertura3a.html:	apertura3a.html.o uncgi.o
	$(CC) -o apertura3a.html apertura3a.html.o uncgi.o util.o $(LDFLAGS) -L$(MYSQLLIBDIR)

apertura3b.html.o:	apertura3b.html.c
	$(CC) -c apertura3b.html.c $(CFLAGS)

apertura3b.html:	apertura3b.html.o uncgi.o
	$(CC) -o apertura3b.html apertura3b.html.o uncgi.o util.o $(LDFLAGS) -L$(MYSQLLIBDIR)

apertura3c.html: apertura3c.html.pl
	$(PERL) -wc apertura3c.html.pl

#trim.o:		trim.c trim.h
#	$(CC) -c trim.c $(CFLAGS)

#db.o:		db.c db.h
#	$(CC) -c db.c $(CFLAGS)

#util.o:		util.c
#	$(CC) -c util.c $(CFLAGS)

#radauth.o:	radauth.c
#	$(CC) -c radauth.c $(CFLAGS) -I$(MYSQLINCDIR)

#radauth:	radauth.o
#	$(CC) -o radauth radauth.o trim.o -L$(MYSQLLIBDIR) $(LDFLAGS) $(CRYPTFLAGS)

#radacct.o:	radacct.c
#	$(CC) -c radacct.c $(CFLAGS) -I$(MYSQLINCDIR)

#radacct:	radacct.o
#	$(CC) -o radacct radacct.o trim.o -L$(MYSQLLIBDIR) $(LDFLAGS)

#htadduser.html.o:	htadduser.html.c
#	$(CC) -c htadduser.html.c $(CFLAGS) -I$(MYSQLINCDIR)

#htadduser.html:	htadduser.html.o uncgi.o util.o
#	$(CC) -o htadduser.html uncgi.o util.o htadduser.html.o -L$(MYSQLLIBDIR) $(LDFLAGS)
	
#adduser.html.o:	adduser.html.c
#	$(CC) -c adduser.html.c $(CFLAGS) -I$(MYSQLINCDIR)

#adduser.html:	adduser.html.o db.o uncgi.o util.o
#	$(CC) -o adduser.html db.o uncgi.o util.o adduser.html.o -L$(MYSQLLIBDIR) $(LDFLAGS)

#addquota.o:	addquota.c
#	$(CC) -c addquota.c $(CFLAGS) -I$(MYSQLINCDIR)

#addquota:	addquota.o
#	$(CC) -o addquota addquota.o db.o -L$(MYSQLLIBDIR) $(LDFLAGS)
	
#htdeluser.html.o:	htdeluser.html.c
#	$(CC) -c htdeluser.html.c $(CFLAGS) -I$(MYSQLINCDIR)

#htdeluser.html:	htdeluser.html.o uncgi.o util.o
#	$(CC) -o htdeluser.html uncgi.o util.o htdeluser.html.o -L$(MYSQLLIBDIR) $(LDFLAGS)

#deluser.html.o:	deluser.html.c
#	$(CC) -c deluser.html.c $(CFLAGS) -I$(MYSQLINCDIR)

#deluser.html:	deluser.html.o db.o uncgi.o util.o
#	$(CC) -o deluser.html db.o uncgi.o util.o deluser.html.o -L$(MYSQLLIBDIR) $(LDFLAGS)

#delquota.o:	delquota.c
#	$(CC) -c delquota.c $(CFLAGS) -I$(MYSQLINCDIR)

#delquota:	delquota.o
#	$(CC) -o delquota delquota.o db.o -L$(MYSQLLIBDIR) $(LDFLAGS)

#deluser.o:	deluser.c
#	$(CC) -c deluser.c $(CFLAGS) -I$(MYSQLINCDIR)

#deluser:	deluser.o
#	$(CC) -o deluser deluser.o db.o -L$(MYSQLLIBDIR) $(LDFLAGS)
	
clean:
	/bin/rm -f $(PROGS) *.o core

install:
	install -s -m 700 -D index.html $(HOMEADMDIR)/index.html
	install -s -m 700 apertura1a.html $(HOMEADMDIR)/apertura1a.html
	install -s -m 700 apertura1b.html $(HOMEADMDIR)/apertura1b.html
	install -s -m 700 apertura1c.html $(HOMEADMDIR)/apertura1c.html
	install -s -m 700 -D AltaCliente $(ADMDIR)/AltaCliente
	install -s -m 700 apertura2a.html $(HOMEADMDIR)/apertura2a.html
	install -s -m 700 apertura2b.html $(HOMEADMDIR)/apertura2b.html
	install -s -m 700 apertura2c.html $(HOMEADMDIR)/apertura2c.html
	install -s -m 700 AltaTicket $(ADMDIR)/AltaTicket
	install -s -m 700 apertura3a.html $(HOMEADMDIR)/apertura3a.html
	install -s -m 700 apertura3b.html $(HOMEADMDIR)/apertura3b.html
	install -m 700 apertura3c.html.pl $(HOMEADMDIR)/apertura3c.html

uninstall:
#	rm -f $(BINDIR)/{radauth,radacct,admin.html}

createdb:
	$(MYSQLBIN)/mysqladmin create rivertech -u $(MYSQLUSER) -p$(MYSQLPASSWORD)

droptables:
	/usr/bin/mysql -u $(MYSQLUSER) -p$(MYSQLPASSWORD) <droptables.sql

createtables:
	/usr/bin/mysql -u $(MYSQLUSER) -p$(MYSQLPASSWORD) <createtables.sql


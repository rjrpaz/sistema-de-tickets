#!/usr/bin/perl

#use CGI;
use strict 'refs';
use lib '..';
use CGI qw(:standard);
use CGI::Carp qw/fatalsToBrowser/;

$TempFile::TMPDIRECTORY='/tmp';
$query = new CGI;

$http_referer = $query->param('HTTP_REFERER');
$usuario = $query->param('usuario');
$password = $query->param('password');
$tipodispositivo = $query->param('tipodispositivo');
$so = $query->param('so');
#$driver = $query->param('driver');

#    /*********************\
#    * Chequeo del referer *
#    \*********************/

#    /********************\
#    * Chequeo de Usuario *
#    \********************/

#    /*********************************\
#    * Chequeo de la Fecha de Apertura *
#    \*********************************/

#    /********************************\
#    * Chequeo de la Hora de Apertura *
#    \********************************/

#print "Content-type: text/html\n\n";
#print "<HTML><BODY>";
#print "HTTP_REFERER: ",$http_referer,"\n";
#print "Tipo de Dispositivo: ",$tipodispositivo,"\n";
#print "Sistema Operativo: ",$so,"\n";


# Process the form if there is a file name entered
if (my $file = param('driver')) {
    my $tmpfile=tmpFileName($file);
#    my $mimetype = uploadInfo($file)->{'Content-Type'} || '';
print "Content-type: ",uploadInfo($file),"\n\n";
print "<HTML><BODY>";
	print "Content-type: ",uploadInfo($file),"\n\n";
    print hr(),
          h2($file),
          h3($tmpfile),
          h4("MIME Type:",em($mimetype));

#    my($lines,$words,$characters,@words) = (0,0,0,0);
open(PRUEBA, "> /tmp/prueba");
{
    while (<$file>) {
	print PRUEBA $_;
#	$lines++;
#	$words += @words=split(/\s+/);
#	$characters += length($_);
    }
    close $file;
}
close (PRUEBA);
#    grep($stats{$_}++,param('count'));
#	print strong("Lines: "),$lines,br if $stats{'count lines'};
#	print strong("Words: "),$words,br if $stats{'count words'};
#	print strong("Characters: "),$characters,br if $stats{'count characters'};
}


	print "</BODY></HTML>";










exit;

#    /************************************************\
#    * Crea una nueva entrada en la tabla de Clientes *
#    \************************************************/
#/*
#	command = malloc(strlen("/root/tickets/AltaTicket ") + strlen(clienteID) + strlen(tipodispositivo) + strlen(descripcion) + strlen(fechaapertura) + strlen(horaapertura) + strlen(tecnico) + 33);
#	sprintf(command,"/root/tickets/AltaTicket -i %s -t \"%s\" -d \"%s\" -f \"%s\" -H \"%s\" -T \"%s\"", clienteID, tipodispositivo, descripcion, fechaapertura, horaapertura, tecnico);
#	printf("Comando: %s\n", command);
#	system(command);
#	free(command);
#*/
#    /*****************************************\
#    * Redirecciona para dar de alta el Ticket *
#    \*****************************************/

#    printf("Location: apertura3a.html?usuario=%s&password=%s\n\n", usuario, password);
#	exit (0);	
#}

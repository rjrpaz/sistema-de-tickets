# Script to construct 'login' & 'logout' table within 'accounting' database.
#
#
DROP DATABASE rivertech;
CREATE DATABASE rivertech;

USE rivertech;


#
# Estructura de la Tabla 'Clientes'
#
DROP TABLE IF EXISTS Clientes;
CREATE TABLE Clientes (
  ClienteID int(10) unsigned DEFAULT '0' NOT NULL auto_increment,
  ContactoID int(10) unsigned DEFAULT '0' NOT NULL,
  Nombre varchar(60),
  Apellido varchar(40),
  Direccion varchar(255),
  CodigoPostal varchar(10),
  Telefono varchar(16),
  Fax varchar(16),
  Email varchar(100),
  Ciudad varchar(50),
  Provincia varchar(30),
  PRIMARY KEY (ClienteID),
  UNIQUE id (ClienteID)
);


#
# Estructura de la tabla 'Pagos'
#
DROP TABLE IF EXISTS Pagos;
CREATE TABLE Pagos (
  PagoID int(10) unsigned DEFAULT '0' NOT NULL auto_increment,
  ClienteID int(10) unsigned DEFAULT '0' NOT NULL,
  FechaPago date,
  TipoPago varchar(10),
  Cantidad float(5,2),
  PRIMARY KEY (PagoID),
  UNIQUE PagoID (PagoID)
);


#
# Estructura de la tabla 'Tickets'
#
DROP TABLE IF EXISTS Tickets;
CREATE TABLE Tickets (
  TicketID int(10) unsigned DEFAULT '0' NOT NULL auto_increment,
  ClienteID int(10) unsigned DEFAULT '0' NOT NULL,
  TipoDispositivo enum('cpu','video'),
  Descripcion varchar(255),
  Estado enum('Abierto','Cerrado'),
  FechaApertura date,
  HoraApertura time,
  FechaCierre date,
  HoraCierre time,
  Tecnico enum('Reynaldo Reynafe','Juan Jose Sierra'),
  PRIMARY KEY (TicketID),
  UNIQUE TicketID (TicketID)
);


#
# Estructura de la tabla 'Drivers'
#
DROP TABLE IF EXISTS Drivers;
CREATE TABLE Drivers (
  DriverID int(10) unsigned DEFAULT '0' NOT NULL auto_increment,
  TipoDispositivo enum('video','modem','red', 'scanner'),
  SistemaOperativo enum('Windows 95','Windows NT'),
  Descripcion varchar(255),
  Driver longblob,
  PRIMARY KEY (DriverID),
  UNIQUE DriverID (DriverID)
);



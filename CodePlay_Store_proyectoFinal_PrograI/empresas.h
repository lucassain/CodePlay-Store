#ifndef EMPRESAS_H_INCLUDED
#define EMPRESAS_H_INCLUDED

#include "juegos.h"

#define ARCHIVO_EMPRESAS "empresas.dat"

typedef struct {
    char nombre[50];
    char email[50];
    char contrasenia[20];
    char pais[30];
    char descripcion[150];
    char fechaRegistro[15];
    int idEmpresa;
} stEmpresa;

//Prototipado
int loginEmpresas(stEmpresa *empresaActual);
void registrarUnaEmpresa (stEmpresa* empresa);
int registrarseEmpresa (stEmpresa* empresa);
void guardarEmpresas (char archivo[], stEmpresa empresa);
int iniciarSesionEmpresa(char archivo[], stEmpresa *empresaActual);
void mostrarUnaEmpresa (stEmpresa empresa); //BORRAR MAS TARDE
void mostrarEmpresas (char archivo[]); //BORRAR MAS TARDE
void menuEmpresa(stEmpresa* empresaActual);
int generarIdUnicoEmpresa ();
void crearArchivoDeEmpresa(stEmpresa empresa);
void guardarJuegoEnArchivoEmpresa(stEmpresa empresa, stJuego juego);


#endif // EMPRESAS_H_INCLUDED

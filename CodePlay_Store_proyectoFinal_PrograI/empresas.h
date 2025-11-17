#ifndef EMPRESAS_H_INCLUDED
#define EMPRESAS_H_INCLUDED

#include "juegos.h"

#define ARCHIVO_EMPRESAS "empresas.dat"

typedef struct {
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct {
    char nombre[50];
    char email[50];
    char contrasenia[20];
    char pais[30];
    char descripcion[150];
    Fecha fechaRegistro;
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
void mostrarJuegosEmpresa(stJuego* arreglo, int validos);
int calcularDimensionArchivoEmpresa(char nombreArchivo[]);
int cargarArregloDesdeArchivoEmpresa (char nombreArchivo[], stJuego** arregloJuegos, int* dimension);
int buscarJuegoPorIdEmpresa(stJuego* arreglo, int validos, int idBuscado);
void modificarJuego(stJuego* arreglo, int validos);
int borrarJuego(stJuego* arreglo, int* validos);
void guardarArregloEnArchivoEmpresa(char nombreArchivo[], stJuego* arreglo, int validos);
void modificarDatosEmpresa(stEmpresa* empresaActual);
void actualizarEmpresaEnArchivo(stEmpresa empresa);
int validarEmailEmpresa (char email[]);
int validarNombreEmpresa (char nombreDeEmpresa[]);
int validarContraseniaEmpresa (char contrasenia[]);
int validarPais (char pais[]);
Fecha cargarFechaManualEmpresa();

#endif // EMPRESAS_H_INCLUDED

#ifndef JUEGOS_H_INCLUDED
#define JUEGOS_H_INCLUDED

#define ARCHIVO_JUEGOS "catalogo.dat"
#define ARCHIVO_PLATAFORMAS "plataformas.dat"

#include "usuarios.h"

typedef struct {
    int id;
    char nombre[50];
    char genero[30];
    char plataforma[20];
    float precio;
    int idEmpresa;
} stJuego;

// PROTOTIPADO
void catalogoJuegos(stLogin usuarioActual);
int existeArchivo ();
void inicializarCatalogo();
void mostrarCatalogo();
void mostrarUnJuego(stJuego juego);
int calcularDimensionArchivo();
stJuego* crearArregloJuegos(int dimension);
int cargarArregloDesdeArchivo (stJuego** arregloDeJuegos, int dimension);
int buscarJuegoPorNombre (stJuego* arregloDeJuegos, int validos, char juegoABuscar[]);
int buscarJuegoPorId (stJuego* arregloDeJuegos, int validos, int idABuscar);
void menuBusquedaJuegos(stJuego* arregloDeJuegos, int validos);
void buscarJuegosPorPlataforma(stJuego* arregloDeJuegos, int validos, char plataformaABuscar[]);
int generarIdUnicoJuego ();
void cargarUnJuego(stJuego* juego);
void agregarJuegoAlCatalogo(stJuego juego);
int agregarJuegoAlArreglo (stJuego** arregloJuegos, int* dimension, int* validos, stJuego juegoNuevo);
int redimensionarArreglo (stJuego** arregloJuegos, int* dimension, int adicional);
int buscarJuegoEnArchivoPorId(int idBuscado, stJuego *out);

#endif // JUEGOS_H_INCLUDED

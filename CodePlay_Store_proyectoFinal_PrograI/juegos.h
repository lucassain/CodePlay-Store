#ifndef JUEGOS_H_INCLUDED
#define JUEGOS_H_INCLUDED

#define ARCHIVO_JUEGOS "catalogo.dat"

typedef struct {
    int id;
    char nombre[30];
    char genero[20];
    float precio;
    int idEmpresaDuena;
} stJuego;

// PROTOTIPOS
void catalogoJuegos();
void inicializarCatalogo();
void mostrarCatalogo();
void mostrarUnJuego(stJuego juego);
int buscarJuegoPorNombre(char nombreBuscado[]);
void mostrarJuegoPorNombre();

#endif // JUEGOS_H_INCLUDED

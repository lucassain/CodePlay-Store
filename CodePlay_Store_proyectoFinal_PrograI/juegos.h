#ifndef JUEGOS_H_INCLUDED
#define JUEGOS_H_INCLUDED

#define ARCHIVO_JUEGOS "catalogo.dat"
#define ARCHIVO_PLATAFORMAS "plataformas.dat"

typedef struct {
    int id;
    char nombre[30];
    char genero[20];
    float precio;
    int idEmpresa;
} stJuego;

typedef struct {
    int idJuego;
    char nombre[20];
} stPlataforma;

// PROTOTIPADO
void catalogoJuegos();
void inicializarCatalogo();
void mostrarCatalogo();
void mostrarUnJuego(stJuego juego);


#endif // JUEGOS_H_INCLUDED

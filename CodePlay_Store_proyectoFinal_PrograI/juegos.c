#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juegos.h"

void catalogoJuegos()
{
    inicializarCatalogo();
    mostrarCatalogo();
    mostrarJuegoPorNombre();
}

void inicializarCatalogo() {
    FILE *buffer = fopen(ARCHIVO_JUEGOS, "rb");
    if(buffer) {
        fclose(buffer);
        return;
    }

    buffer = fopen(ARCHIVO_JUEGOS, "wb");

    stJuego iniciales[] = {
        {1, "GTA V", "Accion", 15000, 1},
        {2, "FIFA 24", "Deportes", 20000, 2},
        {3, "Minecraft", "Aventura", 12000, 3}
    };

    fwrite(iniciales, sizeof(stJuego), 3, buffer);
    fclose(buffer);

    printf("Catalogo inicial creado.\n");
}

void mostrarUnJuego(stJuego juego) {
    printf("\n");
    printf("ID: %i\nNombre: %s\nGenero: %s\nPrecio: $%.2f\nEmpresa Dueña: %i\n",
            juego.id, juego.nombre, juego.genero, juego.precio, juego.idEmpresaDuena);
}

void mostrarCatalogo() {
    FILE *buffer = fopen(ARCHIVO_JUEGOS, "rb");
    if(!buffer) {
        printf("No hay catalogo cargado.\n");
        return;
    }

    printf("\nCATALOGO DISPONIBLE \n");

    stJuego aux;
    while(fread(&aux, sizeof(stJuego), 1, buffer) == 1) {
        mostrarUnJuego(aux);
    }
    fclose(buffer);
}

int buscarJuegoPorNombre(char nombreBuscado[]) {
    FILE *buffer = fopen(ARCHIVO_JUEGOS, "rb");
    if(!buffer) {
        printf("No se pudo abrir el archivo.\n");
        return -1;
    }

    stJuego aux;
    int indice = 0;
    int encontrado = -1;

    while(fread(&aux, sizeof(stJuego), 1, buffer) == 1) {
        if(stricmp(aux.nombre, nombreBuscado) == 0) {
            encontrado = indice;
            break;
        }
        indice++;
    }

    fclose(buffer);
    return encontrado;
}

void mostrarJuegoPorNombre() {
    char nombre[30];
    printf("\nIngrese el nombre del juego a buscar: ");
    fflush(stdin);
    fgets(nombre, 30, stdin);

    nombre[strcspn(nombre, "\n")] = '\0';

    int pos = buscarJuegoPorNombre(nombre);

    if(pos == -1) {
        printf("Juego no encontrado.\n");
    } else {
        FILE *buffer = fopen(ARCHIVO_JUEGOS, "rb");
        stJuego aux;
        fseek(buffer, pos * sizeof(stJuego), SEEK_SET);
        fread(&aux, sizeof(stJuego), 1, buffer);
        fclose(buffer);

        printf("\n Juego encontrado:\n");
        mostrarUnJuego(aux);
    }
}

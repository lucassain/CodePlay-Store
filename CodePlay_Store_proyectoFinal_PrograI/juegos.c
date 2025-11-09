#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juegos.h"

void catalogoJuegos()
{
    inicializarCatalogo();
    int opcion=0;

    do
    {
        printf("\n=====CATALOGO DE JUEGOS=====\n");
        printf("Ver catalogo (1)\n");
        printf("0 PARA SALIR \n");
        printf("Ingrese una opcion: ");
        scanf("%i", &opcion);

        switch (opcion)
        {

        case 0:

            printf("Volviendo al menu principal...\n");
            return;

            break;
        case 1:

            mostrarCatalogo();

            break;

        default:

            printf("Opcion invalida. Ingrese otra opcion.\n");

            break;
        }

    }
    while (opcion!=0);

}

void inicializarCatalogo()
{
    FILE *buffer = fopen(ARCHIVO_JUEGOS, "rb");
    if(buffer)
    {
        fclose(buffer);
        return;
    }

    buffer = fopen(ARCHIVO_JUEGOS, "wb");

    stJuego iniciales[] =
    {
        {1, "GTA V", "Accion", 15000, 1},
        {2, "FIFA 24", "Deportes", 20000, 2},
        {3, "Minecraft", "Aventura", 12000, 3}
    };

    fwrite(iniciales, sizeof(stJuego), 3, buffer);
    fclose(buffer);

    printf("Catalogo inicial creado.\n");
}

void mostrarUnJuego(stJuego juego)
{
    printf("\n");
    printf("ID: %i\nNombre: %s\nGenero: %s\nPrecio: $%.2f\nEmpresa Dueña: %i\n",
           juego.id, juego.nombre, juego.genero, juego.precio, juego.idEmpresaDuena);
}

void mostrarCatalogo()
{
    FILE *buffer = fopen(ARCHIVO_JUEGOS, "rb");
    if(!buffer)
    {
        printf("No hay catalogo cargado.\n");
        return;
    }

    printf("\nCATALOGO DISPONIBLE \n");

    stJuego aux;
    while(fread(&aux, sizeof(stJuego), 1, buffer) == 1)
    {
        mostrarUnJuego(aux);
    }
    fclose(buffer);
}


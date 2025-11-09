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
    FILE* bufferJuegos = fopen(ARCHIVO_JUEGOS, "wb");
    FILE* bufferPlataformas = fopen(ARCHIVO_PLATAFORMAS, "wb");

    if(bufferJuegos!=NULL && bufferPlataformas!=NULL)
    {
        stJuego iniciales[] =
        {
            {1, "GTA V", "Accion", 15000, 1},
            {2, "FIFA 24", "Deportes", 20000, 2},
            {3, "Minecraft", "Aventura", 12000, 3},
            {4, "Cyberpunk 2077", "RPG", 22000, 4},
            {5, "Among Us", "Casual", 5000, 5},
            {6, "Elden Ring", "RPG", 28000, 6},
            {7, "CS:GO", "Shooter", 0, 7},
            {8, "Dota 2", "Estrategia", 0, 8},
            {9, "Hades", "Rogue-like", 13000, 9},
            {10, "The Witcher 3", "RPG", 18000, 10},
            {11, "Valheim", "Supervivencia", 14000, 11},
            {12, "Rust", "Supervivencia", 16000, 12},
            {13, "ARK", "Supervivencia", 17000, 13},
            {14, "Fall Guys", "Plataformas", 9000, 14},
            {15, "Subnautica", "Aventura", 15000, 15},
            {16, "Stardew Valley", "Simulacion", 10000, 16},
            {17, "No Man’s Sky", "Exploracion", 20000, 17},
            {18, "Terraria", "Aventura", 8000, 18},
            {19, "Portal 2", "Puzzle", 7000, 19},
            {20, "Left 4 Dead 2", "Shooter", 6000, 20},
            {21, "Garry’s Mod", "Sandbox", 4000, 21},
            {22, "The Forest", "Supervivencia", 13000, 22},
            {23, "Raft", "Supervivencia", 12000, 23},
            {24, "Slime Rancher", "Simulacion", 9000, 24},
            {25, "Hollow Knight", "Metroidvania", 11000, 25},
            {26, "Celeste", "Plataformas", 8000, 26},
            {27, "Cuphead", "Accion", 9500, 27},
            {28, "Red Dead 2", "Aventura", 23000, 28},
            {29, "Doom Eternal", "Shooter", 19000, 29},
            {30, "Dark Souls III", "RPG", 21000, 30},
            {31, "Sekiro", "Accion", 22000, 31},
            {32, "Far Cry 6", "Accion", 24000, 32},
            {33, "Assassin’s Creed Valhalla", "Aventura", 26000, 33},
            {34, "Watch Dogs 2", "Accion", 14000, 34},
            {35, "Forza Horizon 5", "Carreras", 28000, 35},
            {36, "Need for Speed Heat", "Carreras", 17000, 36},
            {37, "Overwatch 2", "Shooter", 0, 37},
            {38, "Valorant", "Shooter", 0, 38},
            {39, "League of Legends", "MOBA", 0, 39},
            {40, "Team Fortress 2", "Shooter", 0, 40},
            {41, "Baldur’s Gate 3", "RPG", 30000, 41},
            {42, "Phasmophobia", "Terror", 11000, 42},
            {43, "Dead by Daylight", "Terror", 13000, 43},
            {44, "Outlast", "Terror", 8000, 44},
            {45, "Resident Evil 4 Remake", "Terror", 29000, 45},
            {46, "It Takes Two", "Cooperativo", 16000, 46},
            {47, "A Way Out", "Cooperativo", 13000, 47},
            {48, "The Sims 4", "Simulacion", 9000, 48},
            {49, "Cities Skylines", "Construccion", 15000, 49},
            {50, "Planet Zoo", "Construccion", 18000, 50}
        };

        stPlataforma plataformas[] =
        {
            {1, "PC"}, {1, "PS4"}, {1, "Xbox"},
            {2, "PC"}, {2, "PS5"}, {2, "Xbox"},
            {3, "PC"}, {3, "PS4"}, {3, "Switch"},
            {4, "PC"}, {4, "PS5"}, {4, "Xbox"},
            {5, "PC"}, {5, "Mobile"},
            {6, "PC"}, {6, "PS5"}, {6, "Xbox"},
            {7, "PC"}, {7, "Mac"},
            {8, "PC"}, {8, "Mac"}, {8, "Linux"},
            {9, "PC"}, {9, "Switch"},
            {10, "PC"}, {10, "PS4"}, {10, "Xbox"},
            {11, "PC"}, {11, "Linux"},
            {12, "PC"}, {12, "PS4"}, {12, "Xbox"},
            {13, "PC"}, {13, "PS4"}, {13, "Xbox"},
            {14, "PC"}, {14, "PS4"}, {14, "Switch"},
            {15, "PC"}, {15, "PS4"}, {15, "Xbox"},
            {16, "PC"}, {16, "Switch"}, {16, "Mobile"},
            {17, "PC"}, {17, "PS5"}, {17, "Xbox"},
            {18, "PC"}, {18, "PS4"}, {18, "Switch"}, {18, "Mobile"},
            {19, "PC"}, {19, "PS4"}, {19, "Xbox"}, {19, "Mac"},
            {20, "PC"}, {20, "PS4"}, {20, "Xbox"},
            {21, "PC"}, {21, "Mac"},
            {22, "PC"}, {22, "PS4"}, {22, "VR"},
            {23, "PC"}, {23, "PS4"}, {23, "Switch"},
            {24, "PC"}, {24, "PS4"}, {24, "Xbox"}, {24, "Switch"},
            {25, "PC"}, {25, "PS4"}, {25, "Switch"},
            {26, "PC"}, {26, "PS4"}, {26, "Switch"}, {26, "Xbox"},
            {27, "PC"}, {27, "PS4"}, {27, "Switch"}, {27, "Xbox"},
            {28, "PC"}, {28, "PS4"}, {28, "Xbox"},
            {29, "PC"}, {29, "PS4"}, {29, "Xbox"},
            {30, "PC"}, {30, "PS4"}, {30, "Xbox"},
            {31, "PC"}, {31, "PS4"}, {31, "Xbox"},
            {32, "PC"}, {32, "PS5"}, {32, "Xbox"},
            {33, "PC"}, {33, "PS5"}, {33, "Xbox"},
            {34, "PC"}, {34, "PS4"}, {34, "Xbox"},
            {35, "PC"}, {35, "Xbox"}, {35, "SteamDeck"},
            {36, "PC"}, {36, "PS4"}, {36, "Xbox"},
            {37, "PC"}, {37, "PS5"}, {37, "Xbox"},
            {38, "PC"},
            {39, "PC"}, {39, "Mac"},
            {40, "PC"}, {40, "Mac"}, {40, "Linux"},
            {41, "PC"}, {41, "PS5"}, {41, "Mac"},
            {42, "PC"}, {42, "VR"},
            {43, "PC"}, {43, "PS4"}, {43, "Xbox"},
            {44, "PC"}, {44, "PS4"}, {44, "Xbox"},
            {45, "PC"}, {45, "PS5"}, {45, "Xbox"},
            {46, "PC"}, {46, "PS4"}, {46, "Xbox"},
            {47, "PC"}, {47, "PS4"}, {47, "Xbox"},
            {48, "PC"}, {48, "Mac"},
            {49, "PC"}, {49, "Mac"},
            {50, "PC"}, {50, "SteamDeck"}
        };

        fwrite(iniciales, sizeof(stJuego), 50, bufferJuegos);
        fwrite(plataformas, sizeof(stPlataforma),sizeof(plataformas)/sizeof(stPlataforma), bufferPlataformas);

        printf("Catalogo inicial creado.\n");

        fclose(bufferJuegos);
        fclose(bufferPlataformas);

    }
    else
    {
        printf("Error al iniciar el catalogo.\n");
    }

}

void mostrarUnJuego(stJuego juego)
{
    printf("\n");
    printf("ID: %i\nNombre: %s\nGenero: %s\nPrecio: $%.2f\nidEmpresa: %i\n",
           juego.id, juego.nombre, juego.genero, juego.precio, juego.idEmpresa);
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

int calcularDimensionArchivo()
{
    FILE *buffer = fopen(ARCHIVO_JUEGOS, "rb");
    int cantidad = 0;

    if(buffer!=NULL)
    {
        fseek(buffer, 0, SEEK_END);
        int bytes = ftell(buffer);
        fclose(buffer);

        cantidad = bytes / sizeof(stJuego);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }

    return cantidad;
}
stJuego* crearArregloJuegos(int dimension)
{
    stJuego *arr = NULL;

    if(dimension > 0)
    {
        arr = (stJuego*) malloc(sizeof(stJuego) * dimension);
        if(arr == NULL)
        {
            printf("Error al reservar memoria.\n");
        }
    }

    return arr;
}
void cargarDesdeArchivoAlArreglo(stJuego *arr, int dimension)
{
    FILE *buffer = fopen(ARCHIVO_JUEGOS, "rb");

    if(buffer!=NULL && arr != NULL)
    {
        fread(arr, sizeof(stJuego), dimension, buffer);
        fclose(buffer);
    }
    else
    {
        printf("Error al leer el archivo.\n");
    }
}
int cargarJuegosDesdeArchivo(stJuego **arr)
{
    int validos = calcularDimensionArchivo();

    *arr = crearArregloJuegos(validos);

    if(*arr != NULL && validos > 0)
    {
        cargarDesdeArchivoAlArreglo(*arr, validos);
    }

    return validos;
}

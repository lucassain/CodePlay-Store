#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juegos.h"
#include "transacciones.h"
#include "usuarios.h"
#include <ctype.h>

void catalogoJuegos(stLogin usuarioActual)
{
    system("cls");

    if (!existeArchivo())
    {
        inicializarCatalogo();
    }

    int dimension=calcularDimensionArchivo();
    stJuego* arregloDeJuegos=crearArregloJuegos(dimension);

    if (arregloDeJuegos==NULL)
    {
        printf("Cerrando programa...\n");
        return;
    }

    int validosJuegos=cargarArregloDesdeArchivo(&arregloDeJuegos, dimension);

    char opcion=0;

    do
    {
        printf("\n=====CATALOGO DE JUEGOS=====\n");
        printf("Ver catalogo(1)\n");
        printf("Buscar un juego (2)\n");
        printf("Comprar un juego (3)\n");
        printf("0 PARA SALIR \n");
        printf("Ingrese una opcion: ");
        scanf(" %c", &opcion);

        system("cls");

        switch (opcion)
        {

        case '0':

            printf("Volviendo al menu principal...\n");
            return;

        case '1':

            mostrarCatalogo();
            break;

        case '2':

            menuBusquedaJuegos(arregloDeJuegos, validosJuegos);
            break;

        case '3':

            procesarCompra(usuarioActual);
            break;

        default:

            printf("Opcion invalida. Ingrese otra opcion.\n");

            break;
        }

    }
    while (opcion!='0');

    free(arregloDeJuegos);
    arregloDeJuegos=NULL;

}

void inicializarCatalogo()
{
    FILE* bufferJuegos = fopen(ARCHIVO_JUEGOS, "wb");

    if(bufferJuegos!=NULL)
    {
        stJuego iniciales[] =
        {
            {1, "GTA V", "Accion", "PC", 15000, 1},
            {2, "FIFA 24", "Deportes", "PS5", 20000, 2},
            {3, "Minecraft", "Aventura", "PC", 12000, 3},
            {4, "Cyberpunk 2077", "RPG", "PC", 22000, 4},
            {5, "Among Us", "Casual", "PC", 5000, 5},
            {6, "Elden Ring", "RPG", "PS5", 28000, 6},
            {7, "CS:GO", "Shooter", "PC", 0, 7},
            {8, "Dota 2", "Estrategia", "PC", 0, 8},
            {9, "Hades", "Rogue-like", "Switch", 13000, 9},
            {10, "The Witcher 3", "RPG", "PC", 18000, 10},
            {11, "Valheim", "Supervivencia", "PC", 14000, 11},
            {12, "Rust", "Supervivencia", "PC", 16000, 12},
            {13, "ARK", "Supervivencia", "PC", 17000, 13},
            {14, "Fall Guys", "Plataformas", "PS4", 9000, 14},
            {15, "Subnautica", "Aventura", "PC", 15000, 15},
            {16, "Stardew Valley", "Simulacion", "Switch", 10000, 16},
            {17, "No Man's Sky", "Exploracion", "PS5", 20000, 17},
            {18, "Terraria", "Aventura", "PC", 8000, 18},
            {19, "Portal 2", "Puzzle", "PC", 7000, 19},
            {20, "Left 4 Dead 2", "Shooter", "PC", 6000, 20},
            {21, "Garry's Mod", "Sandbox", "PC", 4000, 21},
            {22, "The Forest", "Supervivencia", "PC", 13000, 22},
            {23, "Raft", "Supervivencia", "PC", 12000, 23},
            {24, "Slime Rancher", "Simulacion", "PC", 9000, 24},
            {25, "Hollow Knight", "Metroidvania", "Switch", 11000, 25},
            {26, "Celeste", "Plataformas", "Switch", 8000, 26},
            {27, "Cuphead", "Accion", "Xbox", 9500, 27},
            {28, "Red Dead 2", "Aventura", "PS4", 23000, 28},
            {29, "Doom Eternal", "Shooter", "PC", 19000, 29},
            {30, "Dark Souls III", "RPG", "PC", 21000, 30},
            {31, "Sekiro", "Accion", "PC", 22000, 31},
            {32, "Far Cry 6", "Accion", "PS5", 24000, 32},
            {33, "Assassin's Creed Valhalla", "Aventura", "PS5", 26000, 33},
            {34, "Watch Dogs 2", "Accion", "PC", 14000, 34},
            {35, "Forza Horizon 5", "Carreras", "Xbox", 28000, 35},
            {36, "Need for Speed Heat", "Carreras", "PS4", 17000, 36},
            {37, "Overwatch 2", "Shooter", "PC", 0, 37},
            {38, "Valorant", "Shooter", "PC", 0, 38},
            {39, "League of Legends", "MOBA", "PC", 0, 39},
            {40, "Team Fortress 2", "Shooter", "PC", 0, 40},
            {41, "Baldur's Gate 3", "RPG", "PC", 30000, 41},
            {42, "Phasmophobia", "Terror", "PC", 11000, 42},
            {43, "Dead by Daylight", "Terror", "PC", 13000, 43},
            {44, "Outlast", "Terror", "PC", 8000, 44},
            {45, "Resident Evil 4 Remake", "Terror", "PS5", 29000, 45},
            {46, "It Takes Two", "Cooperativo", "PS4", 16000, 46},
            {47, "A Way Out", "Cooperativo", "PS4", 13000, 47},
            {48, "The Sims 4", "Simulacion", "PC", 9000, 48},
            {49, "Cities Skylines", "Construccion", "PC", 15000, 49},
            {50, "Planet Zoo", "Construccion", "PC", 18000, 50}
        };

        fwrite(iniciales, sizeof(stJuego), 50, bufferJuegos);

        printf("Catalogo inicial creado.\n");

        fclose(bufferJuegos);

    }
    else
    {
        printf("Error al iniciar el catalogo.\n");
    }

}

void mostrarUnJuego(stJuego juego)
{
    printf("\n");
    printf("ID: %i\nNombre: %s\nGenero: %s\nPlataforma: %s \nPrecio: $%.2f\nidEmpresa: %i\n",
           juego.id, juego.nombre, juego.genero, juego.plataforma, juego.precio, juego.idEmpresa);
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

        cantidad = bytes / sizeof(stJuego);

        fclose(buffer);

    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }

    return cantidad;
}

stJuego* crearArregloJuegos(int dimension)
{
    if (dimension <= 0)
        dimension = 1; // evita malloc(0)

    stJuego* arreglo = (stJuego*) malloc(sizeof(stJuego) * dimension);

    return arreglo; // si falla, SÍ será NULL
}

int cargarArregloDesdeArchivo (stJuego** arregloDeJuegos, int dimension)
{
    FILE* buffer=fopen(ARCHIVO_JUEGOS, "rb");
    int validos=0;

    if (buffer!=NULL)
    {
        stJuego aux;
        while(fread(&aux, sizeof(stJuego), 1, buffer)==1)
        {
            (*arregloDeJuegos)[validos]=aux;
            validos++;
        }

        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
    return validos;
}

int existeArchivo()
{
    FILE* buffer=fopen(ARCHIVO_JUEGOS, "rb");

    if (buffer!=NULL)
    {
        fclose(buffer);
        return 1;
    }
    return 0;
}

int buscarJuegoPorNombre (stJuego* arregloDeJuegos, int validos, char juegoABuscar[])
{
    juegoABuscar[strcspn(juegoABuscar, "\n")] = 0;

    for (int i=0; i<validos; i++)
    {
        if (strcmpi (arregloDeJuegos[i].nombre, juegoABuscar)==0)
        {
            return i;
        }
    }
    printf("El juego ingresado no se encuentra.\n");
    return -1;
}

int buscarJuegoPorId (stJuego* arregloDeJuegos, int validos, int idABuscar)
{
    for (int i=0; i<validos; i++)
    {
        if (arregloDeJuegos[i].id==idABuscar)
        {
            return i;
        }
    }
    printf("El juego ingresado no se encuentra.\n");
    return -1;
}

void menuBusquedaJuegos(stJuego* arregloDeJuegos, int validos)
{
    char eleccion = -1;

    do
    {
        system("cls");

        printf("\n===== MENU BUSQUEDA DE JUEGOS =====\n");
        printf("Buscar por nombre (1)\n");
        printf("Buscar por ID (2)\n");
        printf("Buscar por plataforma (3)\n");
        printf("Volver al menu anterior (0)\n");
        printf("Ingrese una opcion: ");
        scanf(" %c", &eleccion);

        int indice;
        char busqueda[50];

        switch (eleccion)
        {
        case '0':
            printf("Volviendo...\n");
            break;

        case '1':
            printf("Ingresar nombre: ");
            scanf(" %[^\n]", busqueda);

            indice = buscarJuegoPorNombre(arregloDeJuegos, validos, busqueda);

            if (indice != -1)
                mostrarUnJuego(arregloDeJuegos[indice]);
            else
                printf("Juego no encontrado.\n");

            break;

        case '2':
            printf("Ingresar ID: ");
            int id;
            scanf("%d", &id);

            indice = buscarJuegoPorId(arregloDeJuegos, validos, id);

            if (indice != -1)
                mostrarUnJuego(arregloDeJuegos[indice]);
            else
                printf("Juego no encontrado.\n");

            break;

        case '3':
            printf("Ingresar plataforma: ");
            scanf(" %[^\n]", busqueda);

            buscarJuegosPorPlataforma(arregloDeJuegos, validos, busqueda);
            break;

        default:
            printf("Opcion invalida.\n");
            break;
        }

        system("pause");

    } while (eleccion != '0');
}


void buscarJuegosPorPlataforma(stJuego* arregloDeJuegos, int validos, char plataformaABuscar[])
{
    plataformaABuscar[strcspn(plataformaABuscar, "\n")] = 0;
    int encontrados = 0;

    for (int i = 0; i < validos; i++)
    {
        if (strcmpi(arregloDeJuegos[i].plataforma, plataformaABuscar) == 0)
        {
            mostrarUnJuego(arregloDeJuegos[i]);
            printf("\n");
            encontrados++;
        }
    }

    if (encontrados == 0)
    {
        printf("No se encontraron juegos para la plataforma ingresada.\n");
    }
}

int generarIdUnicoJuego ()
{
    FILE* buffer=fopen(ARCHIVO_JUEGOS, "rb");
    int idMax=0;

    if (buffer!=NULL)
    {
        stJuego aux;

        while(fread(&aux, sizeof(stJuego), 1, buffer)==1)
        {
            if (aux.id>idMax)
            {
                idMax=aux.id;
            }
        }

        fclose(buffer);
    }
    else
    {
        printf("Error al generar id.\n");
        return 0;
    }

    return idMax+1;
}

void cargarUnJuego(stJuego* juego)
{
    do
    {
        printf("Nombre del juego: ");
        fgets(juego->nombre, sizeof(juego->nombre), stdin);
        juego->nombre[strcspn(juego->nombre, "\n")] = 0; // Saca el \n
    }
    while(!validarNombreJuego(juego->nombre));

    do
    {
        printf("Genero: ");
        fgets(juego->genero, sizeof(juego->genero), stdin);
        juego->genero[strcspn(juego->genero, "\n")] = 0;
    }
    while (!validarGenero(juego->genero));

    do
    {
        printf("Plataforma: ");
        fgets(juego->plataforma, sizeof(juego->plataforma), stdin);
        juego->plataforma[strcspn(juego->plataforma, "\n")] = 0;
    }
    while(!validarPlataforma(juego->plataforma));

    do
    {
        printf("Precio: ");
        scanf("%f", &juego->precio);
    }
    while(!validarPrecio(juego->precio));
}


void agregarJuegoAlCatalogo(stJuego juego)
{
    FILE* buffer = fopen(ARCHIVO_JUEGOS, "ab");
    if(buffer != NULL)
    {
        fwrite(&juego, sizeof(stJuego), 1, buffer);
        fclose(buffer);
    }
    else
    {
        printf("Error al agregar el juego al catalogo.\n");
    }
}

int redimensionarArreglo (stJuego** arregloJuegos, int* dimension, int adicional)
{
    int nuevaDim=*dimension+adicional;

    stJuego* aux=(stJuego*)realloc(*arregloJuegos, nuevaDim*sizeof(stJuego));

    if (aux!=NULL)
    {
        (*arregloJuegos)=aux;

        *dimension=nuevaDim;

        return 1;
    }

    return 0;
}

int agregarJuegoAlArreglo (stJuego** arregloJuegos, int* dimension, int* validos, stJuego juegoNuevo)
{
    if (*validos==*dimension)
    {
        int redimensionado=redimensionarArreglo(arregloJuegos, dimension, 1);

        if (!redimensionado)
        {
            printf("Error al cargar el juego en el catalogo.\n");
            return 0;
        }
    }

    (*arregloJuegos)[*validos]=juegoNuevo;
    (*validos)++;

    return 1;
}

int buscarJuegoEnArchivoPorId(int idBuscado, stJuego *out)
{
    FILE *f = fopen(ARCHIVO_JUEGOS, "rb");
    if (!f) return 0;

    stJuego j;
    int encontrado = 0;

    while (fread(&j, sizeof(stJuego), 1, f) == 1)
    {
        if (j.id == idBuscado)
        {
            if (out != NULL)
            {
                *out = j;   // Copia el juego encontrado
            }
            encontrado = 1;
            break;
        }
    }
    fclose(f);
    return encontrado;  // 1 si lo encontró, 0 si no
}

void aMinusculas(char s[])
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        s[i] = tolower(s[i]);
    }
}

int validarNombreJuego(char nombre[])
{
    if (strlen(nombre) < 2)
    {
        printf("El nombre del juego es demasiado corto.\n");
        return 0;
    }

    for (int i = 0; i < strlen(nombre); i++)
    {
        char c = nombre[i];

        if ((c >= 'A' && c <= 'Z') ||
                (c >= 'a' && c <= 'z') ||
                (c >= '0' && c <= '9') ||
                c == ' ' || c == '-' || c == '\'')
        {
            // válido
        }
        else
        {
            printf("El nombre contiene caracteres invalidos.\n");
            return 0;
        }
    }

    return 1;
}

int validarGenero(char genero[])
{
    char copia[50];
    strcpy(copia, genero);
    aMinusculas(copia);

    char generosValidos[][20] =
    {
        "accion",
        "aventura",
        "rpg",
        "shooter",
        "deportes",
        "carreras",
        "puzzle",
        "plataformas",
        "lucha",
        "terror"
    };

    int cantidad = 10;

    for (int i = 0; i < cantidad; i++)
    {
        if (strcmp(copia, generosValidos[i]) == 0)
            return 1;
    }

    printf("Genero invalido. Intente nuevamente.\n");
    return 0;
}

int validarPlataforma(char plataforma[])
{
    char copia[20];
    strcpy(copia, plataforma);
    aMinusculas(copia);

    char plataformasValidas[][10] =
    {
        "pc",
        "ps4",
        "ps5",
        "xbox",
        "switch"
    };

    int cantidad = 5;

    for (int i = 0; i < cantidad; i++)
    {
        if (strcmp(copia, plataformasValidas[i]) == 0)
            return 1;
    }

    printf("Plataforma invalida. Use PC, PS4, PS5, XBOX o Switch.\n");
    return 0;
}

int validarPrecio(float precio)
{
    if (precio <= 0)
    {
        printf("El precio debe ser mayor que 0.\n");
        return 0;
    }

    if (precio > 200000)
    {
        printf("Precio demasiado alto. Revise el valor.\n");
        return 0;
    }

    return 1;
}

int juegoExisteEnArchivo(char nombre[], char plataforma[])
{
    FILE *pArch = fopen(ARCHIVO_JUEGOS, "rb");
    if (!pArch)
        return 0;

    char nomBuscado[50];
    char platBuscada[20];

    strcpy(nomBuscado, nombre);
    strcpy(platBuscada, plataforma);

    aMinusculas(nomBuscado);
    aMinusculas(platBuscada);

    stJuego aux;
    while (fread(&aux, sizeof(stJuego), 1, pArch) == 1)
    {
        char nomAux[50];
        char platAux[20];

        strcpy(nomAux, aux.nombre);
        strcpy(platAux, aux.plataforma);

        aMinusculas(nomAux);
        aMinusculas(platAux);

        if (strcmp(nomAux, nomBuscado) == 0 &&
            strcmp(platAux, platBuscada) == 0)
        {
            fclose(pArch);
            return 1;
        }
    }

    fclose(pArch);
    return 0;
}

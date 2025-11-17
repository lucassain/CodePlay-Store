#include <stdio.h>
#include <stdlib.h>
#include "empresas.h"
#include <string.h>
#include "juegos.h"

int loginEmpresas(stEmpresa *empresaActual)
{
    int registro = 0;
    char opcion;
    stEmpresa empresa;

    do
    {
        mostrarEmpresas(ARCHIVO_EMPRESAS);

        printf("\n=== MENU EMPRESA ===\n");
        printf("Iniciar sesion (I)\n");
        printf("Registrarse (R)\n");
        printf("Volver al menu principal (S)\n");
        printf("Ingrese una opcion: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case 'i':
        case 'I':
            if (iniciarSesionEmpresa(ARCHIVO_EMPRESAS, empresaActual) == 1)
            {
                return 1;
            }
            else
            {
                printf("Credenciales incorrectas.\n");
            }
            break;

        case 'r':
        case 'R':
            registro = registrarseEmpresa(&empresa);

            if (registro == 1)
            {
                printf("Empresa registrada correctamente.\n");
                guardarEmpresas(ARCHIVO_EMPRESAS, empresa);

                crearArchivoDeEmpresa(empresa);
            }
            else if (registro == -1)
            {
                printf("La empresa ya existe.\n");
            }
            else
            {
                printf("Error al registrarse.\n");
            }
            break;

        case 's':
        case 'S':
            printf("Volviendo al menu principal...\n");
            return 0;

        default:
            printf("Opcion invalida.\n");
        }

    }
    while (opcion != 's' && opcion != 'S');

    return 0;
}

void registrarUnaEmpresa (stEmpresa* empresa)
{
    printf("Nombre de la empresa: ");
    scanf("%s", empresa->nombre);

    printf("Mail de contacto: ");
    scanf("%s", empresa->email);

    printf("Pais: ");
    scanf("%s", empresa->pais);

    printf("Contrasenia: ");
    scanf("%s", empresa->contrasenia);

    printf("Fecha de registro: ");
    scanf("%s", empresa->fechaRegistro);

    fflush(stdin);

    printf("Ingrese una breve descripcion de la empresa: ");
    fgets(empresa->descripcion, 150, stdin);

    empresa->idEmpresa=generarIdUnicoEmpresa();
}

int registrarseEmpresa (stEmpresa* empresa)
{
    printf("REGISTRARSE COMO EMPRESA\n");

    registrarUnaEmpresa(empresa);

    if (strlen(empresa->nombre)>0 && strlen(empresa->email)>0 &&
            strlen(empresa->contrasenia)>0 && strlen(empresa->pais)>0 &&
            strlen(empresa->descripcion)>0 && strlen(empresa->fechaRegistro)>0)
    {
        return 1;

    }
    else
    {
        return 0;
    }
}


void guardarEmpresas (char archivo[], stEmpresa empresa)
{
    FILE* buffer=fopen(archivo, "ab");

    if (buffer!=NULL)
    {
        fwrite(&empresa, sizeof(stEmpresa), 1, buffer);

        fclose(buffer);
    }
    else

    {
        printf("Error al guardar la empresa en el archivo.\n");
    }
}

int iniciarSesionEmpresa(char archivo[], stEmpresa *empresaActual)
{
    stEmpresa ingreso;
    stEmpresa guardado;
    int encontrado = 0;

    FILE* buffer = fopen(archivo, "rb");
    if(buffer == NULL)
    {
        printf("Error al abrir el archivo de empresas.\n");
        return 0;
    }

    printf("\nINICIAR SESION EMPRESA\n");

    printf("Email: ");
    scanf("%s", ingreso.email);
    printf("Contrasenia: ");
    scanf("%s", ingreso.contrasenia);

    while(fread(&guardado, sizeof(stEmpresa), 1, buffer) == 1)
    {
        if(strcmp(ingreso.email, guardado.email) == 0 &&
                strcmp(ingreso.contrasenia, guardado.contrasenia) == 0)
        {
            printf("Inicio de sesion exitoso. Bienvenido %s!\n", guardado.nombre);
            *empresaActual = guardado;
            encontrado = 1;
            break;
        }
    }

    fclose(buffer);

    if(!encontrado)
    {
        printf("Email o contrasenia incorrectos.\n");
    }

    return encontrado;
}

void mostrarUnaEmpresa (stEmpresa empresa) //BORRAR MAS TARDE
{
    printf("Nombre de empresa: %s\n", empresa.nombre);
    printf("Direccion de correo electronico: %s\n", empresa.email);
    printf("Contrasenia: %s\n", empresa.contrasenia);
    printf("Pais: %s\n", empresa.pais);
    printf("Descripcion: %s\n", empresa.descripcion);
    printf("Fecha de registro: %s\n", empresa.fechaRegistro);
    printf("Id empresa: %i\n", empresa.idEmpresa);

}

void mostrarEmpresas (char archivo[]) //BORRAR MAS TARDE
{
    FILE* buffer=fopen(archivo, "rb");
    stEmpresa empresa;

    if (buffer!=NULL)
    {
        while (fread(&empresa, sizeof(stEmpresa), 1, buffer))
        {
            mostrarUnaEmpresa(empresa);
        }
        fclose(buffer);
    }
}

void menuEmpresa(stEmpresa* empresaActual)
{
    char archivoEmpresa[200];
    sprintf(archivoEmpresa, "juegos_%s.dat", empresaActual->email);

    // Calcular dimension inicial
    int dimension = calcularDimensionArchivoEmpresa(archivoEmpresa);

    // Si no hay juegos todavía, evitamos malloc(0)
    if (dimension <= 0)
    {
        dimension = 1;
    }

    // Crear arreglo dinámico
    stJuego* arregloDeJuegos = crearArregloJuegos(dimension);

    if (arregloDeJuegos == NULL)
    {
        printf("Error al reservar memoria para juegos.\n");
        return;
    }

    // Cargar juegos desde el archivo de la empresa
    int validos = cargarArregloDesdeArchivoEmpresa(archivoEmpresa, &arregloDeJuegos, &dimension);

    char opcion;

    do
    {
        printf("\n===== MENU EMPRESA =====\n");
        printf("1 - Publicar nuevo juego\n");
        printf("2 - Ver mis juegos\n");
        printf("3 - Modificar un juego\n");
        printf("4 - Borrar un juego\n");
        printf("5 - Modificar datos de la empresa\n");
        printf("0 - Cerrar sesion\n");
        printf("Seleccione una opcion: ");
        scanf(" %c", &opcion);
        getchar();

        switch (opcion)
        {
        case '1':
        {
            stJuego juegoNuevo;

            printf("Ingrese los datos del nuevo juego:\n");
            cargarUnJuego(&juegoNuevo);
            getchar();

            juegoNuevo.id = generarIdUnicoJuego();
            juegoNuevo.idEmpresa = empresaActual->idEmpresa;

            // Guardar en archivo propio de la empresa
            guardarJuegoEnArchivoEmpresa(*empresaActual, juegoNuevo);

            // Guardar en arreglo dinámico de la empresa
            if (agregarJuegoAlArreglo(&arregloDeJuegos, &dimension, &validos, juegoNuevo) == 1)
            {
                printf("Juego agregado correctamente.\n");

                // Guardar también en el archivo general del catálogo
                agregarJuegoAlCatalogo(juegoNuevo);
            }
            else
            {
                printf("Error al agregar el juego.\n");
            }

            break;
        }

        case '2':
            mostrarJuegosEmpresa(arregloDeJuegos, validos);
            break;

        case '3':
            modificarJuego(arregloDeJuegos, validos);
            guardarArregloEnArchivoEmpresa(archivoEmpresa, arregloDeJuegos, validos);
            break;

        case '4':
            if (borrarJuego(arregloDeJuegos, &validos))
            {
                guardarArregloEnArchivoEmpresa(archivoEmpresa, arregloDeJuegos, validos);
            }
            break;

        case '5':

             modificarDatosEmpresa(empresaActual);  // llamar función de modificación
            actualizarEmpresaEnArchivo(*empresaActual);  // guardar cambios en archivo

            break;

        case '0':
            printf("Sesion cerrada.\n");
            break;

        default:
            printf("Opcion invalida.\n");
        }

    }
    while (opcion != '0');

    free(arregloDeJuegos);
    arregloDeJuegos = NULL;
}


int generarIdUnicoEmpresa()
{
    FILE* buffer=fopen(ARCHIVO_EMPRESAS, "rb");
    int idMax=0;

    if (buffer!=NULL)
    {
        stEmpresa aux;

        while(fread(&aux, sizeof(stEmpresa), 1, buffer)==1)
        {
            if (aux.idEmpresa>idMax)
            {
                idMax=aux.idEmpresa;
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

void crearArchivoDeEmpresa(stEmpresa empresa)
{
    char archivoEmpresa[200];
    sprintf(archivoEmpresa, "juegos_%s.dat", empresa.email);

    FILE* buffer = fopen(archivoEmpresa, "ab");
    if (buffer != NULL)
    {
        fclose(buffer);
    }
    else
    {
        printf("No se pudo crear el archivo %s\n", archivoEmpresa);
    }
}

void guardarJuegoEnArchivoEmpresa(stEmpresa empresa, stJuego juego)
{
    char archivoEmpresa[200];
    sprintf(archivoEmpresa, "juegos_%s.dat", empresa.email);

    FILE* buffer = fopen(archivoEmpresa, "ab");
    if(buffer != NULL)
    {
        fwrite(&juego, sizeof(stJuego), 1, buffer);
        fclose(buffer);
    }
    else
    {
        printf("Error al guardar el juego en el archivo de la empresa.\n");
    }
}


void mostrarJuegosEmpresa(stJuego* arreglo, int validos)
{
    printf("\n--- Juegos de la Empresa ---\n\n");

    for (int i=0; i<validos; i++)
    {
        mostrarUnJuego(arreglo[i]);
    }

    if(validos == 0)
    {
        printf("No hay juegos cargados.\n");
    }
}

int calcularDimensionArchivoEmpresa(char nombreArchivo[])
{
    FILE *buffer = fopen(nombreArchivo, "rb");
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

int cargarArregloDesdeArchivoEmpresa (char nombreArchivo[], stJuego** arregloJuegos, int* dimension)
{
    FILE* buffer = fopen(nombreArchivo, "rb");
    int validos = 0;

    if (buffer != NULL)
    {
        stJuego aux;

        while (fread(&aux, sizeof(stJuego), 1, buffer) == 1)
        {
            if (validos == *dimension)
            {
                int ok = redimensionarArreglo(arregloJuegos, dimension, 1);

                if (!ok)
                {
                    printf("No hay memoria para agregar mas juegos.\n");
                    fclose(buffer);
                    return validos;
                }
            }

            (*arregloJuegos)[validos] = aux;
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

int buscarJuegoPorIdEmpresa(stJuego* arreglo, int validos, int idBuscado)
{
    for (int i = 0; i < validos; i++)
    {
        if (arreglo[i].id == idBuscado)
        {
            return i;
        }
    }
    return -1;
}

void modificarJuego(stJuego* arreglo, int validos)
{
    int id;
    printf("Ingrese el ID del juego que desea modificar: ");
    scanf("%d", &id);

    int pos = buscarJuegoPorId(arreglo, validos, id);

    if (pos == -1)
    {
        printf("No existe un juego con ese ID.\n");
        return;
    }

    printf("\nModificando el juego:\n");
    mostrarUnJuego(arreglo[pos]);

    char opcion;

    printf("\n=== MODIFICAR CAMPOS ===\n");

    // NOMBRE
    printf("¿Desea cambiar el nombre? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S')
    {
        printf("Nuevo nombre: ");
        fflush(stdin);
        fgets(arreglo[pos].nombre, 50, stdin);
        arreglo[pos].nombre[strcspn(arreglo[pos].nombre, "\n")] = 0;
    }

    // GENERO
    printf("¿Desea cambiar el género? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S')
    {
        printf("Nuevo género: ");
        fflush(stdin);
        fgets(arreglo[pos].genero, 30, stdin);
        arreglo[pos].genero[strcspn(arreglo[pos].genero, "\n")] = 0;
    }

    // PLATAFORMA
    printf("¿Desea cambiar la plataforma? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S')
    {
        printf("Nueva plataforma: ");
        fflush(stdin);
        fgets(arreglo[pos].plataforma, 20, stdin);
        arreglo[pos].plataforma[strcspn(arreglo[pos].plataforma, "\n")] = 0;
    }

    // PRECIO
    printf("¿Desea cambiar el precio? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S')
    {
        printf("Nuevo precio: ");
        scanf("%f", &arreglo[pos].precio);
    }

    printf("\nJuego modificado correctamente.\n");
}

int borrarJuego(stJuego* arreglo, int* validos)
{
    int id;
    printf("Ingrese el ID del juego que desea borrar: ");
    scanf("%d", &id);

    int pos = buscarJuegoPorId(arreglo, *validos, id);

    if (pos == -1)
    {
        printf("No existe un juego con ese ID.\n");
        return 0;
    }

    for (int i = pos; i < *validos - 1; i++)
    {
        arreglo[i] = arreglo[i + 1];
    }

    (*validos)--;

    printf("Juego borrado correctamente.\n");

    return 1;
}

void guardarArregloEnArchivoEmpresa(char nombreArchivo[], stJuego* arreglo, int validos)
{
    FILE* buffer = fopen(nombreArchivo, "wb");

    if (buffer != NULL)
    {
        for (int i = 0; i < validos; i++)
        {
            fwrite(&arreglo[i], sizeof(stJuego), 1, buffer);
        }
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir el archivo para escribir.\n");
    }
}

void modificarDatosEmpresa(stEmpresa* empresaActual)
{
    stEmpresa modificado = *empresaActual;
    char opcion;

    printf("\n=== MODIFICAR DATOS DE LA EMPRESA ===\n");

    // NOMBRE
    printf("¿Desea cambiar el nombre de la empresa? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S')
    {
        printf("Nuevo nombre: ");
        scanf("%s", modificado.nombre);
    }

    // EMAIL
    printf("¿Desea cambiar el email de contacto? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S')
    {
        printf("Nuevo email: ");
        scanf("%s", modificado.email);
    }

    // PAIS
    printf("¿Desea cambiar el país? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S')
    {
        printf("Nuevo país: ");
        scanf("%s", modificado.pais);
    }

    // CONTRASEÑA
    printf("¿Desea cambiar la contraseña? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S')
    {
        printf("Nueva contraseña: ");
        scanf("%s", modificado.contrasenia);
    }

    // DESCRIPCIÓN
    printf("¿Desea cambiar la descripción? (s/n): ");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S')
    {
        fflush(stdin);
        printf("Nueva descripción: ");
        fgets(modificado.descripcion, 150, stdin);
        modificado.descripcion[strcspn(modificado.descripcion, "\n")] = '\0';
    }

    // CONFIRMAR
    printf("\n¿Confirmar modificaciones? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S')
    {
        *empresaActual = modificado;
        printf("Datos modificados correctamente.\n");
    }
    else
    {
        printf("Modificación cancelada.\n");
    }
}

void actualizarEmpresaEnArchivo(stEmpresa empresa)
{
    FILE* buffer = fopen(ARCHIVO_EMPRESAS, "r+b"); // abrir en modo lectura/escritura binaria
    if (buffer == NULL)
    {
        printf("No se pudo abrir el archivo de empresas.\n");
        return;
    }

    stEmpresa aux;
    int encontrado = 0;

    while(fread(&aux, sizeof(stEmpresa), 1, buffer) == 1)
    {
        if(aux.idEmpresa == empresa.idEmpresa)
        {
            // mover el puntero del archivo al inicio del registro encontrado
            fseek(buffer, -(long)sizeof(stEmpresa), SEEK_CUR);
            fwrite(&empresa, sizeof(stEmpresa), 1, buffer);
            encontrado = 1;
            break;
        }
    }

    fclose(buffer);

    if(encontrado)
        printf("Datos de la empresa actualizados en el archivo.\n");
    else
        printf("No se encontró la empresa en el archivo.\n");
}

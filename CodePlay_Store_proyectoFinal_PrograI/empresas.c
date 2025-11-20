#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "empresas.h"
#include <string.h>
#include "juegos.h"
#include "transacciones.h"

int loginEmpresas(stEmpresa *empresaActual)
{
    int registro = 0;
    char opcion;
    stEmpresa empresa;

    do
    {
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
            Sleep(800);
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
    do{
    printf("Nombre de la empresa: ");
    scanf("%s", empresa->nombre);
      } while(!validarNombreEmpresa(empresa->nombre));

    do{
    printf("Mail de contacto: ");
    scanf("%s", empresa->email);
   } while(!validarEmailEmpresa(empresa->email));

   do{
    printf("Pais: ");
    scanf("%s", empresa->pais);
   } while(!validarPais(empresa->pais));

   do{
    printf("Contrasenia: ");
    scanf("%s", empresa->contrasenia);
   }while(!validarContraseniaEmpresa(empresa->contrasenia));


    printf("Fecha de registro: ");
    empresa->fechaRegistro=cargarFechaManualEmpresa();

    fflush(stdin);

    empresa->idEmpresa=generarIdUnicoEmpresa();
}

int registrarseEmpresa (stEmpresa* empresa)
{
    system("cls");
    printf("REGISTRARSE COMO EMPRESA\n");

    registrarUnaEmpresa(empresa);
    return 1;


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
    system("cls");
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
            Sleep(800);
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

void mostrarUnaEmpresa (stEmpresa empresa)
{
    printf("Nombre de empresa: %s\n", empresa.nombre);
    printf("Direccion de correo electronico: %s\n", empresa.email);
    printf("Contrasenia: %s\n", empresa.contrasenia);
    printf("Pais: %s\n", empresa.pais);
    printf("Descripcion: %s\n", empresa.descripcion);
    printf("Fecha de registro: %i/%i/%i\n", empresa.fechaRegistro.dia, empresa.fechaRegistro.mes, empresa.fechaRegistro.anio);
    printf("Id empresa: %i\n", empresa.idEmpresa);

}

void mostrarEmpresas (char archivo[])
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

    int dimension = calcularDimensionArchivoEmpresa(archivoEmpresa);

    if (dimension <= 0)
    {
        dimension = 1;
    }

    stJuego* arregloDeJuegos = crearArregloJuegos(dimension);

    if (arregloDeJuegos == NULL)
    {
        printf("Error al reservar memoria para juegos.\n");
        return;
    }

    int validos = cargarArregloDesdeArchivoEmpresa(archivoEmpresa, &arregloDeJuegos, &dimension);

    char opcionStr[10];
    char opcion;

    do
    {
        system("cls");
        printf("\n===== MENU EMPRESA =====\n");
        printf("Publicar nuevo juego (1)\n");
        printf("Ver mis juegos (2)\n");
        printf("Modificar un juego (3)\n");
        printf("Borrar un juego (4)\n");
        printf("Modificar datos de la empresa (5)\n");
        printf("Cerrar sesion (0)\n");
        printf("Seleccione una opcion: ");
        scanf("%9s", opcionStr);

        opcion = opcionStr[0];

        if (opcion != '0' && opcion != '1' && opcion != '2' && opcion != '3' && opcion!='4' && opcion!='5')
        {
            printf("Opcion invalida. Intente nuevamente.\n");
            Sleep(1000);
            system("cls");
            continue;
        }

        switch (opcion)
        {
        case '1':
            stJuego juegoNuevo;

            printf("Ingrese los datos del nuevo juego:\n");
            cargarUnJuego(&juegoNuevo);
            getchar();

            if (juegoExisteEnArchivo(juegoNuevo.nombre, juegoNuevo.plataforma))
            {
                printf("El juego publicado ya existe.\n");
                return;
            }

            juegoNuevo.id = generarIdUnicoJuego();
            juegoNuevo.idEmpresa = empresaActual->idEmpresa;

            guardarJuegoEnArchivoEmpresa(*empresaActual, juegoNuevo);

            if (agregarJuegoAlArreglo(&arregloDeJuegos, &dimension, &validos, juegoNuevo) == 1)
            {
                printf("Juego agregado correctamente.\n");

                agregarJuegoAlCatalogo(juegoNuevo);
            }
            else
            {
                printf("Error al agregar el juego.\n");
            }

            break;

        case '2':
            mostrarJuegosEmpresa(arregloDeJuegos, validos);
            system("pause");
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

             modificarDatosEmpresa(empresaActual);
            actualizarEmpresaEnArchivo(*empresaActual);

            break;

        case '0':
            printf("Sesion cerrada.\n");
            Sleep(800);
            break;

        default:

            break;
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
    scanf("%i", &id);
    limpiarBuffer();

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

    printf("¿Desea cambiar el nombre? (s/n): ");
    scanf(" %c", &opcion);
    limpiarBuffer();

    if (opcion == 's' || opcion == 'S')
    {
        printf("Nuevo nombre: ");
        fgets(arreglo[pos].nombre, 50, stdin);
        arreglo[pos].nombre[strcspn(arreglo[pos].nombre, "\n")] = 0;
    }

    printf("¿Desea cambiar el genero? (s/n): ");
    scanf(" %c", &opcion);
    limpiarBuffer();

    if (opcion == 's' || opcion == 'S')
    {
        printf("Nuevo genero: ");
        fgets(arreglo[pos].genero, 30, stdin);
        arreglo[pos].genero[strcspn(arreglo[pos].genero, "\n")] = 0;
    }

    printf("¿Desea cambiar la plataforma? (s/n): ");
    scanf(" %c", &opcion);
    limpiarBuffer();

    if (opcion == 's' || opcion == 'S')
    {
        printf("Nueva plataforma: ");
        fgets(arreglo[pos].plataforma, 20, stdin);
        arreglo[pos].plataforma[strcspn(arreglo[pos].plataforma, "\n")] = 0;
    }

    printf("¿Desea cambiar el precio? (s/n): ");
    scanf(" %c", &opcion);
    limpiarBuffer();

    if (opcion == 's' || opcion == 'S')
    {
        printf("Nuevo precio: ");
        scanf("%f", &arreglo[pos].precio);
        limpiarBuffer();
    }

    printf("\nJuego modificado correctamente.\n");
    Sleep(800);
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
        Sleep(800);
        return 0;
    }

    for (int i = pos; i < *validos - 1; i++)
    {
        arreglo[i] = arreglo[i + 1];
    }

    (*validos)--;

    printf("Juego borrado correctamente.\n");
    Sleep(800);

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
    char buffer[50];

    printf("\n=== MODIFICAR DATOS DE LA EMPRESA ===\n");

    do
    {
        printf("¿Desea cambiar el nombre de la empresa? (s/n): ");
        scanf("%49s", buffer);
        opcion = buffer[0];
    }
    while(opcion!='s' && opcion!='S' && opcion!='n' && opcion!='N');

    if (opcion == 's' || opcion == 'S')
    {
        printf("Nuevo nombre: ");
        scanf("%s", modificado.nombre);
    }

    do
    {
        printf("¿Desea cambiar el email de contacto? (s/n): ");
        scanf("%49s", buffer);
        opcion = buffer[0];
    }
    while(opcion!='s' && opcion!='S' && opcion!='n' && opcion!='N');

    if (opcion == 's' || opcion == 'S')
    {
        printf("Nuevo email: ");
        scanf("%s", modificado.email);
    }

    do
    {
        printf("¿Desea cambiar el pais? (s/n): ");
        scanf("%49s", buffer);
        opcion = buffer[0];
    }
    while(opcion!='s' && opcion!='S' && opcion!='n' && opcion!='N');

    if (opcion == 's' || opcion == 'S')
    {
        printf("Nuevo pais: ");
        scanf("%s", modificado.pais);
    }

    do
    {
        printf("¿Desea cambiar la contrasenia? (s/n): ");
        scanf("%49s", buffer);
        opcion = buffer[0];
    }
    while(opcion!='s' && opcion!='S' && opcion!='n' && opcion!='N');

    if (opcion == 's' || opcion == 'S')
    {
        printf("Nueva contrasenia: ");
        scanf("%s", modificado.contrasenia);
    }


    do
    {
        printf("\n¿Confirmar modificaciones? (s/n): ");
        scanf("%49s", buffer);
        opcion = buffer[0];
    }
    while(opcion!='s' && opcion!='S' && opcion!='n' && opcion!='N');

    if (opcion == 's' || opcion == 'S')
    {
        *empresaActual = modificado;
        printf("Datos modificados correctamente.\n");

        Sleep(800);
    }
    else
    {
        printf("Modificacion cancelada.\n");

        Sleep(800);
    }
}


void actualizarEmpresaEnArchivo(stEmpresa empresa)
{
    FILE* buffer = fopen(ARCHIVO_EMPRESAS, "r+b");
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
int validarEmailEmpresa (char email[])
{
    int tieneArroba=0;
    int tienePuntoDespuesDelArroba=0;

    if (strlen(email)<5)
    {
        printf("La direccion de correo es demasiado corta.\n");
        return 0;
    }

    for (int i=0; i<strlen(email); i++)
    {

        if (email[i]=='@')
        {

            if (tieneArroba)
            {
                printf("El correo solo puede contener un @.\n");
                return 0;
            }

            tieneArroba=1;

            if (i==0 || i==strlen(email)-1)
            {
                printf("El correo no puede empezar ni terminar con un @.\n");
                return 0;
            }
        }
        else if (tieneArroba && email[i]=='.')
        {
            tienePuntoDespuesDelArroba=1;
        }
    }

    if (!tieneArroba || !tienePuntoDespuesDelArroba)
    {
        printf("El correo debe contener un @ y un . despues del arroba.\n");
        return 0;
    }

    return 1;
}

int validarNombreEmpresa (char nombreDeEmpresa[])
{
    int tieneLetraONumero=0;

    for (int i=0; i<strlen(nombreDeEmpresa); i++)
    {
        char caracter=nombreDeEmpresa[i];

        if ((caracter>='a' && caracter<='z') ||
                (caracter>='A' && caracter<='Z') ||
                (caracter>='0' && caracter<='9'))
        {
            tieneLetraONumero=1;
        }
        else if (caracter=='_' || caracter=='-')
        {

        }
        else
        {
            printf("El nombre de la empresa contiene simbolos invalidos. Intente de nuevo\n");
            return 0;
        }

    }

    if (!tieneLetraONumero)
    {
        printf("El nombre de la empresa no puede estar vacio. Intente de nuevo.\n");
        return 0;
    }

    return 1;
}


int validarContraseniaEmpresa (char contrasenia[])
{
    int tieneNumero=0;
    int tieneLetra=0;

    if (strlen(contrasenia)<6)
    {
        printf("La contrasenia es demasiado corta (minimo 6 caracteres).\n");
        return 0;
    }


    for (int i=0; i<strlen(contrasenia); i++)
    {
        if ((contrasenia[i]>='a' && contrasenia[i]<='z') || (contrasenia[i]>='A' && contrasenia[i]<='Z'))
        {
            tieneLetra=1;
        }

        if (contrasenia[i]>='0' && contrasenia[i]<='9')
        {
            tieneNumero=1;
        }
    }

    if (!tieneLetra || !tieneNumero)
    {
        printf("La contrasenia debe tener al menos una letra y numero.\n");
        return 0;
    }

    return 1;
}

void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarPais (char pais[])
{
    int tieneLetra=0;

    for (int i=0; i<strlen(pais); i++)
    {
        char caracter=pais[i];

        if ((caracter>='a' && caracter<='z') ||
                (caracter>='A' && caracter<='Z') ||
                (caracter>='0' && caracter<='9'))
        {
            tieneLetra=1;
        }
        else if (caracter=='_' || caracter=='-')
        {

        }
        else
        {
            printf("El nombre del pais contiene simbolos invalidos. Intente de nuevo\n");
            return 0;
        }

    }

    if (!tieneLetra)
    {
        printf("El nombre del pais no puede estar vacio. Intente de nuevo.\n");
        return 0;
    }

    return 1;
}

Fecha cargarFechaManualEmpresa()
{
    Fecha fecha;
    do {
        printf("Ingrese dia (1-31): ");
        scanf("%d", &fecha.dia);
    } while (fecha.dia < 1 || fecha.dia > 31);

    do {
        printf("Ingrese mes (1-12): ");
        scanf("%d", &fecha.mes);
    } while (fecha.mes < 1 || fecha.mes > 12);

    do {
        printf("Ingrese anio (ej. 2025): ");
        scanf("%d", &fecha.anio);
    } while (fecha.anio!=2025);

    return fecha;
}



#include <stdio.h>
#include <stdlib.h>
#include "empresas.h"
#include <string.h>

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

    } while (opcion != 's' && opcion != 'S');

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

    printf("Ingrese una breve descripcion de la empresa: ");
    scanf("%s", empresa->descripcion);
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
    char opcion;

    do
    {
        printf("\n===== MENU EMPRESA =====\n");
        printf("Publicar nuevo juego (1)\n");
        printf("Ver mis juegos (2)\n");
        printf("Cerrar sesion (0)\n");
        printf("Seleccione una opcion: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case '1':
            printf("Funcionalidad para publicar juegos (proximamente).\n");
            break;

        case '2':
            printf("Listado de juegos de la empresa (proximamente).\n");
            break;

        case '0':
            printf("Sesion cerrada.\n");
            break;

        default:
            printf("Opcion invalida.\n");
        }

    } while (opcion != '0');
}


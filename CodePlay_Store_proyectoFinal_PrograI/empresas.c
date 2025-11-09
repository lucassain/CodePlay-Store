#include <stdio.h>
#include <stdlib.h>
#include "empresas.h"
#include <string.h>

void loginEmpresas()
{
    stEmpresa empresa;
    char opcion;

    printf("\nBienvenido a CodePlay!\n");

    do
    {
        printf("\n===== MENU EMPRESAS =====\n");
        printf("Iniciar sesion (I)\n");
        printf("Registrar empresa (R)\n");
        printf("Volver / Salir (S)\n");
        printf("=========================\n");
        printf("Seleccione una opcion: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
            case 'i':
            case 'I':
                iniciarSesionEmpresa(ARCHIVO_EMPRESAS);

                return;
                break;

            case 'r':
            case 'R':
            {
                int registrarse = registrarseEmpresa(&empresa);

                if (registrarse)
                {
                    printf("Empresa registrada con exito!\n");
                    guardarEmpresas(ARCHIVO_EMPRESAS, empresa);
                }
                else
                {
                    printf("Error al registrar la empresa.\n");
                }

                return;
                break;
            }

            case 's':
            case 'S':
                printf("Volviendo al menu anterior...\n");
                return;

                break;

            default:
                printf("Opcion invalida. Intente nuevamente.\n");

                break;
        }

    } while (opcion != '0' && opcion != 's' && opcion != 'S');
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

void iniciarSesionEmpresa (char archivo[])
{
    FILE* buffer=fopen(archivo, "rb");

    stEmpresa guardado;
    stEmpresa ingreso;
    int registroExitoso=0;

    if (buffer!=NULL)
    {
        fseek(buffer, 0, SEEK_SET);
        printf("INICIAR SESION COMO EMPRESA\n");

        printf("Mail de contacto: ");
        scanf("%s", ingreso.email);

        printf("Contrasenia: ");
        scanf("%s", ingreso.contrasenia);

        while (fread(&guardado, sizeof(stEmpresa), 1, buffer)==1)
        {
            if (strcmp(ingreso.email, guardado.email)==0 &&
                    strcmp(ingreso.contrasenia, guardado.contrasenia)==0)
            {
                printf("Inicio de sesion exitoso. Bienvenido %s!\n", guardado.nombre);
                registroExitoso=1;
                break;
            }

        }
        if(registroExitoso==0)
        {
            printf("Correo,usuario o contrasenia incorrectas\n");
        }

        fclose(buffer);
    }
    else
    {
        printf("Error en el achivo\n");
    }
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

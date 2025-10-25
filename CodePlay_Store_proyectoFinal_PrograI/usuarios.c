#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include <string.h>

void loginUsuarios (char archivos[])
{
    int registro=0;

    FILE* buffer=fopen(archivos, "ab");

    if(buffer!=NULL)
    {
        stLogin usuario;

        printf("Bienvenido a CodePlay\n");

        do
        {
            printf("INICIAR SESION (I) - REGISTRARSE (R): ");
            scanf(" %c", &usuario.opcion);

            if( usuario.opcion=='i' || usuario.opcion=='I')
            {


            }
            else if(usuario.opcion == 'r' || usuario.opcion=='R')
            {
                registro=registrarse(&usuario);

                if (registro==1)
                {
                    printf("Usuario registrado correctamente.\n");
                    guardarUsuarios(ARCHIVOS_USUARIOS, usuario);
                }
                else
                {
                    printf("Error al registrarse.");
                }

            }
            else
            {
                printf("Opcion invalida. Elija otra opcion\n");
            }
        }
        while (usuario.opcion!='i' && usuario.opcion!='I' && usuario.opcion!='r' && usuario.opcion!='R');

        fclose(buffer);
    }
}

void registrarUnUsuario (stLogin* usuario)
{
    printf("Ingrese su direccion de correo electronico: ");
    scanf("%s", usuario->email);

    printf("Ingrese su nombre de usuario: ");
    scanf("%s", usuario->usuario);

    printf("Ingrese su contrasenia: ");
    scanf("%s", usuario->contrasenia);
}

int registrarse (stLogin* usuario)
{
    printf("CREAR USUARIO\n");

    registrarUnUsuario(usuario);

    if (strlen(usuario->usuario)>0 && strlen(usuario->email)>0 && strlen(usuario->contrasenia)>0)
    {
        return 1;

    }
    else
    {
        return 0;
    }
}

void guardarUsuarios (char archivo[], stLogin usuarios)
{
    FILE* buffer=fopen(archivo, "ab");

    if (buffer!=NULL)
    {
        fwrite(&usuarios, sizeof(stLogin), 1, buffer);

        fclose(buffer);
    }else
    {
        printf("Error\n");
    }
}

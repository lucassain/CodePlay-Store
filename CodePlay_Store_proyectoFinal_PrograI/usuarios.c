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
            mostrarUsuarios (ARCHIVOS_USUARIOS);
            printf("INICIAR SESION (I) - REGISTRARSE (R): ");
            scanf(" %c", &usuario.opcion);

            if( usuario.opcion=='i' || usuario.opcion=='I')
            {
                iniciarSesion(ARCHIVOS_USUARIOS);

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
    }
    else
    {
        printf("Error\n");
    }
}

void iniciarSesion (char archivo[])
{
    FILE* buffer=fopen(archivo, "rb");
    stLogin aux;

    if (buffer!=NULL)
    {
        printf("INICIAR SESION\n");
        printf("Ingrese su dreccion de correo electronico: ");
        scanf("%s", aux.email);
        printf("Ingrese su nombre de usuario: ");
        scanf("%s", aux.usuario);
        printf("Ingrese su contrasenia: ");
        scanf("%s", aux.contrasenia);
        int registroExitoso=0;

        do
        {
            while (fread(&aux, sizeof(stLogin), 1, buffer)==1)
            {
                if (strcmp(aux.usuario, usuarios.usuario)==0 && strcmp(aux.email, usuarios.email)==0 && strcmp(aux.contrasenia, usuarios.contrasenia)==0)
                {
                    printf("Inicio de sesion exitoso.\n");
                    registroExitoso=1;
                }
                else

                {
                    printf("Correo, usuario o contrasenia incorrecta\n");
                    registroExitoso=0;
                }
            }
        }while (registroExitoso!=1);

            fclose(buffer);
    }
}

void mostrarUnUsuario (stLogin user)
{
    printf("Nombre de usuario: %s\n", user.usuario);
    printf("Direccion de correo electronico: %s\n", user.email);
    printf("Contrasenia: %s\n", user.contrasenia);
}

void mostrarUsuarios (char archivo[])
{
    FILE* usuarios=fopen(archivo, "rb");
    stLogin user;

    if (usuarios!=NULL)
    {
        while (fread(&user, sizeof(stLogin), 1, usuarios))
        {
            mostrarUnUsuario(user);
        }
    }
}

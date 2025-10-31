#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include <string.h>

void loginUsuarios ()
{
    int registro=0;

    stLogin usuario;

    printf("Bienvenido a CodePlay\n");

    do
    {
        mostrarUsuarios (ARCHIVOS_USUARIOS); //BORRAR MAS TARDE
        printf("INICIAR SESION (I) - REGISTRARSE (R): ");
        scanf(" %c", &usuario.opcion);

        if( usuario.opcion=='i' || usuario.opcion=='I')
        {
            iniciarSesion(ARCHIVOS_USUARIOS);

        }
        else if(usuario.opcion == 'r' || usuario.opcion=='R')
        {
            registro=registrarseUsuario(&usuario);

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

int registrarseUsuario (stLogin* usuario)
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
    stLogin guardado;
    stLogin ingreso;
    int registroExitoso=0;

    if (buffer!=NULL)
    {
        fseek(buffer, 0, SEEK_SET);
        printf("INICIAR SESION\n");

        registrarUnUsuario(&ingreso);

        while (fread(&guardado, sizeof(stLogin), 1, buffer)==1)
        {
            if (strcmp(ingreso.usuario, guardado.usuario)==0 && strcmp(ingreso.email, guardado.email)==0 && strcmp(ingreso.contrasenia, guardado.contrasenia)==0)
            {
                printf("Inicio de sesion exitoso. Bienvenido %s!\n", guardado.usuario);
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


void mostrarUnUsuario (stLogin user) //BORRAR MAS TARDE
{
    printf("Nombre de usuario: %s\n", user.usuario);
    printf("Direccion de correo electronico: %s\n", user.email);
    printf("Contrasenia: %s\n", user.contrasenia);
}

void mostrarUsuarios (char archivo[]) //BORRAR MAS TARDE
{
    FILE* usuarios=fopen(archivo, "rb");
    stLogin user;

    if (usuarios!=NULL)
    {
        while (fread(&user, sizeof(stLogin), 1, usuarios))
        {
            mostrarUnUsuario(user);
        }
        fclose(usuarios);
    }
}

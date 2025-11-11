#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include <string.h>

void loginUsuarios()
{
    int registro = 0;
    char opcion;
    stLogin usuario;

    do
    {
        printf("\n=== MENU USUARIO ===\n");
        printf("Iniciar sesion (I)\n");
        printf("Registrarse (R)\n");
        printf("Volver al menu principal (S)\n");
        printf("Ingrese una opcion: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
            case 'i':
            case 'I':
                iniciarSesion(ARCHIVOS_USUARIOS);

                return;
                break;

            case 'r':
            case 'R':
                registro = registrarseUsuario(&usuario);

                if (registro == 1)
                {
                    printf("Usuario registrado correctamente.\n");
                    guardarUsuarios(ARCHIVOS_USUARIOS, usuario);
                }
                else if (registro == -1)
                {
                    printf("El usuario registrado ya existe.\n");
                }
                else
                {
                    printf("Error al registrarse.\n");
                }

                return;
                break;

            case 's':
            case 'S':
                printf("Volviendo al menu principal...\n");

                return;

                break;

            default:
                printf("Opcion invalida. Intente de nuevo.\n");

                break;
        }

    } while (opcion != 's' && opcion != 'S');
}


void registrarUnUsuario (stLogin* usuario)
{
    do
    {
        printf("Ingrese su direccion de correo electronico: ");
        scanf("%s", usuario->email);
    }
    while(!validarEmail(usuario->email));


    do
    {
        printf("Ingrese su nombre de usuario: ");
        scanf("%s", usuario->usuario);
    }
    while(!validarUsuario(usuario->usuario));

    do
    {
        printf("Ingrese su contrasenia: ");
        scanf("%s", usuario->contrasenia);

    }
    while (!validarContrasenia(usuario->contrasenia));
}

int registrarseUsuario (stLogin* usuario)
{
    printf("CREAR USUARIO\n");

    registrarUnUsuario(usuario);

    if (existeUsuario(ARCHIVOS_USUARIOS, *usuario))
    {
        return -1;
    }
    else
    {

        if (strlen(usuario->usuario)>0 && strlen(usuario->email)>0 && strlen(usuario->contrasenia)>0)
        {
            return 1;

        }
        else
        {
            return 0;
        }
    }

}


int validarEmail (char email[])
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

int validarUsuario (char nombreDeUsuario[])
{
    int tieneLetraONumero=0;

    for (int i=0; i<strlen(nombreDeUsuario); i++)
    {
        char caracter=nombreDeUsuario[i];

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
            printf("El nombre de usuario contiene simbolos invalidos. Intente de nuevo\n");
            return 0;
        }

    }

    if (!tieneLetraONumero)
    {
        printf("El nombre de usuario no puede estar vacio. Intente de nuevo.\n");
        return 0;
    }

    return 1;
}


int validarContrasenia (char contrasenia[])
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
    }

    return 1;
}

int existeUsuario (char archivo[], stLogin nuevoUsuario)
{
    FILE* buffer=fopen(archivo, "rb");

    if (buffer!=NULL)
    {
        stLogin aux;

        while(fread(&aux, sizeof(stLogin), 1, buffer)==1)
        {
            if (strcmp(nuevoUsuario.usuario, aux.usuario)==0 || strcmp(nuevoUsuario.email, aux.email)==0)
            {
                fclose(buffer);
                return 1;
            }
        }

        fclose(buffer);
    }

    return 0;
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

        printf("Ingrese su direccion de correo electronico: ");
        scanf("%s", ingreso.email);

        printf("Ingrese su nombre de usuario: ");
        scanf("%s", ingreso.usuario);

        printf("Ingrese su contrasenia: ");
        scanf("%s", ingreso.contrasenia);


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

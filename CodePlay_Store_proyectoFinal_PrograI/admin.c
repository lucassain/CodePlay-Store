#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "usuarios.h"

int loginAdmin()
{
    char opcion;

    do
    {
        printf("\n=== MENU ADMIN ===\n");
        printf("Iniciar sesion (I)\n");
        printf("Volver al menu principal (S)\n");
        printf("Ver usuarios (V)\n");
        printf("Buscar usuario por dni (B)\n");
        printf("Ingrese una opcion: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case 'i':
        case 'I':
            if (iniciarSesionAdmin(ARCHIVOS_ADMINS) == 1)
            {
                return 1;
            }
            else
            {
                return -1;
            }
          break;

        case 'v':
        case 'V':
            mostrarUsuariosAdmin();

            break;

        case 'b':
        case 'B':
             verUsuarioPorDni();
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

void creacionAdmin ()
{
    FILE* buffer = fopen(ARCHIVOS_ADMINS, "rb");
    if(buffer == NULL)
    {

        buffer = fopen(ARCHIVOS_ADMINS, "wb");
        if(buffer != NULL)
        {
            stAdmin admins[] =
            {
                {"Lucas","lucasSain@gmail.com","lucaspro"},
                {"Franco","francobidegain@gmail.com","bidepro"},
                {"Santi", "santiolea@gmail.com","santipro"}
            };
            fwrite(admins, sizeof(stAdmin), 3, buffer);
            fclose(buffer);
        }
        else
        {
            printf("Error en el archvio\n");
        }
    }
    else
    {
        fclose(buffer);
    }
}
int iniciarSesionAdmin (char archivo[])
{
    stAdmin ingreso;
    int exito = 0;

    printf("\nINICIAR SESION\n");

    while(!exito)
    {
        printf("Ingrese su correo electronico: ");
        scanf("%29s", ingreso.email);
        printf("Ingrese su nombre de usuario: ");
        scanf("%29s", ingreso.usuario);
        printf("Ingrese su contrasenia: ");
        scanf("%29s", ingreso.contrasenia);

        exito = validarInicioSesionAdmin(archivo, ingreso);

        if(!exito)
        {
            printf("Intente de nuevo.\n\n");
            return 0;
        }
    }

    return 1;
}

int validarInicioSesionAdmin(char archivo[], stAdmin recibido)
{

    FILE* buffer=fopen(archivo, "rb");
    stAdmin aux;
    int registroExitoso=0;

    if(buffer != NULL)
    {

        while (fread(&aux, sizeof(stAdmin), 1, buffer)==1)
        {
            if (strcmp(aux.usuario, recibido.usuario)==0 && strcmp(aux.email, recibido.email)==0 && strcmp(aux.contrasenia, recibido.contrasenia)==0)
            {
                printf("Inicio de sesion exitoso. Bienvenido admin %s!\n", recibido.usuario);
                registroExitoso=1;
                break;
            }
        }
        fclose(buffer);
    }
    else
    {
        printf("Error con el archivo de admins\n");
    }
    if(registroExitoso==0)
    {
        printf("Correo,usuario o contrasenia incorrectas\n");
    }

    return registroExitoso;
}
void mostrarUsuariosRec(FILE *buffer)
{
    stLogin aux;

    if (fread(&aux, sizeof(stLogin), 1, buffer) != 1)
        return;


    mostrarUnUsuario(aux);

    mostrarUsuariosRec(buffer);
}


void mostrarUsuariosAdmin()
{
    FILE *buffer = fopen(ARCHIVOS_USUARIOS, "rb");

    if (buffer == NULL)
    {
        printf("No se pudo abrir el archivo de usuarios.\n");
        return;
    }

    printf("\n Lista de usuarios \n");

    mostrarUsuariosRec(buffer);

    fclose(buffer);
}
int buscarUsuarioPorDni(char dniBuscado[])
{
    FILE *arch = fopen("usuarios.dat", "rb");
    if (!arch)
    {
        printf("Error al abrir archivo de usuarios.\n");
        return -1;
    }

    stLogin aux;

    while (fread(&aux, sizeof(stLogin), 1, arch) == 1)
    {
        if (strcmp(aux.DNI, dniBuscado) == 0)
        {
            printf("\nUsuario encontrado:\n");
            mostrarUnUsuario(aux);
            fclose(arch);
            return 1;
        }
    }

    fclose(arch);
    printf("No se encontro un usuario con ese DNI.\n");
    return 0;
}
void verUsuarioPorDni()
{
    char dniBuscado[20];

    printf("Ingrese DNI del usuario: ");
    scanf("%s", dniBuscado);

    buscarUsuarioPorDni(dniBuscado);
}

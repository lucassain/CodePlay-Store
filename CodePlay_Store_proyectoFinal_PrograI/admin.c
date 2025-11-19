#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "usuarios.h"
#include "transacciones.h"

int loginAdmin(stAdmin *adminActual)
{
    char opcion;

    do {
        printf("\n=== MENU ADMIN ===\n");
        printf("Iniciar sesion (I)\n");
        printf("Volver al menu principal (S)\n");
        printf("Ingrese una opcion: ");
        scanf(" %c", &opcion);

        switch (opcion) {
        case 'i':
        case 'I':
            if (iniciarSesionAdmin(ARCHIVOS_ADMINS, adminActual) == 1) {
                return 1;   // INICIA SESIÓN
            } else {
                printf("Credenciales incorrectas.\n");
            }
            break;

        case 's':
        case 'S':
            printf("Volviendo al menu principal...\n");
            return 0;

        default:
            printf("Opcion invalida.\n");
        }
    } while(opcion != 's' && opcion != 'S');

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

int iniciarSesionAdmin(char archivo[], stAdmin *adminActual)
{
    stAdmin ingreso, guardado;
    int encontrado = 0;

    FILE* buffer = fopen(archivo, "rb");
    if(buffer == NULL) {
        printf("Error al abrir el archivo de admins.\n");
        return 0;
    }

    printf("\nINICIAR SESION ADMIN\n");
    printf("Usuario: ");
    scanf("%s", ingreso.usuario);
    printf("Email: ");
    scanf("%s", ingreso.email);
    printf("Contrasenia: ");
    scanf("%s", ingreso.contrasenia);

    while(fread(&guardado, sizeof(stAdmin), 1, buffer) == 1) {
        if( strcmp(ingreso.usuario, guardado.usuario) == 0 &&
            strcmp(ingreso.email, guardado.email) == 0 &&
            strcmp(ingreso.contrasenia, guardado.contrasenia) == 0)
        {
            printf("Inicio de sesion exitoso. Bienvenido admin %s!\n", guardado.usuario);
            *adminActual = guardado;
            encontrado = 1;
            break;
        }
    }

    fclose(buffer);

    if(!encontrado) {
        printf("Usuario, email o contrasenia incorrectos.\n");
    }

    return encontrado;
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

void menuAdmin(stAdmin* adminActual)
{
    system("cls");
    char opcion;

    do {
        printf("\n===== MENU ADMIN =====\n");
        printf("Ver usuarios (1)\n");
        printf("Buscar usuario por DNI (2)\n");
        printf("Ver transacciones (3)\n");      // <-- AGREGADO
        printf("Cerrar sesion (0)\n");
        printf("Seleccione una opcion: ");
        scanf(" %c", &opcion);

        switch(opcion) {

        case '1':
            mostrarUsuariosAdmin();
            break;

        case '2':
            verUsuarioPorDni();
            break;

        case '3':                               // <-- AGREGADO
            menuTransaccionesAdmin();
            break;

        case '0':
            printf("Sesion de admin cerrada.\n");
            break;

        default:
            printf("Opcion invalida.\n");
        }

    } while(opcion != '0');
}


void menuTransaccionesAdmin()
{

    char opcion;

    do {
        printf("\n====== MENU TRANSACCIONES (ADMIN) ======\n");
        printf("1) Ver listado completo de transacciones\n");
        printf("2) Buscar transaccion por ID\n");
        printf("3) Mostrar transaccion de mayor ganancia\n");
        printf("4) Recaudacion mensual\n");
        printf("0) Volver al menu anterior\n");
        printf("Seleccione una opcion: ");
        scanf(" %c", &opcion);

        switch(opcion)
        {
        case '1':
            verTransaccionesResumen();
            break;

        case '2':
            buscarYMostrarTransaccion();
            break;

        case '3':
            reporteMayorGanancia();
            break;

        case '4':
            {
                int mes, anio;
                printf("Ingrese mes: ");
                scanf("%d", &mes);
                printf("Ingrese anio: ");
                scanf("%d", &anio);

                reporteRecaudacionMensual(mes, anio);
            }
            break;

        case '0':
            printf("Volviendo...\n");
            break;

        default:
            printf("Opcion invalida.\n");
        }

    } while(opcion != '0');
}


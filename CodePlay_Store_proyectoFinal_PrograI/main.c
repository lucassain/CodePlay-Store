#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "usuarios.h"
#include "admin.h"
#include "empresas.h"
#include "juegos.h"
#include "transacciones.h"

int main()
{
    inicializarArchivoUsuarios();
    char opcionStr[10];
    char opcion;

    do
    {
        printf("===== Bienvenido a CodePlay! =====\n");
        printf("USUARIO (1)\n");
        printf("ADMIN (2)\n");
        printf("EMPRESA (3)\n");
        printf("AYUDA (4)\n");
        printf("0 PARA SALIR\n");
        printf("Como desea ingresar? (Ingrese una opcion): ");

        scanf("%9s", opcionStr);
        opcion = opcionStr[0];

        if (opcion != '0' && opcion != '1' && opcion != '2' && opcion != '3' && opcion!='4')
        {
            printf("Opcion invalida. Intente nuevamente.\n");
            Sleep(1000);
            system("cls");
        }


        switch (opcion)
        {
        case '1':
            system("cls");
            stLogin usuarioActual;

            if (loginUsuarios(&usuarioActual) == 1)
            {
                menuUsuario(&usuarioActual);
            }
            else
            {
                printf("No se pudo iniciar sesion o registro cancelado.\n\n");
            }
            break;

        case '2':
            system("cls");

            stAdmin adminActual;
            if (loginAdmin(&adminActual) == 1)
            {
                menuAdmin(&adminActual);
            }
            else
            {
                printf("No se pudo iniciar sesion de admin.\n");
            }
            break;

        case '3':
            system("cls");

            stEmpresa empresaActual;
            if (loginEmpresas(&empresaActual) == 1)
            {
                menuEmpresa(&empresaActual);
            }
            else
            {
                printf("No se pudo iniciar sesion de empresa o registro cancelado.\n");
            }
            break;

        case '4':

            system("cls");

            mostrarAyuda();

            break;

        case '0':
            printf("Cerrando programa...\n");
            break;

        }
    }
    while (opcion != '0');

    printf("Programa cerrado con exito.\n");

    return 0;
}

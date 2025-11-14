#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include "admin.h"
#include "empresas.h"
#include "juegos.h"

int main()
{
    inicializarArchivoUsuarios();

    char opcion;

    do
    {
        printf("===== Bienvenido a CodePlay! =====\n");
        printf("USUARIO (1)\n");
        printf("ADMIN (2)\n");
        printf("EMPRESA (3)\n");
        printf("0 PARA SALIR\n");
        printf("Como desea ingresar? (Ingrese una opcion): ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case '1':
        {
            stLogin usuarioActual;

            if (loginUsuarios(&usuarioActual) == 1)
            {
                menuUsuario(&usuarioActual);
            }
            else
            {
                printf("No se pudo iniciar sesion o registro cancelado.\n");
            }
            break;
        }

        case '2':
        {
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
        }

        case '3':
        {
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
        }

        case '0':
            printf("Cerrando programa...\n");
            break;

        default:
            printf("Opcion invalida. Intente nuevamente.\n");
            break;
        }

    }
    while (opcion != '0');

    printf("Programa cerrado con exito.\n");

    return 0;
}

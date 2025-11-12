#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include "admin.h"
#include "empresas.h"
#include "juegos.h"

int main()
{
    int opcion=0;

    do
    {
        printf("=====Bienvenido a CodePlay!=====\n");
        printf("USUARIO (1)\n");
        printf("ADMIN (2)\n");
        printf("EMPRESA(3)\n");
        printf("0 PARA SALIR\n");
        printf("Como desea ingresar? (Ingrese una opcion): ");
        scanf("%i", &opcion);

        switch (opcion)
        {
        case 1:

            if (loginUsuarios()==1)
            {
                menuUsuario();

            }

            break;

        case 2:
            loginAdmin();

            break;

        case 3:
            loginEmpresas();

            break;

        case 0:
            printf("Cerrando programa...\n");
            opcion=0;

            break;

        default:
            printf("Opcion invalida. Intente nuevamente.\n");

            break;
        }

    }
    while (opcion != 0);

    printf("Programa cerrado con exito.\n");

    return 0;
}

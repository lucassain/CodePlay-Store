#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include <string.h>
#include "juegos.h"
#include "transacciones.h"

int loginUsuarios(stLogin *usuarioActual)
{
    system("cls");
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

            if (iniciarSesion(ARCHIVOS_USUARIOS, usuarioActual) == 1)
            {
                return 1;
            }
            else
            {
                printf("Credenciales incorrectas.\n");
            }
            break;

        case 'r':
        case 'R':
            registro = registrarseUsuario(&usuario);

            if (registro == 1)
            {
                printf("Usuario registrado correctamente.\n");
                guardarUsuarios(ARCHIVOS_USUARIOS, usuario);

                crearArchivoDeUnUsuario(usuario);
            }
            else if (registro == -1)
            {
                printf("El usuario ya existe.\n");
            }
            else
            {
                printf("Error al registrarse.\n");
            }
            break;

        case 's':
        case 'S':
            printf("Volviendo al menu principal...\n\n");
            return 0;

        default:
            printf("Opcion invalida.\n");
        }

    }
    while (opcion != 's' && opcion != 'S');

    return 0;
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
        printf("Ingrese su nombre de usuario (sin espacios): ");
        scanf("%s", usuario->usuario);
    }
    while(!validarUsuario(usuario->usuario));

    do
    {
        printf("Ingrese su contrasenia: ");
        scanf("%s", usuario->contrasenia);

    }
    while (!validarContrasenia(usuario->contrasenia));

    do
    {
        printf("Ingrese su DNI: ");
        scanf("%s", usuario->DNI);

    }
    while(!validarDni(usuario->DNI));
}

int registrarseUsuario (stLogin* usuario)
{
    system("cls");
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
        return 0;
    }

    return 1;
}

int validarDni(char DNI[])
{
    int tieneSoloNumeros = 1;
    int rangoValido = 0;
    int len = strlen(DNI);

    if (len >= 7 && len <= 8)
    {
        rangoValido = 1;
    }
    else
    {
        rangoValido = 0;
    }

    for (int i = 0; i < len; i++)
    {
        if (DNI[i] < '0' || DNI[i] > '9')
        {
            tieneSoloNumeros = 0;
            break;
        }
    }

    if (!rangoValido)
    {
        printf("DNI invalido. Debe tener entre 7 y 8 digitos.\n");
        return 0;
    }

    if (!tieneSoloNumeros)
    {
        printf("El DNI no puede contener letras ni caracteres especiales.\n");
        return 0;
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

int iniciarSesion(char archivo[], stLogin *usuarioActual)
{
    system("cls");
    stLogin ingreso;
    stLogin guardado;
    int encontrado = 0;

    FILE* buffer = fopen(archivo, "rb");
    if(buffer == NULL)
    {
        printf("Error al abrir el archivo de usuarios.\n");
        return 0;
    }

    printf("\nINICIAR SESION\n");

    printf("Usuario: ");
    scanf("%s", ingreso.usuario);
    printf("Contrasenia: ");
    scanf("%s", ingreso.contrasenia);

    while(fread(&guardado, sizeof(stLogin), 1, buffer) == 1)
    {
        if(strcmp(ingreso.usuario, guardado.usuario) == 0 &&
                strcmp(ingreso.contrasenia, guardado.contrasenia) == 0)
        {
            printf("Inicio de sesion exitoso. Bienvenido %s!\n", guardado.usuario);
            *usuarioActual = guardado;
            encontrado = 1;
            break;
        }
    }

    fclose(buffer);

    if(!encontrado)
    {
        printf("Usuario o contrasenia incorrectos.\n");
    }

    return encontrado;
}


void mostrarUnUsuario (stLogin user) //BORRAR MAS TARDE
{
    printf("Nombre de usuario: %s\n", user.usuario);
    printf("Direccion de correo electronico: %s\n", user.email);
    printf("Contrasenia: %s\n", user.contrasenia);
    printf("DNI: %s\n", user.DNI);
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

void configuracion(stLogin* usuario)
{
    char opcion;
    stLogin nuevaCuenta;

    do
    {
        printf("\n===== CONFIGURACION =====\n");
        printf("Modificar perfil (1)\n");
        printf("Cambiar de cuenta (2)\n");
        printf("Volver al menu anterior (0)\n");
        printf("Seleccione una opcion: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case '1':
            editarDatosPerfil(usuario);
            break;

        case '2':

            printf("\nIngrese los datos de la nueva cuenta:\n");

            int resultado = loginUsuarios(&nuevaCuenta);

            if (resultado == 1)
            {
                printf("\nInicio de sesion exitoso!.\n");
                *usuario=nuevaCuenta;
                return;
            }
            else
            {
                printf("\nError al iniciar sesion. Se mantiene la sesion actual.\n");
                return;
            }

            break;

        case '0':
            printf("Volviendo al menu anterior...\n");
            break;

        default:
            printf("Opción invalida. Intente de nuevo.\n");
            break;
        }

    }
    while (opcion != '0');
}


void editarDatosPerfil(stLogin* usuarioActual)
{
    stLogin modificado = *usuarioActual;
    char opcion;

    printf("\n=== EDITAR DATOS DEL PERFIL ===\n");


    printf("¿Desea cambiar el email? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S')
    {
        do
        {
            printf("Ingrese el nuevo email: ");
            scanf("%s", modificado.email);
        }
        while(!validarEmail(modificado.email));

    }

    printf("¿Desea cambiar el nombre de usuario? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S')
    {
        do
        {
            printf("Ingrese el nuevo nombre de usuario: ");
            scanf("%s", modificado.usuario);
        }
        while(!validarUsuario(modificado.usuario));

    }

    printf("¿Desea cambiar la contrasenia? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S')
    {
        do
        {
            printf("Ingrese la nueva contrasenia: ");
            scanf("%s", modificado.contrasenia);

        }
        while(!validarContrasenia(modificado.contrasenia));

    }

    modificarPerfil(usuarioActual->DNI, modificado);

    printf("\nPerfil actualizado correctamente.\n");
    *usuarioActual = modificado;

}

void modificarPerfil (char DniABuscar[], stLogin usuarioModificado)
{
    FILE* buffer = fopen(ARCHIVOS_USUARIOS, "r+b");

    if (buffer != NULL)
    {
        stLogin aux;

        while (fread(&aux, sizeof(stLogin), 1, buffer) == 1)
        {
            if (strcmp(aux.DNI, DniABuscar) == 0)
            {
                fseek(buffer, -(long)sizeof(stLogin), SEEK_CUR);
                fwrite(&usuarioModificado, sizeof(stLogin), 1, buffer);

                break;
            }
        }

        fclose(buffer);
    }
    else
    {
        printf("Error al acceder al archivo de usuarios.\n");
    }
}


void menuUsuario(stLogin* usuarioActual)
{
    char opcion;

    do
    {

        printf("\n===== MENU USUARIO =====\n");
        printf("Explorar catalogo de juegos(1)\n");
        printf("Ver mis compras (2)\n");
        printf("Configuracion (3)\n");
        printf("Cerrar sesion (0)\n");
        printf("Seleccione una opcion: ");
        scanf(" %c", &opcion);

        switch(opcion)
        {
        case '1':
            system("cls");

            catalogoJuegos(*usuarioActual);

            break;

        case '2':
            system("cls");

            verTransaccionesDeUsuario(*usuarioActual);

            break;

        case '3':

            system("cls");

            configuracion(usuarioActual);

            break;

        case '0':

            printf("Sesion cerrada.\n");

            break;

        default:

            printf("Opcion invalida.\n");

            break;
        }

    }
    while (opcion != '0');

}

void inicializarArchivoUsuarios()
{
    FILE* buffer = fopen(ARCHIVOS_USUARIOS, "ab");
    if (buffer!= NULL)
    {
        fclose(buffer);
    }
}

void crearArchivoDeUnUsuario(stLogin usuario)
{
    char archivoUsuario[200];
    sprintf(archivoUsuario, "usuario_%s.dat", usuario.email);

    FILE* buffer = fopen(archivoUsuario, "ab");
    if (buffer != NULL)
    {
        fclose(buffer);
    }
    else
    {
        printf("No se pudo crear el archivo %s\n", archivoUsuario);
    }
}

void mostrarAyuda()
{
    system("cls");

    printf("=============================================\n");
    printf("                 AYUDA - CODEPLAY\n");
    printf("=============================================\n\n");

    printf(">> ¿QUE ES CODEPLAY?\n");
    printf("CodePlay es una tienda digital de videojuegos. Permite comprar\n");
    printf("juegos, administrar catálogos, registrar empresas creadoras,\n");
    printf("y gestionar ventas mediante transacciones.\n\n");

    printf(">> ¿COMO FUNCIONA PARA LOS USUARIOS?\n");
    printf("- Crear cuenta o iniciar sesion.\n");
    printf("- Explorar el catalogo de juegos.\n");
    printf("- Ver los detalles de cada juego.\n");
    printf("- Realizar compras y ver el historial personal.\n\n");

    printf(">> ¿COMO FUNCIONA PARA LOS ADMINISTRADORES?\n");
    printf("- Gestionar el catalogo completo.\n");
    printf("- Ver todas las transacciones de la tienda.\n");
    printf("- Consultar reportes y ventas.\n");
    printf("- Administrar usuarios y empresas.\n\n");

    printf(">> ¿COMO FUNCIONA PARA LAS EMPRESAS?\n");
    printf("- Iniciar sesion como desarrolladora.\n");
    printf("- Ver los juegos propios.\n");
    printf("- Administrar el catalogo de sus productos.\n");
    printf("- Revisar las ventas de la empresa.\n\n");

    printf(">> PREGUNTAS FRECUENTES\n");
    printf(" - ¿Necesito cuenta para comprar?\n");
    printf("   Si, es necesario iniciar sesion para registrar transacciones.\n\n");

    printf(" - ¿Las compras se guardan por usuario?\n");
    printf("   Si, cada usuario tiene su propio archivo de historial.\n\n");

    printf(" - ¿Puedo borrar mis compras?\n");
    printf("   No, por motivos de registro interno.\n\n");


    return;

}


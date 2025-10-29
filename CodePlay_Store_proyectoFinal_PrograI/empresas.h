#ifndef EMPRESAS_H_INCLUDED
#define EMPRESAS_H_INCLUDED

#define ARCHIVO_EMPRESAS "empresas.dat"

typedef struct {
    char nombre[50];            // Nombre de la empresa
    char email[50];             // Correo de contacto
    char contrasenia[20];       // Contraseña
    char telefono[20];          // Teléfono (opcional)
    char pais[30];              // País de origen
    char cuit[20];              // Número de identificación fiscal
    char tipo[20];              // Desarrolladora / Distribuidora / Publicadora
    char sitioWeb[60];          // Página o red social
    char contacto[50];          // Persona responsable
    char descripcion[150];      // Descripción breve
    char fechaRegistro[15];     // Fecha de creación de la cuenta
    char opcion;                //iniciar sesion o registrarse
} stEmpresa;

//Prototipado
void loginEmpresas ();


#endif // EMPRESAS_H_INCLUDED

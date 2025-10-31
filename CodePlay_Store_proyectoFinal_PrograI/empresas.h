#ifndef EMPRESAS_H_INCLUDED
#define EMPRESAS_H_INCLUDED

#define ARCHIVO_EMPRESAS "empresas.dat"

typedef struct {
    char nombre[50];            // Nombre de la empresa
    char email[50];             // Correo de contacto
    char contrasenia[20];       // Contraseña
    char pais[30];              // País de origen
    char descripcion[150];      // Descripción breve
    char fechaRegistro[15];     // Fecha de creación de la cuenta
    char opcion;                //iniciar sesion o registrarse
} stEmpresa;

//Prototipado
void loginEmpresas ();
void registrarUnaEmpresa (stEmpresa* empresa);
int registrarseEmpresa (stEmpresa* empresa);
void guardarEmpresas (char archivo[], stEmpresa empresa);
void iniciarSesionEmpresa (char archivo[]);
void mostrarUnaEmpresa (stEmpresa empresa); //BORRAR MAS TARDE
void mostrarEmpresas (char archivo[]); //BORRAR MAS TARDE


#endif // EMPRESAS_H_INCLUDED

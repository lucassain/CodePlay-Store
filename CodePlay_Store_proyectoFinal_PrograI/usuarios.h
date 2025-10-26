#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

#define DIMENSION_LOGIN 30
#define ARCHIVOS_USUARIOS "usuarios.dat"

typedef struct
{
    char usuario[DIMENSION_LOGIN];
    char email[DIMENSION_LOGIN];
    char contrasenia[DIMENSION_LOGIN];
    char opcion;
} stLogin;

// Prototipo
void loginUsuarios();
void registrarUnUsuario (stLogin* usuario);
int registrarse (stLogin* usuario);
void guardarUsuarios (char archivo[], stLogin usuarios);
void mostrarUsuarios (char archivo[]);
void mostrarUnUsuario (stLogin user);
void iniciarSesion (char archivo[]);



#endif

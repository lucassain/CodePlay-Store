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

// Prototipado
void loginUsuarios();
void registrarUnUsuario (stLogin* usuario);int registrarseUsuario (stLogin* usuario);
void guardarUsuarios (char archivo[], stLogin usuarios);
void mostrarUsuarios (char archivo[]); //BORRAR MAS TARDE
void mostrarUnUsuario (stLogin user); //BORRAR MAS TARDE
void iniciarSesion (char archivo[]);



#endif

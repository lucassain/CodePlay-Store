#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED
#define DIMENSION_LOGIN 30

typedef struct
{
    char usuario[DIMENSION_LOGIN];
    char email [DIMENSION_LOGIN];
    char contrasenia [DIMENSION_LOGIN];
}stLogin;


#endif // USUARIOS_H_INCLUDED

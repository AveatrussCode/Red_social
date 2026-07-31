#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Listas.h"

class Usuario {
    public:
        std::string name;
        long long id;

        Lista<long> amigos;
        Lista<long> publicaciones;

        Usuario(int, std::string);
        void agregar_amigo(long long);
        void eliminar_amigo(long long);
        void agregar_publicacion(long long);

};



#endif
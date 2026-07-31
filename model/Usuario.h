#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Listas.h"

class Usuario {
    public:
        std::string name;
        long long id;

        Lista amigos;
        Lista publicaciones;

        Usuario(int, std::string);
        void agregar_amigo(int);
        void eliminar_amigo(int);
        void agregar_publicacion(int);

};

Usuario::Usuario(int _id, std::string _name){
    name = _name;
    id = _id;
}
void Usuario::agregar_amigo(int data){
    amigos.insert(data);
}

void Usuario::eliminar_amigo(int data){
    amigos.eliminar(data);
}
void Usuario::agregar_publicacion(int data){
    publicaciones.insert(data);
}


#endif
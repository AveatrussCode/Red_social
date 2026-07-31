
#include "Usuario.h"

Usuario::Usuario(int _id, std::string _name){
    name = _name;
    id = _id;
}
void Usuario::agregar_amigo(long long data){
    amigos.insert(data);
}

void Usuario::eliminar_amigo(long long data){
    amigos.eliminar(data);
}
void Usuario::agregar_publicacion(long long data){
    publicaciones.insert(data);
}

#include "Usuario.h"

Usuario::Usuario(long long _id, std::string _name,std::string _fecha){
    name = _name;
    id = _id;
    Correo = _name + std::to_string(_id) + "@facebook2.com";
    fecha = _fecha;
    num_publicaciones = 0;
    seguidores = 0;
    cantidad_amigos = 0;
    reacciones_resividas = 0;
}
void Usuario::agregar_amigo(long long data){
    amigos.insert(data);
    cantidad_amigos ++;
}

void Usuario::eliminar_amigo(long long data){
    amigos.eliminar(data);
    cantidad_amigos--;
}
void Usuario::agregar_publicacion(long long data){
    publicaciones.insert(data);
    num_publicaciones++;
}
void Usuario::nuevo_seguidor(){
    seguidores++;
}
void Usuario::agregar_reacciones(){
    reacciones_resividas++;
}



#include "Usuario.h"

Usuario::Usuario(int _id, std::string _name){
    name = _name;
    id = _id;
    comentarios_realizados = 0;
    reacciones_realizadas = 0;
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

void Usuario::registrar_comentario(){
    comentarios_realizados++;
}

void Usuario::registrar_reaccion(){
    reacciones_realizadas++;
}

long long Usuario::calcular_actividad() const {
    return publicaciones.current * PESO_PUBLICACION
         + comentarios_realizados * PESO_COMENTARIO
         + reacciones_realizadas * PESO_REACCION;
}

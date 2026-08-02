
#include "../model/Usuario.h"
#include <iostream>

Usuario::Usuario(long long _id, std::string _name,std::string _fecha){
    name = _name;
    id = _id;
    Correo = _name + std::to_string(_id) + "@facebook2.com";
    fecha = _fecha;
    seguidores = 0;
    cantidad_amigos = 0;
    reacciones_resividas = 0;
    comentarios_realizados = 0;
    reacciones_realizadas = 0;
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

void Usuario::nuevo_seguidor(){
    seguidores++;
}
void Usuario::agregar_reacciones(){
    reacciones_resividas++;
}
void Usuario::mostrar(){

    std::cout << "ID: "
              << id << "\n";

    std::cout << "Nombre: "
              << name << "\n";

    std::cout << "Correo: "
              << Correo << "\n";

    std::cout << "Amigos: "
              << cantidad_amigos << "\n";

    std::cout << "Seguidores: "
              << seguidores << "\n";

    std::cout << "Actividad: "
              << calcular_actividad()
              << "\n";
}
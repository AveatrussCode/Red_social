#include "Sistema.h"

Sistema::Sistema(){

    siguiente_usuario_id = 1;
    siguiente_post_id = 1;

    usuario_actual = nullptr;
}

long long Sistema::generar_usuario_id(){
    return siguiente_usuario_id++;
}

long long Sistema::generar_post_id(){
    return siguiente_post_id++;
}

Usuario* Sistema::registrar_usuario(std::string nombre){

    long long id = generar_usuario_id();
    Usuario* nuevo = new Usuario(id,nombre);
    usuarios.insertar(id,nuevo);
    return nuevo;
}

Post* Sistema::crear_post(long long id_usuario, int fecha, std::string cabecera, std::string img ){

    long long id = generar_post_id();

    Post* nuevo = new Post( id_usuario, id, fecha, cabecera, img);
    posts.insertar(id,nuevo);
    return nuevo;
}

Usuario* Sistema::buscar_usuario(long long id){
    Usuario* resultado = nullptr;
    if(usuarios.buscar(id, resultado)){
        return resultado;
    }
    return nullptr;
}

Post* Sistema::buscar_post(long long id){
    Post* resultado = nullptr;
    if(posts.buscar(id, resultado)){
        return resultado;
    }
    return nullptr;
}
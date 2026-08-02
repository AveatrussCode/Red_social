#include "Sistema.h"
#include "HeapTree.h"
#include <iostream>

namespace {
bool usuario_mas_activo(Usuario* primero, Usuario* segundo){
    if(primero->calcular_actividad() != segundo->calcular_actividad()){
        return primero->calcular_actividad() > segundo->calcular_actividad();
    }
    return primero->id < segundo->id;
}

bool post_mas_reaccionado(Post* primero, Post* segundo){
    int reacciones_primero = primero->like + primero->dislike;
    int reacciones_segundo = segundo->like + segundo->dislike;
    if(reacciones_primero != reacciones_segundo){
        return reacciones_primero > reacciones_segundo;
    }
    return primero->id_post < segundo->id_post;
}
}

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

    Usuario* propietario = buscar_usuario(id_usuario);
    if(propietario != nullptr){
        propietario->agregar_publicacion(id);
    }

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

bool Sistema::registrar_comentario_usuario(long long id_usuario){
    Usuario* usuario = buscar_usuario(id_usuario);
    if(usuario == nullptr){
        return false;
    }
    usuario->registrar_comentario();
    return true;
}

bool Sistema::registrar_reaccion_usuario(long long id_usuario){
    Usuario* usuario = buscar_usuario(id_usuario);
    if(usuario == nullptr){
        return false;
    }
    usuario->registrar_reaccion();
    return true;
}

void Sistema::mostrar_usuarios_activos(int cantidad){
    if(cantidad <= 0 || usuarios.tamano() == 0){
        std::cout << "No hay usuarios para mostrar.\n";
        return;
    }

    if(cantidad > usuarios.tamano()){
        cantidad = static_cast<int>(usuarios.tamano());
    }

    HeapTree<Usuario*> ranking(usuarios.tamano(), usuario_mas_activo);

    for(long long i = 0; i < usuarios.size; i++){
        Nodo<Usuario*>* nodo = usuarios.id_list[i].heap;
        while(nodo != nullptr){
            ranking.insertar(nodo->valor);
            nodo = nodo->next;
        }
    }

    std::cout << "Usuarios mas activos:\n";
    for(int i = 0; i < cantidad; i++){
        Usuario* usuario = nullptr;
        ranking.extraer_maximo(usuario);
        std::cout << i + 1 << ". " << usuario->name
                  << " (ID: " << usuario->id
                  << ", actividad: " << usuario->calcular_actividad()
                  << ", publicaciones: " << usuario->publicaciones.current
                  << ", comentarios: " << usuario->comentarios_realizados
                  << ", reacciones: " << usuario->reacciones_realizadas << ")\n";
    }
}

void Sistema::mostrar_posts_mas_reaccionados(int cantidad){
    if(cantidad <= 0 || posts.tamano() == 0){
        std::cout << "No hay publicaciones para mostrar.\n";
        return;
    }

    if(cantidad > posts.tamano()){
        cantidad = static_cast<int>(posts.tamano());
    }

    HeapTree<Post*> ranking(posts.tamano(), post_mas_reaccionado);

    for(long long i = 0; i < posts.size; i++){
        Nodo<Post*>* nodo = posts.id_list[i].heap;
        while(nodo != nullptr){
            ranking.insertar(nodo->valor);
            nodo = nodo->next;
        }
    }

    std::cout << "Publicaciones con mas reacciones:\n";
    for(int i = 0; i < cantidad; i++){
        Post* post = nullptr;
        ranking.extraer_maximo(post);
        std::cout << i + 1 << ". Post " << post->id_post
                  << " (usuario: " << post->id_usuario
                  << ", reacciones: " << post->like + post->dislike
                  << ", likes: " << post->like
                  << ", dislikes: " << post->dislike << ")\n";
    }
}

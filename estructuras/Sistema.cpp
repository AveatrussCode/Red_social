#include "../model/Sistema.h"
#include "../model/HeapTree.h"
#include "../model/Comentario.h"
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
bool Sistema::agregar_amigo(long long id1, long long id2){

    Usuario* u1 = buscar_usuario(id1);
    Usuario* u2 = buscar_usuario(id2);
    if(!u1 || !u2){
        return false;
    }
    u1->agregar_amigo(id2);
    u2->agregar_amigo(id1);

    return true;
}

bool Sistema::comentar_post(
    long long id_post,
    long long id_usuario,
    std::string texto){

    Post* post = buscar_post(id_post);
    Usuario* usuario = buscar_usuario(id_usuario);

    if(!post || !usuario){
        return false;
    }

    Comentario nuevo(id_usuario,texto);

    post->new_comentario(nuevo);

    usuario->registrar_comentario();

    return true;
}

bool Sistema::reaccionar_like(long long id_post){
    Post* post = buscar_post(id_post);
    if(!post){
        return false;
    }

    post->dar_like();

    Usuario* propietario =
        buscar_usuario(post->id_usuario);

    if(propietario){
        propietario->agregar_reacciones();
    }

    return true;
}
void Sistema::mostrar_usuario(
    long long id){

    Usuario* usuario = buscar_usuario(id);

    if(usuario){
        usuario->mostrar();
    }
}
void Sistema::mostrar_post(
    long long id){

    Post* post = buscar_post(id);

    if(post){
        post->mostrar();
    }
}

bool Sistema::iniciar_sesion(long long id){

    Usuario* usuario = buscar_usuario(id);

    if(usuario == nullptr){
        return false;
    }

    usuario_actual = usuario;
    return true;
}

void Sistema::cerrar_sesion(){
    usuario_actual = nullptr;
}

void Sistema::ver_perfil_actual(){

    if(usuario_actual == nullptr){
        std::cout << "No hay sesion iniciada\n";
        return;
    }

    std::cout << "\n=== PERFIL ===\n";

    std::cout << "ID: " << usuario_actual->id << "\n";
    std::cout << "Nombre: " << usuario_actual->name << "\n";
    std::cout << "Correo: " << usuario_actual->Correo << "\n";
    std::cout << "Amigos: " << usuario_actual->cantidad_amigos << "\n";
    std::cout << "Seguidores: " << usuario_actual->seguidores << "\n";
    std::cout << "Actividad: " << usuario_actual->calcular_actividad() << "\n";
}

void Sistema::ver_amigos(){

    if(usuario_actual == nullptr){
        return;
    }

    std::cout << "\n=== AMIGOS ===\n";

    for(long long i=0; i<usuario_actual->amigos.current; i++){

        long long id = usuario_actual->amigos.lista[i];

        Usuario* amigo = buscar_usuario(id);

        if(amigo){
            std::cout << amigo->id<< " - " << amigo->name << "\n";
        }
    }
}
void Sistema::ver_mis_posts(){

    if(usuario_actual == nullptr){
        return;
    }

    for(long long i=0;i<usuario_actual->publicaciones.current;i++){
        long long idPost = usuario_actual->publicaciones.lista[i];
        Post* post = buscar_post(idPost);

        if(post){

            std::cout << "\nPOST " << post->id_post  << "\n";
            std::cout << post->cabecera  << "\n";
            std::cout << "Likes: " << post->like<< "\n";
        }
    }
}
bool Sistema::publicar( std::string texto, std::string imagen){

    if(usuario_actual == nullptr){
        return false;
    }

    crear_post(usuario_actual->id,20260802,texto,imagen);

    return true;
}
void Sistema::ver_feed(){

    if(usuario_actual == nullptr){
        return;
    }

    std::cout
        << "\n=== FEED ===\n";

    for(long long i=0;i<usuario_actual->amigos.current;i++){
        long long idAmigo =usuario_actual->amigos.lista[i];

        Usuario* amigo = buscar_usuario(idAmigo);

        if(!amigo){
            continue;
        }

        for(long long j=0;j<amigo->publicaciones.current;j++){

            long long idPost = amigo->publicaciones.lista[j];
            Post* post = buscar_post(idPost);

            if(post){
                std::cout<< "\n"  << amigo->name << "\n";

                std::cout<< post->cabecera << "\n";

                std::cout<< "Likes: "<< post->like << "\n";
            }
        }
    }
}
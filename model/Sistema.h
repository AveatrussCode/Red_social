#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>

#include "Usuario.h"
#include "Post.h"
#include "Tabla_hash.h"

class Sistema{

public:
    Hash<Usuario*> usuarios;
    Hash<Post*> posts;
    long long siguiente_usuario_id;
    long long siguiente_post_id;
    Usuario* usuario_actual;
    Sistema();
    long long generar_usuario_id();
    long long generar_post_id();
    Usuario* registrar_usuario(std::string nombre);
    Post* crear_post( long long id_usuario, int fecha, std::string cabecera, std::string img );
    Usuario* buscar_usuario(long long id);
    Post* buscar_post(long long id);
    bool registrar_comentario_usuario(long long id_usuario);
    bool registrar_reaccion_usuario(long long id_usuario);
    void mostrar_usuarios_activos(int cantidad);
    void mostrar_posts_mas_reaccionados(int cantidad);
};

#endif

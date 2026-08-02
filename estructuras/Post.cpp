#include "../model/Post.h"
#include <iostream>
#include "../model/Comentario.h"

Post::Post(long long usuario, long long _id_post,int _fecha, std::string _cabesera , std::string _img ){
    id_usuario = usuario;
    id_post = _id_post;
    fecha = _fecha;
    cabecera = _cabesera;
    img = _img;
    like = 0;
    dislike = 0;
}
void Post::new_comentario(Comentario comentario){
    comentarios.insert(comentario);
}

void Post::dar_like(){
    like++;
}

void Post::mostrar(){

    std::cout << "Post ID: "
              << id_post << "\n";

    std::cout << "Usuario: "
              << id_usuario << "\n";

    std::cout << "Cabecera: "
              << cabecera << "\n";

    std::cout << "Imagen: "
              << img << "\n";

    std::cout << "Likes: "
              << like << "\n";

    std::cout << "Dislikes: "
              << dislike << "\n";

    std::cout << "Comentarios: "<< comentarios.current<< "\n";
}
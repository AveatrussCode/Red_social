#ifndef POST_H
#define POST_H

#include <string>
#include "Comentario.h"
#include "Listas.h"

class Post{
    public:
        long long id_usuario;
        long long id_post;

        int fecha;
        std::string cabecera;
        std::string img; // no hay soporte para imagenes por que esto se correra en the temrinal, so, i neet a description of img

        long like;
        long dislike;


        Lista<std::string> Comentarios;

        Post(long long, long long, int, std::string, std::string);
        void new_comentario(std::string);

};
Post::Post(long long usuario, long long _id_post,int _fecha, std::string _cabesera , std::string _img ){
    id_usuario = usuario;
    id_post = _id_post;
    fecha = _fecha;
    cabecera = _cabesera;
    img = _img;
    like = 0;
    dislike = 0;
}
void Post::new_comentario(std::string comentario){
    Comentarios.insert(comentario);


}




#endif
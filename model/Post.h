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

        int like; //100
        int dislike;


        Lista<Comentario> Comentarios;

        Post(long long, long long, int, std::string, std::string);
        void new_comentario(Comentario);

};


#endif
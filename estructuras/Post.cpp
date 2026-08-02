#include "../model/Post.h"

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
    Comentarios.insert(comentario);
}

void Post::dar_like(){
    like++;
}
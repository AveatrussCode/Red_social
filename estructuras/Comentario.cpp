#include "../model/Comentario.h"

Comentario::Comentario(long long id_usuario, std::string texto){
    usuario = id_usuario;
    comentario = texto;
}


Comentario::Comentario(){
    usuario = 0;
    comentario = "";
}
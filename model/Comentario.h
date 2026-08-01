#ifndef COMENTARIO_H
#define COMENTARIO_H

#include <string>
class Comentario {
    public:
        long long id_comentario;
        long long usuario;
        std::string comentario;
        Comentario(long long,long long, std::string);
        bool operator==(const Comentario& otro);

};
Comentario::Comentario(long long _id_comentario, long long id_usuario, std::string _comentario){
    id_comentario = _id_comentario;
    usuario = id_usuario;
    comentario = _comentario;
}
bool Comentario::operator==(const Comentario& otro) {
    return id_comentario == otro.id_comentario;
}

#endif


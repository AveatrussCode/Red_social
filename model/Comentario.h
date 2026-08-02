#ifndef COMENTARIO_H
#define COMENTARIO_H

#include <string>
class Comentario {
    public:
        long long usuario;
        std::string comentario;
        Comentario(long long id_usuario, std::string texto);
        bool operator==(const Comentario& otro);

};
Comentario::Comentario(long long id_usuario, std::string _comentario){
    usuario = id_usuario;
    comentario = _comentario;
}


#endif


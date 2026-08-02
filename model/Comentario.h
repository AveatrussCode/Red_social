#ifndef COMENTARIO_H
#define COMENTARIO_H

#include <string>
class Comentario {
    public:
        long long usuario;
        std::string comentario;
        Comentario();
        Comentario(long long id_usuario, std::string texto);
        bool operator==(const Comentario& otro);

};



#endif


#include "../model/CreadorBots.h"

#include <string>

CreadorBots::CreadorBots(
    Sistema& sistema,
    unsigned long long semilla
) : sistema(sistema) {

    if (semilla == 0) {
        semilla = 88172645463325252ULL;
    }

    estadoRandom = semilla;
    siguienteComentarioId = 1;
}

/*
    Generador pseudoaleatorio Xorshift.

    No utiliza:
    - vector
    - map
    - unordered_map
    - queue
    - ninguna estructura STL
*/
unsigned long long CreadorBots::siguienteRandom() {
    estadoRandom ^= estadoRandom << 13;
    estadoRandom ^= estadoRandom >> 7;
    estadoRandom ^= estadoRandom << 17;

    return estadoRandom;
}

long long CreadorBots::randomEntre(
    long long minimo,
    long long maximo
) {
    if (maximo <= minimo) {
        return minimo;
    }

    unsigned long long rango =
        static_cast<unsigned long long>(maximo - minimo + 1);

    return minimo +
        static_cast<long long>(siguienteRandom() % rango);
}

std::string CreadorBots::generarNombre(long long numeroBot) {
    static const char* nombres[] = {
        "Ana", "Luis", "Carlos", "Maria",
        "Lucia", "Pedro", "Valeria", "Diego",
        "Camila", "Jose", "Daniel", "Andrea",
        "Sofia", "Miguel", "Renata", "Jorge"
    };

    static const char* apellidos[] = {
        "Quispe", "Flores", "Rojas", "Torres",
        "Mendoza", "Vargas", "Castro", "Ramirez",
        "Huaman", "Salazar", "Paredes", "Chavez",
        "Condori", "Lopez", "Sanchez", "Medina"
    };

    const long long cantidadNombres = 16;
    const long long cantidadApellidos = 16;

    long long posicionNombre =
        randomEntre(0, cantidadNombres - 1);

    long long posicionApellido =
        randomEntre(0, cantidadApellidos - 1);

    std::string resultado;

    resultado += nombres[posicionNombre];
    resultado += " ";
    resultado += apellidos[posicionApellido];
    resultado += " Bot";
    resultado += std::to_string(numeroBot);

    return resultado;
}

std::string CreadorBots::generarTextoPost() {
    static const char* textos[] = {
        "Hoy fue un buen dia para aprender algo nuevo.",
        "Trabajando en un nuevo proyecto.",
        "Que opinan sobre las estructuras de datos?",
        "Acabo de publicar mi primera actualizacion.",
        "Programar tambien es resolver problemas.",
        "Saludos a todos mis amigos.",
        "Hoy estoy practicando algoritmos.",
        "Me gusta conocer personas nuevas.",
        "Terminando algunas tareas pendientes.",
        "Preparandome para una nueva semana.",
        "Alguien mas esta aprendiendo C++?",
        "Las tablas hash son bastante interesantes.",
        "Un cafe y a seguir programando.",
        "Compartiendo un poco de mi dia.",
        "Espero que todos tengan un excelente dia."
    };

    const long long cantidadTextos = 15;

    return textos[randomEntre(0, cantidadTextos - 1)];
}

std::string CreadorBots::generarComentario() {
    static const char* comentarios[] = {
        "Excelente publicacion.",
        "Estoy de acuerdo.",
        "Muy interesante.",
        "Gracias por compartir.",
        "Que buena idea.",
        "Me gusto bastante.",
        "Buen trabajo.",
        "Pienso algo parecido.",
        "Saludos.",
        "Interesante punto de vista.",
        "Totalmente cierto.",
        "Espero ver mas publicaciones."
    };

    const long long cantidadComentarios = 12;

    return comentarios[
        randomEntre(0, cantidadComentarios - 1)
    ];
}

void CreadorBots::generarAutomaticamente() {
    long long cantidad = randomEntre(1000, 20000);
    generar(cantidad);
}

void CreadorBots::generar(long long cantidad) {
    if (cantidad < 1) {
        cantidad = 1;
    }

    if (cantidad > 20000) {
        cantidad = 20000;
    }

    crearBots(cantidad);
    crearAmistades();
    crearPublicaciones();
    crearInteracciones();
}

void CreadorBots::crearBots(long long cantidad) {
    for (long long i = 0; i < cantidad; i++) {
        std::string nombre = generarNombre(i + 1);

        Usuario* nuevoBot =
            sistema.registrar_usuario(nombre);

        if (nuevoBot != nullptr) {
            idsBots.insert(nuevoBot->id);
        }
    }
}

bool CreadorBots::conectarUsuarios(
    long long idUsuario1,
    long long idUsuario2
) {
    if (idUsuario1 == idUsuario2) {
        return false;
    }

    Usuario* usuario1 =
        sistema.buscar_usuario(idUsuario1);

    Usuario* usuario2 =
        sistema.buscar_usuario(idUsuario2);

    if (usuario1 == nullptr || usuario2 == nullptr) {
        return false;
    }

    /*
        Evitamos amistades repetidas.

        amigos.buscar(...) devuelve:
        - posición si existe
        - -1 si no existe
    */
    if (usuario1->amigos.buscar(idUsuario2) != -1) {
        return false;
    }

    usuario1->agregar_amigo(idUsuario2);
    usuario2->agregar_amigo(idUsuario1);

    return true;
}

void CreadorBots::crearAmistades() {
    if (idsBots.current < 2) {
        return;
    }

    for (long long i = 0; i < idsBots.current; i++) {
        long long idBotActual = idsBots.lista[i];

        /*
            Cada bot intenta agregar entre 2 y 15 amigos.

            Puede terminar con menos, porque:
            - no puede agregarse a sí mismo;
            - no se permiten amistades duplicadas.
        */
        long long cantidadAmigos =
            randomEntre(2, 15);

        for (long long j = 0; j < cantidadAmigos; j++) {
            long long posicionAleatoria =
                randomEntre(0, idsBots.current - 1);

            long long idOtroBot =
                idsBots.lista[posicionAleatoria];

            conectarUsuarios(idBotActual, idOtroBot);
        }
    }
}

void CreadorBots::crearPublicaciones() {
    for (long long i = 0; i < idsBots.current; i++) {
        long long idBot = idsBots.lista[i];

        /*
            Cada bot crea entre 1 y 5 publicaciones.
        */
        long long cantidadPublicaciones =
            randomEntre(1, 5);

        for (
            long long publicacion = 0;
            publicacion < cantidadPublicaciones;
            publicacion++
        ) {
            /*
                Fecha simulada del 1 al 28 de agosto de 2026.

                Se usa hasta el día 28 para evitar fechas inválidas.
            */
            int dia = static_cast<int>(randomEntre(1, 28));
            int fecha = 20260800 + dia;

            std::string texto = generarTextoPost();

            /*
                Como el programa no maneja imágenes reales,
                guardamos una descripción.
            */
            std::string imagen;

            if (randomEntre(0, 3) == 0) {
                imagen = "Fotografia simulada del bot";
            } else {
                imagen = "";
            }

            Post* nuevoPost = sistema.crear_post(
                idBot,
                fecha,
                texto,
                imagen
            );

            if (nuevoPost != nullptr) {
                idsPosts.insert(nuevoPost->id_post);

                Usuario* propietario =
                    sistema.buscar_usuario(idBot);

                /*
                    El Sistema actual no agrega automáticamente
                    la publicación al usuario, por eso se hace aquí.

                    Cuando corrijas Sistema::crear_post para que lo
                    haga automáticamente, elimina estas líneas.
                */
                if (propietario != nullptr) {
                    if (
                        propietario->publicaciones.buscar(
                            nuevoPost->id_post
                        ) == -1
                    ) {
                        propietario->agregar_publicacion(
                            nuevoPost->id_post
                        );
                    }
                }
            }
        }
    }
}

void CreadorBots::crearInteracciones() {
    if (
        idsBots.current == 0 ||
        idsPosts.current == 0
    ) {
        return;
    }

    /*
        Número de interacciones proporcional a los bots.

        Por ejemplo:
        - 1,000 bots  -> aproximadamente 8,000 interacciones
        - 20,000 bots -> aproximadamente 160,000 interacciones
    */
    long long cantidadInteracciones =
        idsBots.current * 8;

    for (
        long long i = 0;
        i < cantidadInteracciones;
        i++
    ) {
        long long posicionUsuario =
            randomEntre(0, idsBots.current - 1);

        long long posicionPost =
            randomEntre(0, idsPosts.current - 1);

        long long idUsuario =
            idsBots.lista[posicionUsuario];

        long long idPost =
            idsPosts.lista[posicionPost];

        Post* post = sistema.buscar_post(idPost);

        if (post == nullptr) {
            continue;
        }

        /*
            Tipo de interacción:
            0-5: like
            6: dislike
            7-9: comentario

            Así los likes son más frecuentes.
        */
        long long tipoInteraccion = randomEntre(0, 9);

        if (tipoInteraccion <= 5) {
            post->like++;
            sistema.registrar_reaccion_usuario(idUsuario);
        }
        else if (tipoInteraccion == 6) {
            post->dislike++;
            sistema.registrar_reaccion_usuario(idUsuario);
        }
        else {
            Comentario nuevoComentario(idUsuario,generarComentario());

            post->new_comentario(nuevoComentario);
            sistema.registrar_comentario_usuario(idUsuario);
        }
    }
}

long long CreadorBots::cantidadBots() const {
    return idsBots.current;
}

long long CreadorBots::cantidadPosts() const {
    return idsPosts.current;
}

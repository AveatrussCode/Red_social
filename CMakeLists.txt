cmake_minimum_required(VERSION 3.8)

project(Facebook2)

add_executable(hi
    estructuras/CreadorBots.cpp
    estructuras/GrafoAmistad.cpp
    estructuras/Interfaz.cpp
    estructuras/Post.cpp
    estructuras/Sistema.cpp
    estructuras/Usuario.cpp
    estructuras/Comentario.cpp
    main.cpp
)
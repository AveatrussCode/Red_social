Facebook 2 — red social hecha a mano en C++

Backend de una red social simplificada, hecho para el curso de Algoritmos y Estructuras de Datos. La regla del juego era no usar nada de la STL (nada de vector, map, list, etc.) así que todo — arreglo dinámico, lista enlazada, tabla hash, heap — está escrito desde cero.

¿Qué hace?
Registrar usuarios e iniciar sesión.
Crear publicaciones, comentar y dar like.
Agregar amigos.
Ver perfil, feed y tus propias publicaciones.
Rankings: usuarios más activos y posts con más reacciones.
Un generador de bots que puebla todo esto automáticamente al arrancar (usuarios, amistades, posts e interacciones aleatorias), para poder probar el sistema con volumen real de datos.
Cómo compilar y correr
bash
g++ -std=c++17 -O2 -o facebook2 estructuras/*.cpp main.cpp
./facebook2

O con CMake, si lo prefieres:

bash
cmake -B build && cmake --build build

Al arrancar, el programa se puebla solo con entre 1 000 y 20 000 bots (usuarios ficticios) antes de mostrarte el menú, así que no vas a ver una app vacía.

Cómo está armado por dentro
model/          <- headers: las clases y sus firmas
estructuras/    <- .cpp: la implementación
main.cpp        <- arranca todo

Las piezas clave:

Lista<T>: un arreglo que se duplica solo cuando se llena. Es nuestro vector casero.
Lista_enlazada<V>: lista enlazada simple, la usamos para resolver colisiones en el hash.
Hash<V>: tabla hash con id % size, cada bucket es una Lista_enlazada. Guarda usuarios y posts por id.
HeapTree<T>: max-heap genérico, recibe un comparador por función. Se usa solo para armar los rankings cuando se piden (no vive persistente en memoria).
Usuario y Post: el modelo de datos. Cada usuario guarda sus amigos y sus posts como listas de ids — ahí vive el "grafo" de amistad, de forma implícita (cada usuario conoce a sus vecinos directos, no hay una clase Grafo aparte).
CreadorBots: genera datos falsos con un generador pseudoaleatorio propio (Xorshift, para no depender de <random> de la STL).
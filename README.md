# Facebook 2 — Red social hecha a mano en C++

Backend de una red social simplificada desarrollado para el curso de **Algoritmos y Estructuras de Datos**.

La principal restricción del proyecto fue **no utilizar contenedores de la STL** (`vector`, `map`, `list`, `unordered_map`, etc.), por lo que todas las estructuras de datos fundamentales fueron implementadas manualmente desde cero.

---

## Características

* Registro de usuarios.
* Inicio de sesión mediante ID.
* Creación de publicaciones.
* Comentarios en publicaciones.
* Reacciones (likes y dislikes).
* Gestión de amistades.
* Visualización de perfiles.
* Visualización de publicaciones propias.
* Ranking de usuarios más activos.
* Ranking de publicaciones con más reacciones.
* Generación automática de bots para poblar la red social y realizar interacciones simuladas.

---

## Compilación

### Usando g++

```bash
g++ -std=c++17 -O2 -o facebook2 estructuras/*.cpp main.cpp
```

### Ejecutar

```bash
./facebook2
```

---

## Compilación con CMake

```bash
cmake -B build
cmake --build build
```

### Ejecutar

```bash
./build/facebook2
```

---

## Generación automática de datos

Al iniciar el programa se ejecuta automáticamente un generador de bots que crea entre **1 000 y 20 000 usuarios simulados**.

Los bots realizan acciones como:

* Crear perfiles.
* Formar amistades.
* Publicar contenido.
* Comentar publicaciones.
* Dar likes y dislikes.

Esto permite probar el comportamiento de la aplicación con una cantidad considerable de datos sin necesidad de ingresar información manualmente.

---

## Estructura del proyecto

```text
Facebook2/
│
├── model/
│   ├── Usuario.h
│   ├── Post.h
│   ├── Comentario.h
│   ├── Listas.h
│   ├── Lista_enlazada.h
│   ├── Tabla_hash.h
│   └── HeapTree.h
│
├── estructuras/
│   ├── Usuario.cpp
│   ├── Post.cpp
│   ├── Sistema.cpp
│   ├── CreadorBots.cpp
│   └── Interfaz.cpp
│
├── main.cpp
├── CMakeLists.txt
└── README.md
```

---

## Estructuras de datos implementadas

### Lista<T>

Arreglo dinámico implementado manualmente.

Características:

* Crecimiento automático.
* Inserción.
* Búsqueda lineal.
* Eliminación por desplazamiento.

Cumple el papel de un `vector`, pero sin utilizar STL.

---

### Lista_enlazada<V>

Lista enlazada simple.

Características:

* Inserción.
* Búsqueda.
* Eliminación.
* Almacenamiento de pares `(id, valor)`.

Se utiliza principalmente para resolver colisiones dentro de la tabla hash.

---

### Hash<V>

Tabla hash genérica implementada desde cero.

Características:

* Función hash basada en:

```cpp
id % size
```

* Encadenamiento separado mediante listas enlazadas.
* Inserción.
* Búsqueda.
* Eliminación.
* Verificación de existencia.

Se utiliza para almacenar:

* Usuarios.
* Publicaciones.

---

### HeapTree<T>

Implementación de un Max Heap genérico.

Características:

* Inserción.
* Extracción del máximo.
* Comparador configurable mediante función.

Se utiliza para generar:

* Ranking de usuarios más activos.
* Ranking de publicaciones más reaccionadas.

El heap se construye únicamente cuando se solicita un ranking.

---

## Modelo de datos

### Usuario

Cada usuario almacena:

* ID único.
* Nombre.
* Correo generado automáticamente.
* Fecha de registro.
* Cantidad de amigos.
* Cantidad de seguidores.
* Reacciones recibidas.
* Publicaciones realizadas.
* Comentarios realizados.
* Reacciones realizadas.

Además mantiene listas de IDs para:

* Amigos.
* Publicaciones.

Las relaciones de amistad forman implícitamente un grafo social.

---

### Post

Cada publicación almacena:

* ID único.
* Usuario propietario.
* Fecha.
* Texto principal.
* Descripción de imagen.
* Likes.
* Dislikes.
* Comentarios.

---

### Comentario

Cada comentario almacena:

* Usuario que comenta.
* Contenido del comentario.

---

## Sistema

La clase `Sistema` actúa como núcleo de la aplicación.

Responsabilidades:

* Registrar usuarios.
* Crear publicaciones.
* Buscar usuarios.
* Buscar publicaciones.
* Gestionar la sesión actual.
* Actualizar estadísticas de actividad.
* Generar rankings.

---

## Generador de Bots

La clase `CreadorBots` genera datos de prueba automáticamente.

Características:

* Generador pseudoaleatorio propio basado en **Xorshift**.
* Creación masiva de usuarios.
* Creación de amistades aleatorias.
* Generación de publicaciones.
* Likes y dislikes automáticos.
* Comentarios automáticos.

No depende de `<random>` ni de contenedores STL.

---

## Restricciones del proyecto

Este proyecto fue desarrollado siguiendo las restricciones del curso:

* No utilizar `vector`.
* No utilizar `map`.
* No utilizar `unordered_map`.
* No utilizar `list`.
* No utilizar estructuras STL equivalentes.

Todas las estructuras utilizadas fueron implementadas manualmente.

---

## Autores

Proyecto desarrollado para el curso de **Algoritmos y Estructuras de Datos**.

**Facebook 2** es una implementación educativa enfocada en la construcción de estructuras de datos fundamentales y su aplicación en una red social simplificada.

# Red_social
Este pryecto se trata de crear una simulacion sobre una red social




okey usare esta parte como bitacora,
se decicio optar pr una estructura de nodos, en este caos cada ndoos usuairo tendra una lista que indicara o susn amifogs  o sus post, esot con un id  amanera ams parctica
El caso de lista es escxpecial  aya que s epondra todo el copdigo dentor del .h a fiun de reducir la funcionalidad de todo este proceso



# 🚀 Social Network AED

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue">
  <img src="https://img.shields.io/badge/Status-In%20Development-orange">
  <img src="https://img.shields.io/badge/Course-Algorithms%20and%20Data%20Structures-green">
</p>

---

## 📖 About the Project

This project implements the core backend of a social network inspired by Facebook.

The objective is to manage large-scale collections of:

* 👤 Users
* 🤝 Friendships
* 📝 Posts
* 💬 Comments
* 👍 Reactions

using only data structures implemented from scratch in C++.

The use of STL containers such as `vector`, `map`, `list`, `queue`, `unordered_map`, etc. is not allowed.

---

# 🏗️ Current Architecture

```text
Sistema
│
├── UserManager
│
├── PostManager
│
├── HashTable Usuarios
│
├── HashTable Publicaciones
│
└── Grafo de Amistades
```

---

# 📂 Project Structure

```text
Project
│
├── main.cpp
│
├── Models
│   ├── Usuario.h
│   ├── Post.h
│   └── Comentario.h
│
├── Structures
│   ├── Vector.h
│   ├── LinkedList.h
│   ├── HashTable.h
│   ├── Graph.h
│   └── Heap.h
│
├── Managers
│   ├── UserManager.h
│   └── PostManager.h
│
└── Docs
```

---

# 🧠 Data Structures

## Dynamic Vector

Status:

* [x] Implemented
* [ ] Tested
* [ ] Documented

Operations:

| Operation | Complexity     |
| --------- | -------------- |
| Insert    | O(1) amortized |
| Search    | O(n)           |
| Delete    | O(n)           |

---

## Linked List

Status:

* [ ] Implemented
* [ ] Tested
* [ ] Documented

Purpose:

* Hash collision resolution
* Internal storage

---

## Hash Table

Status:

* [ ] Implemented
* [ ] Tested
* [ ] Documented

Purpose:

* User lookup
* Post lookup

Expected Complexity:

| Operation | Complexity |
| --------- | ---------- |
| Insert    | O(1)       |
| Search    | O(1)       |
| Delete    | O(1)       |

---

## Friendship Graph

Status:

* [ ] Implemented
* [ ] Tested
* [ ] Documented

Features:

* Friend suggestions
* Common friends
* Friendship path

Algorithm:

```text
BFS
```

---

## Publication Ranking Structure

Status:

* [ ] Under Design

Possible candidates:

* Heap
* AVL Tree
* B+ Tree

Final decision pending.

---

# 👤 User Model

```text
Usuario
│
├── id
├── nombre
├── correo
├── fechaRegistro
│
├── amigos
│   ├── id_1
│   ├── id_2
│   └── ...
│
└── publicaciones
    ├── post_1
    ├── post_2
    └── ...
```

---

# 📝 Post Model

```text
Post
│
├── id
├── owner
├── date
├── title
├── imageDescription
├── likes
├── dislikes
│
└── comments
```

---

# 💬 Comment Model

```text
Comment
│
├── id
├── author
└── text
```

---

# 📈 Complexity Summary

| Feature            | Structure  | Complexity |
| ------------------ | ---------- | ---------- |
| Search User        | Hash Table | O(1)       |
| Search Post        | Hash Table | O(1)       |
| Add Friend         | Graph      | O(1)       |
| Friend Path        | BFS        | O(V + E)   |
| Common Friends     | Graph      | O(n)       |
| Most Popular Posts | Heap       | O(log n)   |

---

# 🧪 Performance Tests

## Users

| Users     | Time    |
| --------- | ------- |
| 1,000     | Pending |
| 10,000    | Pending |
| 100,000   | Pending |
| 1,000,000 | Pending |

---

# 📌 Development Log

## 2026-07-31

* [x] Dynamic Vector implemented
* [x] User class created
* [x] Post class created
* [ ] Comment class pending
* [ ] Hash Table pending

---

# 🎯 Pending Tasks

* [ ] Convert Vector to Template
* [ ] Implement Linked List
* [ ] Implement Hash Table
* [ ] Implement Graph
* [ ] Implement BFS
* [ ] Implement Post Ranking Structure
* [ ] Generate Synthetic Dataset
* [ ] Performance Benchmarks

---

# 📄 License

Academic project developed for the Algorithms and Data Structures course.

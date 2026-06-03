# Nombre-Jimy-Morales-Curso-Programacion-III-proyecto-final-red-social-academica

Red Social Académica

Proyecto final del curso de Estructuras de Datos. Sistema desarrollado en C++ que simula una red social universitaria donde los estudiantes pueden conectarse, registrar proyectos académicos y competir en un ranking.

¿Qué hace el sistema?

Carga una base de 10,000 estudiantes desde un archivo CSV y permite gestionarlos a través de un menú interactivo. Se pueden crear conexiones entre estudiantes, agregar proyectos académicos, buscar por ID, ver el ranking académico y recorrer la red usando BFS y DFS.

Estructuras utilizadas

- Tabla Hash — búsqueda rápida de estudiantes por ID
- Árbol AVL — ranking académico ordenado automáticamente
- Grafo — red de conexiones entre estudiantes
- Lista enlazada — proyectos de cada estudiante
- Cola — solicitudes de conexión pendientes

Estructura del repositorio

proyecto-final/
├── cpp-system/
├── java-benchmark/
├── dataset/
├── evidencias/
└── README.md

Benchmark

Se midió el rendimiento de las estructuras en C++ contra las nativas de Java. C++ resultó significativamente más rápido en todas las operaciones medidas.

Tecnologías

- C++ con CLion
- Java con Apache NetBeans

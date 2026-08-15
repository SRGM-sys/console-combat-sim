<div align="center">
  <h1>Shadow Realm Tactics</h1>
  <p><em>Un juego de combate por turnos en línea de comandos desarrollado en C++</em></p>
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++ Badge" />
</div>

<br>

## Acerca del juego

Toma el control de un grupo de tres héroes (Arquero, Sacerdote y Escudero) en una batalla contrarreloj frente al formidable Rey Demonio. Tienes un límite estricto de 60 turnos para gestionar la salud de tu equipo, utilizar las habilidades únicas de cada clase y mitigar los efectos de estado. Cada turno aliado se asigna de forma aleatoria a uno de tus héroes supervivientes, lo que te obligará a adaptar tu estrategia sobre la marcha para asegurar la victoria antes de que el contador llegue a cero.

## Características principales del código

* **Programación Orientada a Objetos:** Implementación de una superclase abstracta `Personaje` con métodos virtuales puros (`activarHabilidad`) y sobrecarga de operadores para el formateo de datos, permitiendo un polimorfismo limpio entre las clases derivadas de los héroes y el enemigo.
* **Gestión de estados a nivel de bits:** Uso avanzado de `std::bitset` y máscaras de bits (ej. `0b1'1000`) para optimizar el registro y la limpieza de los efectos de estado (Envenenado, Vulnerado, Debilitado) aplicados durante el combate.
* **Estructuras de datos dinámicas:** Manejo del grupo activo a través de un `std::vector` de punteros (`vector<Personaje*>`). El programa identifica y elimina dinámicamente a los héroes caídos de la memoria usando `std::find` y reajusta sus índices en tiempo real.
* **Sistema de combate probabilístico (RNG):** Algoritmos de toma de decisiones aleatorias (`rand()`) que determinan tanto la selección del héroe en cada turno como el comportamiento de la IA del enemigo, el cual cuenta con un 60% de probabilidad de realizar un ataque directo y un 40% de aplicar penalizaciones.

## Imagen del juego

<div align="center">
  <img src="./screenshot1.png" width="45%" alt="Captura del menú de batalla">
  <br>
  <em>Captura que muestra el combate por turnos, la interfaz de la terminal y la información de los personajes.</em>
</div>

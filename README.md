# sld-pong-cpp
Un pequeño proyecto de Pong hecho con C++ y SDL para la UADE.

## Prerequisitos
- Microsoft Visual Studio 2019

Todo el código fue escrito con Microsoft Visual Studio 2019 y la idea es correrlo con ese programa. (ADVERTENCIA: Tiene que ser en la versión v142, en otras versiones no se reconocen grandes partes del código).

## Ejecución del Programa
- Descargar el repositorio.
- Entrar a la carpeta "project".
- Abrir el archivo "SDL_Project.2019.sln".
- Depurar (si estás en Visual Studio) o compilar.

![El juego](/doc/img/game.png)

## Funciones
En "SDL_Project.cpp" encontrarás toda la base que posibilita la ejecución del programa:
- La inicialización del programa mismo
`void initEngine();`
- La carga de los assets de sprite, texto y sonido
`void loadAssets();`
- La carga y liberación de recursos
`void unloadAssets();`
- La actualización y pintado
`void inputUpdate();`
`void updateGame(float deltaTime);`
`void render();`
- Finalmente, el main (y hay algunas funciones agregadas que fueron parte de "experimentos fallidos", pero que si saco el programa deja de funcionar...)

En "GSLogoState.cpp" se encuentra todo el código modularizado que le da al programa las mecánicas del Pong:
- `void P1StateUpdate(float delta, ResourceManager& resource)` define al Jugador 1.
- `void P2StateUpdate(float delta, ResourceManager& resource)` define al Jugador 2.
- `void BallStateUpdate(float delta, ResourceManager& resource)` define a la pelota y su interacción con el resto de objetos.
- `void EndStateUpdate(float delta, ResourceManager& resource)` define cuando termina el juego y las acciones del programa cuando esto sucede.

Todos los botones/teclas utilizados por los controles del programa están especificados en "InputModule.cpp".

Los cambios en "StructsDef.h", "GSLogoState.h" y "InputModule.h" son mínimos, pero importante ya que posibilitan que los nuevos módulos cumplan su función.

![Codigo del programa](/doc/img/morecode.png)

# Creación de Videojuegos - De Astra Ad Terra

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue?style=flat-square)
![Lua](https://img.shields.io/badge/Scripting-Lua-2C2D72?style=flat-square)
![ASAN](https://img.shields.io/badge/Memory%20Cleaned-ASAN-success?style=flat-square)
![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen?style=flat-square)
![GitHub Repo Size](https://img.shields.io/github/repo-size/archibald-carrion/The-Templar?style=flat-square)

## Entrega

Fecha de entrega: 8 de diciembre de 2024

## Descripción del juego

Es un juego de ciencia ficción en el que el jugador controla a un caballero que debe enfrentarse a enemigos en un mundo de invierno eterno.
El juego cuenta con :

- un menú principal
- cuatro niveles
- una pantalla de "muerte" donde llega el jugador si se muere que permite redirrecionar a los cuatro niveles
- una pantalla de "congratulation" que permite redirrecionar al menu principal
  El juego cuenta con música de fondo y assets de itch.io.

## Controles

- A: Mueve al jugador a la izquierda
- D: Mueve al jugador a la derecha
- Espacio: Saltar
- Esc: Salir del juego
- E: Disparar
- Q: Disparar el power up shoot
- P: Pausar el juego

## Historia del juego

El Portador del Invierno
Un mundo desolado y cubierto por un invierno eterno, donde una fuerza oscura ha transformado un castillo ancestral en la fuente de la maldición que consume la tierra. Sir Fort, el último caballero de los Guardianes del Invierno, emprende una misión desesperada para enfrentar el origen del hielo eterno y restaurar la esperanza.

Nivel 1: Las Afueras del Castillo
Sir Fort atraviesa las gélidas tierras que rodean el castillo, enfrentándose a sombras pequeñas y bandadas de murciélagos que atacan desde el aire. Entre ruinas cubiertas de nieve, descubre que las criaturas parecen emanar del interior del castillo. Este nivel introduce mecánicas básicas de combate y exploración, como el manejo de su espada y el uso estratégico de su escudo para repeler ataques.

Nivel 2: Los Pasillos del Castillo
Dentro del castillo, Sir Fort recorre oscuros y fríos pasillos llenos de trampas y enemigos más desafiantes, como sombras más ágiles y murciélagos que atacan en oleadas coordinadas. También encuentra gigantes de hielo, criaturas imponentes que requieren precisión y estrategia para derrotar. Este nivel prueba las habilidades avanzadas del jugador y presenta objetos ocultos que ofrecen pistas sobre la maldición.

Nivel 3: El Calabozo Profundo
En lo más profundo del castillo, Fort explora un lúgubre calabozo lleno de ecos de sufrimiento. Los gigantes de hielo se vuelven más frecuentes, y las sombras pequeñas atacan en grupos, haciendo del combate una prueba de resistencia. Aquí, Sir Fort encuentra fragmentos de escritos antiguos que revelan que una sombra gigantesca surgió tras un antiguo ritual que salió mal, transformando al castillo y a sus habitantes en instrumentos de la oscuridad.

Nivel 4: El Corazón del Invierno
En la sala central del castillo, Fort finalmente se enfrenta a la sombra titánica, una colosal manifestación del poder oscuro que trajo el invierno eterno. La batalla final es feroz, con la sombra utilizando ataques devastadores y el entorno helado en su favor. Con ingenio y valentía, Fort logra derrotarla, rompiendo la maldición y permitiendo que el sol vuelva a brillar en el mundo.

## Objetivos del juego

Para ir avanzando en el juego, el jugador debe:

- Buscar la puerta de salida en cada nivel sin morir para avanzar al siguiente nivel
- Destruir a los enemigos para obtener puntos y poder obtener el power up shoot
- Matar al final boss para ganar el juego

## 4 enemigos

En mi juego hay 4 enemigos:

- Murciélagos: Son enemigos voladores que se mueven de arriba a bajo, tienen 1 de vida y 1 de daño
- Sombras: Son enemigos que se mueven de izquierda a derecha, tienen 1 de vida y 1 de daño
- Gigante de Hielo: Es un enemigo que se mueve de izquierda a derecha, tiene 3 de vida y 1 de daño
- Boss: Es un enemigo que se mueve de izquierda a derecha, tiene 20 de vida y 1 de daño

## Guía de uso

Para compilar el programa, ejecute el siguiente comando:

```bash
make clean; make; make run
```

El proyecto fue desarrollado en Ubuntu 24.04 en WSL2, utilizando el compilador g++ 13.2.0

El makefile para funcionar con mi arquitectura de carpeta fue modificado.

## Proceso de desarrollo

Para desarrollar el juego se uso el motor hecho en clase, el desarrollo se llevo a cabo siguiendo los videos disponibles en la plataforma, y agregando poco a poco las funcionalidades requeridas por la tarea.

Los principales cambios realizados en el motor fueron los siguientes:

- Se agrego un audio manager para reproducir música de fondo y efectos de sonido
- Se agregaron nuevos lua bindings para poder cargar y reproducir música y efectos de sonido
- Se arreglaron varios bugs en el motor, como el bug que no borraba los entities y components al cambiar de escena, lo cual llevaba a tener nuevos entities con componentes de la escena anterior
- Los niveles fueron creados utilizando Tiled, y se crearon scripts en lua para cargar los niveles y los assets necesarios
- Se agregaron nuevos componentes y sistemas para manejar la lógica de los enemigos y del jugador

Adjunto se agrego una serie de screenshots del juego ejecutandose:
![screenshot del menu del juego](documentation/main_menu.PNG)
![screenshot del primer nivel](documentation/level_01.PNG)
![screenshot del segundo nivel](documentation/level_02.PNG)
![screenshot del tercer nivel](documentation/level_03.PNG)
![screenshot del cuarto nivel](documentation/level_04.PNG)
![screenshot de la pantalla de "muerte"](documentation/fail_screen.PNG)
![screenshot de la pantalla de "congratulation"](documentation/win_screen.PNG)

## Instalación de las bibliotecas necesarias

Para instalar las bibliotecas necesarias en linux, ejecute el siguiente comando:

```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev lua5.3 liblua5.3-dev libtinyxml2-dev
```

## Puntos extras

Para obtener puntos extras, implemente las siguientes características:

- [x] Se implemento el audio manager para reproducir música de fondo y efectos de sonido, ademas se usaron audios hechos propios por [Namlin] (https://github.com/namlin)
- [x] Se implementó el uso de mandos para controlar al jugador

## UML del motor de videojuegos

```mermaid
classDiagram
    class Game {
        -window: SDL_Window*
        -camera: SDL_Rect
        -isRunning: bool
        -mPreviousFrame: int
        -isPaused: bool
        -map_height: int
        -map_width: int
        -player_location: std::tuple<int, int>
        -player_score: int
        -WINDOW_WIDTH: int
        -WINDOW_HEIGHT: int
        -renderer: SDL_Renderer*
        -registry: std::unique_ptr<Registry>
        -scene_manager: std::unique_ptr<SceneManager>
        -assets_manager: std::unique_ptr<AssetsManager>
        -events_manager: std::unique_ptr<EventManager>
        -controller_manager: std::unique_ptr<ControllerManager>
        -audio_manager: std::unique_ptr<AudioManager>
        -animation_manager: std::unique_ptr<AnimationManager>
        -stats_manager: std::unique_ptr<StatsManager>
        -lua: sol::state
        +Game()
        +~Game()
        +processInput()
        +update()
        +render()
        +setup()
        +run_scene()
        +init()
        +run()
        +destroy()
        +print_game_data()
        +get_instance(): Game&
    }
    class SceneManager{
        -std::map<std::string, std::string> scenes
        -std::string next_scene
        -bool is_scene_running
        -std::unique_ptr<SceneLoader> scene_loader

        +SceneManager()
        +~SceneManager()

        +get_next_scene()
        +load_scene_from_script()
        +load_scene()
        +set_next_scene()
        +is_current_scene_running()
        +start_scene()
        +stop_scene()
    }

    class AssetsManager {
        -textures: std::map<std::string, SDL_Texture*>
        -fonts: std::map<std::string, TTF_Font*>
        +AssetsManager()
        +~AssetsManager()
        +clear_assets()
        +add_texture(SDL_Renderer*, std::string, std::string)
        +get_texture(std::string): SDL_Texture*
        +add_font(std::string, std::string, int)
        +get_font(std::string): TTF_Font*
    }
    class EventManager {
        -subscribers: std::map<std::type_index, std::unique_ptr<handler_list>>
        +EventManager()
        +~EventManager()
        +reset()
        +subscribe_to_event<TEvent, TOwner>(TOwner*, void (TOwner::*)(TEvent&))
        +emit_event<TEvent, TArgs>(TArgs...)
    }

    class ControllerManager {
        -action_key_name: std::map<std::string, int>
        -key_state: std::map<int, bool>
        -mouse_buttons_name: std::map<std::string, int>
        -mouse_button_state: std::map<int, bool>
        -mouse_position_x: int
        -mouse_position_y: int
        +ControllerManager()
        +~ControllerManager()
        +clear()
        +add_key(std::string, int)
        +is_key_pressed(std::string): bool
        +update_key(std::string, bool)
        +update_key(int, bool)
        +set_key_to_pressed(int)
        +set_key_to_pressed(std::string)
        +set_key_to_up(int)
        +set_key_to_up(std::string)
        +add_mouse_button(std::string, int)
        +is_mouse_button_pressed(std::string): bool
        +update_mouse_button(int, bool)
        +set_mouse_position(int, int)
        +get_mouse_position(): std::tuple<int, int>
        +set_mouse_button_to_pressed(int)
        +set_mouse_button_to_up(int)
    }

    class AudioManager {
        -music_tracks: std::map<std::string, Mix_Music*>
        -sound_effects: std::map<std::string, Mix_Chunk*>
        +AudioManager()
        +~AudioManager()
        +add_music(std::string, std::string)
        +get_music(std::string): Mix_Music*
        +add_sound_effect(std::string, std::string)
        +get_sound_effect(std::string): Mix_Chunk*
        +play_music(std::string, int)
        +play_sound_effect(std::string, int)
        +stop_music(std::string)
        +stop_sound_effect(std::string)
        +stop_all_sounds()
        +clear_audio()
    }

    class Registry {
        -componentsPools: std::vector<std::shared_ptr<IPool>>
        -entityComponentSignatures: std::vector<Signature>
        -systems: std::unordered_map<std::type_index, std::shared_ptr<System>>
        -entities_to_be_added: std::set<Entity>
        -entities_to_be_killed: std::set<Entity>
        -free_ids: std::deque<int>
        +num_entities: int
        +Registry()
        +~Registry()
        +update()
        +create_entity(): Entity
        +kill_entity(Entity)
        +add_component<TComponent, TArgs>(Entity, TArgs...)
        +remove_component<TComponent>(Entity)
        +has_component<TComponent>(Entity): bool
        +get_component<TComponent>(Entity): TComponent&
        +add_system<TSystem, TArgs>(TArgs...)
        +remove_system<TSystem>(Entity)
        +has_system<TSystem>(Entity): bool
        +get_system<TSystem>(): TSystem&
        +add_entity_to_system(Entity)
        +remove_entity_from_system(Entity)
        +clear_all_entities()
    }
     class Entity {
        -id: int
        -registry: Registry*
        +Entity(int)
        +~Entity()
        +get_id(): int
        +kill()
        +operator==(const Entity& other) const: bool
        +operator!=(const Entity& other) const: bool
        +operator>(const Entity& other) const: bool
        +operator<(const Entity& other) const: bool  

        +add_component<TComponent, TArgs>(TArgs...)
        +remove_component<TComponent>()
        +has_component<TComponent>(): bool
        +get_component<TComponent>(): TComponent&
    }

    class System {
        -componentSignature: Signature
        -entities: std::vector<Entity>
        +System()
        +~System()
        +add_entity_to_system(Entity)
        +remove_entity_from_system(Entity)
        +get_entities(): std::vector<Entity>
        +get_signature(): const Signature&
        +RequireComponent<TComponent>()
    }


    class Component {
        +get_id() int
    }

    class SceneLoader {
        +SceneLoader()
        +~SceneLoader()
        +load_scene(std::string, sol::state&, std::unique_ptr<AssetsManager>&, std::unique_ptr<ControllerManager>&, std::unique_ptr<AudioManager>&, std::unique_ptr<Registry>&, SDL_Renderer*)
        -load_sounds(sol::table, std::unique_ptr<AudioManager>)
        -load_music(sol::table, std::unique_ptr<AudioManager>)
        -load_sprites(SDL_Renderer*, sol::table sprites, std::unique_ptr<AssetsManager>)
        -load_fonts(sol::table, std::unique_ptr<AssetsManager>)
        -load_buttons(sol::table, std::unique_ptr<ControllerManager>)
        -load_keys_actions(sol::table, std::unique_ptr<ControllerManager>)
        -load_entities(sol::state, sol::table, std::unique_ptr<Registry>)
        -load_entity(sol::state , Entity, sol::table)
        -load_animations(sol::table, std::unique_ptr<AnimationManager>)
        -LoadMap(sol::table, std::unique_ptr<Registry>, string, sol::state)
        -LoadLayer(std::unique_ptr<Registry>, tinyxml2::XMLElement*, int, int, int, string, int)
        -LoadColliders(std::unique_ptr<Registry>, tinyxml2::XMLElement*)
        -load_enemy_colliders(std::unique_ptr<Registry>, tinyxml2::XMLElement*)
        -load_enemies(Registry, string, tinyxml2::XMLElement*, sol::state)
        -load_damage_colliders(sol::table)
        -load_stats(sol::table)
    }

    class AnimationData {
        +string texture_id
        +int width
        +int height
        +int num_frames
        +int frame_speed_rate
        +bool is_loop
        +AnimationData(string texture_id, int width, int height, int num_frames, int frame_speed_rate, bool is_loop)
    }

    class AnimationManager {
        -map<string, AnimationData> animations
        +AnimationManager()
        +~AnimationManager()
        +void add_animation(string animation_id, string texture_id, int width, int height, int num_frames, int frame_speed_rate, bool is_loop)
        +AnimationData get_animation(string animation_id)
    }

    class StatsManager {
        -std::unordered_map<string, StatsComponent> _tagToStat
        -StatsManager()

        +static StatsManager& GetInstance()
        +void AddStat(string, StatsComponent)
        +void AddStatsToEntity(Entity&)
        +void Clear()
        +std::optional<StatsComponent> operator[](string)
    }

    SceneLoader "1" -- "1" SceneManager
    AnimationManager "1" -- "1" AnimationData
    Game "1" -- "1" Registry
    Game "1" -- "1" SceneManager
    Game "1" -- "1" AssetsManager
    Game "1" -- "1" EventManager
    Game "1" -- "1" ControllerManager
    Game "1" -- "1" AudioManager
    Game "1" -- "1" AnimationManager
    Game "1" -- "1" Registry
    Game "1" -- "1" StatsManager
    Registry "1" -- "*" Entity
    Registry "1" -- "*" System
    Entity "1" -- "0..*" Component
    System "*" -- "*" Entity

```

## Ressources used for the game

- [arcade classic font](https://www.1001fonts.com/arcadeclassic-font.html)
- [tileset de ruinas](https://bdragon1727.itch.io/platform-asset-part-4)
- [asset del knight](https://aamatniekss.itch.io/fantasy-knight-free-pixelart-animated-character)
- [asset del boss](https://zneeke.itch.io/dark-fantasy-big-boss-1)
- [asset de las sombras](https://zneeke.itch.io/dark-fantasy-monster-pack-1)
- [asset del gigante de hielo](https://chierit.itch.io/boss-frost-guardian)
- [asset de los murciélagos](https://zneeke.itch.io/dark-fantasy-monster-pack-1)
- [asset del power up shoot](https://gamedeveloperstudio.itch.io/snowball)
- Music made by game developer [Namlin](https://github.com/namlin)
- [dungeon tileset](https://raou.itch.io/dark-dun)

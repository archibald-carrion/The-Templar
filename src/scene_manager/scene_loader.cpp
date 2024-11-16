#include "scene_loader.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include "../game/game.hpp"
#include <sstream>

#include "../components/transform_component.hpp"
#include "../components/RigidBodyComponent.hpp"
#include "../components/sprite_component.hpp"
#include "../components/circle_collider_component.hpp"
#include "../components/animation_component.hpp"
#include "../components/script_component.hpp"
#include "../components/text_component.hpp"
#include "../components/clickable_component.hpp"
#include "../components/camera_follow_component.hpp"
#include "../components/box_collider_component.hpp"
#include "../components/tag_component.hpp"
#include "../components/player_velocity.hpp"
#include "../components/player_score_component.hpp"

SceneLoader::SceneLoader() {
    //std::cout << "[SCENELOADER] scene loader constructor" << std::endl;
}

SceneLoader::~SceneLoader() {
    //std::cout << "[SCENELOADER] scene loader destructor" << std::endl;
}

void SceneLoader::load_scene(const std::string& scene_path,
    sol::state& lua, 
    std::unique_ptr<AssetsManager>& asset_manager, 
    std::unique_ptr<ControllerManager>& controller_manager,
    std::unique_ptr<AudioManager>& audio_manager,
    std::unique_ptr<Registry>& registry,
    std::unique_ptr<AnimationManager>& animation_manager,
    SDL_Renderer* renderer) {

    // load the script
    sol::load_result script_result = lua.load_file(scene_path);
    if(!script_result.valid()) {
        sol::error err = script_result;
        std::string error_message = err.what();
        std::cerr << "[SCENELOADER] " << error_message << std::endl;
        return;
    }

    // load the scene
    lua.script_file(scene_path);
    sol::table scene = lua["scene"];
    // load the sprites
    sol::table sprites = scene["sprites"];
    load_sprites(renderer, sprites, asset_manager);

    // load the animations
    sol::table animations = scene["animations"];
    load_animations(animations, animation_manager);

    // load the sounds
    sol::table sounds = scene["sounds"];
    load_sounds(sounds, audio_manager);
    // load the music
    sol::table music = scene["music"];
    load_music(music, audio_manager);
    // load the fonts
    sol::table fonts = scene["fonts"];
    load_fonts(fonts, asset_manager);
    // load the buttons
    sol::table buttons = scene["buttons"];
    load_buttons(buttons, controller_manager);
    // load the keys
    sol::table keys = scene["keys"];
    load_keys_actions(keys, controller_manager);
    // load the map
    std::cout <<"before loading map" << std::endl;
    sol::table map = scene["maps"];
    LoadMap(map, registry);
    std::cout <<"after loading map" << std::endl;

    // load the entities
    std::cout <<"before loading entities" << std::endl;
    sol::table entities = scene["entities"];
    load_entities(lua, entities, registry);
    std::cout <<"after loading entities" << std::endl;
}

void SceneLoader::load_sprites(SDL_Renderer* renderer, const sol::table& sprites, std::unique_ptr<AssetsManager>& asset_manager) {
    int index = 0;

    while(true) {
        sol::optional<sol::table> has_sprite = sprites[index];
        if(has_sprite == sol::nullopt) {
            break;
        }

        sol::table sprite = sprites[index];
        std::string asset_id = sprite["asset_id"];
        std::string file_path = sprite["file_path"];

        asset_manager->add_texture(renderer, asset_id, file_path);

        index++;
    }
}


void SceneLoader::load_sounds(const sol::table& sounds, std::unique_ptr<AudioManager>& audio_manager) {
    int index = 0;

    while(true) {
        sol::optional<sol::table> has_sounds = sounds[index];
        if(has_sounds == sol::nullopt) {
            break;
        }

        sol::table sound = sounds[index];
        std::string sound_id = sound["sound_id"];
        std::string file_path = sound["file_path"];

        audio_manager->add_sound_effect(sound_id, file_path);

        index++;
    }
}

void SceneLoader::load_music(const sol::table& music, std::unique_ptr<AudioManager>& audio_manager) {
    int index = 0;

    // loop through all the music
    while(true) {
        sol::optional<sol::table> has_music = music[index];
        if(has_music == sol::nullopt) {
            break;
        }
        sol::table selected_music = music[index];
        std::string music_id = selected_music["music_id"];
        std::string file_path = selected_music["file_path"];

        audio_manager->add_music(music_id, file_path);

        index++;
    }
}

void SceneLoader::load_keys_actions(const sol::table& keys, std::unique_ptr<ControllerManager>& controller_manager) {
    int index = 0;
    while(true) {
        sol::optional<sol::table> has_key = keys[index];
        if(has_key == sol::nullopt) {
            break;
        }

        sol::table key = keys[index];
        std::string name = key["name"];
        int key_code = key["key"];

        controller_manager->add_key(name, key_code);

        index++;
    }
}

void SceneLoader::load_entities(sol::state& lua, const sol::table& entities, std::unique_ptr<Registry>& registry) {
    int index = 0;

    while(true) {
        std::cout << "loading entity" << std::endl;
        sol::optional<sol::table> has_entity = entities[index];

        if(has_entity == sol::nullopt) {
            break;
        }

        sol::table entity = entities[index];
        Entity new_entity = registry->create_entity();

        // to be sure, remove_component is called for all components
        new_entity.remove_component<TransformComponent>();
        new_entity.remove_component<RigidBodyComponent>();
        new_entity.remove_component<SpriteComponent>();
        new_entity.remove_component<CircleColliderComponent>();
        new_entity.remove_component<AnimationComponent>();
        new_entity.remove_component<ScriptComponent>();
        new_entity.remove_component<TextComponent>();
        new_entity.remove_component<ClickableComponent>();
        new_entity.remove_component<CameraFollowComponent>();
        new_entity.remove_component<BoxColliderComponent>();
        new_entity.remove_component<TagComponent>();
        

        sol::optional<sol::table> has_components = entity["components"];

        if(has_components != sol::nullopt) {
            sol::table components = entity["components"];

            // Animation component
            sol::optional<sol::table> has_animation = components["animation"];
            if(has_animation != sol::nullopt) {
                sol::table animation = components["animation"];
                
                // add explicit conversions
                int num_frames = animation["num_frames"].get<int>();
                float frame_speed_rate = static_cast<float>(animation["frame_speed_rate"].get<double>());
                bool is_loop = animation["is_loop"].get<bool>();
                
                new_entity.add_component<AnimationComponent>(
                    num_frames,
                    frame_speed_rate,
                    is_loop
                );
            }

            // Box collider component
            sol::optional<sol::table> has_box_collider = components["box_collider"];
            if(has_box_collider != sol::nullopt) {
                new_entity.add_component<BoxColliderComponent>(
                    components["box_collider"]["width"],
                    components["box_collider"]["height"],
                    glm::vec2(components["box_collider"]["offset"]["x"], components["box_collider"]["offset"]["y"])
                );
            }

            // camera follow component
            sol::optional<sol::table> has_camera_follow_component = components["camera_follow"];
            if(has_camera_follow_component != sol::nullopt) {
                new_entity.add_component<CameraFollowComponent>(); // has not parameters
            }

            // Circle collider component
            sol::optional<sol::table> has_circle_collider = components["circular_collider"];

            if(has_circle_collider != sol::nullopt) {
                new_entity.add_component<CircleColliderComponent>(
                    components["circular_collider"]["radius"],
                    components["circular_collider"]["width"],
                    components["circular_collider"]["height"]
                );
            }

            // Rigid body component
            sol::optional<sol::table> has_rigid_body = components["rigid_body"];
            if(has_rigid_body != sol::nullopt) {
                new_entity.add_component<RigidBodyComponent>(
                    components["rigid_body"]["is_dynamic"],
                    components["rigid_body"]["is_solid"],
                    components["rigid_body"]["mass"]
                );
            }

            // Clickable component
            sol::optional<sol::table> has_clickable = components["clickable"];
            if(has_clickable != sol::nullopt) {
                new_entity.add_component<ClickableComponent>();
            }

            // script component
            sol::optional<sol::table> has_script = components["script"];
            if( has_script != sol::nullopt) {
                lua["on_collision"] = sol::nil;
                lua["on_click"] = sol::nil;
                lua["update"] = sol::nil;
                lua["on_init"] = sol::nil;

                std::string path = components["script"]["path"];

                lua.script_file(path);

                sol::optional<sol::function> has_on_collision = lua["on_collision"];
                sol::function on_collision = sol::nil;
                if(has_on_collision != sol::nullopt) {
                    on_collision = lua["on_collision"];
                }

                sol::optional<sol::function> has_on_click = lua["on_click"];
                sol::function on_click = sol::nil;
                if(has_on_click != sol::nullopt) {
                    on_click = lua["on_click"];
                }

                sol::optional<sol::function> has_update = lua["update"];
                sol::function update = sol::nil;
                if(has_update != sol::nullopt) {
                    update = lua["update"];
                }

                sol::optional<sol::function> has_on_init = lua["on_init"];
                sol::function on_init = sol::nil;
                if(has_on_init != sol::nullopt) {
                    on_init = lua["on_init"];
                }

                new_entity.add_component<ScriptComponent>(on_collision, update, on_click, on_init);
            }

            // Sprite component
            sol::optional<sol::table> has_sprite = components["sprite"];
            if(has_sprite != sol::nullopt) {
                new_entity.add_component<SpriteComponent>(
                    components["sprite"]["asset_id"],
                    components["sprite"]["width"],
                    components["sprite"]["height"],
                    components["sprite"]["src_rect"]["x"],
                    components["sprite"]["src_rect"]["y"]
                );
            }

            // Text component
            sol::optional<sol::table> has_text = components["text"];
            if(has_text != sol::nullopt) {
                new_entity.add_component<TextComponent>(
                    components["text"]["text"],
                    components["text"]["font_id"],
                    components["text"]["r"],
                    components["text"]["g"],
                    components["text"]["b"],
                    components["text"]["a"]
                );
            }

            // tag component
            sol::optional<sol::table> has_tag = components["tag"];
            if(has_tag != sol::nullopt) {
                new_entity.add_component<TagComponent>(static_cast<std::string>(components["tag"]["tag"]));
            }

             // transform component
            sol::optional<sol::table> has_transform = components["transform"];
            if(has_transform != sol::nullopt) {
                new_entity.add_component<TransformComponent>(
                    glm::vec2(
                        components["transform"]["position"]["x"],
                        components["transform"]["position"]["y"]
                    ),
                    glm::vec2(
                        components["transform"]["scale"]["x"],
                        components["transform"]["scale"]["y"]
                    ),
                    components["transform"]["rotation"]
                );
            }

            // player velocity component
            sol::optional<sol::table> has_player_velocity = components["player_velocity"];
            if(has_player_velocity != sol::nullopt) {

                // add static cast to avoid warning
                new_entity.add_component<PlayerVelocity>(
                    static_cast<int>(components["player_velocity"]["player_velocity"])
                );
            }

            // player score component
            sol::optional<sol::table> has_player_score = components["player_score"];
            if(has_player_score != sol::nullopt) {
                new_entity.add_component<PlayerScore>(
                    static_cast<int>(components["player_score"]["player_score"])
                );
            }
        }

        index++;
    }
}

void SceneLoader::load_fonts(const sol::table& fonts, std::unique_ptr<AssetsManager>& asset_manager) {
    int index = 0;
    while(true){
        sol::optional<sol::table> has_font = fonts[index];
        if(has_font == sol::nullopt) {
            break;
        }

        sol::table font = fonts[index];
        std::string font_id = font["font_id"];
        std::string file_path = font["file_path"];
        int font_size = font["font_size"];

        asset_manager->add_font(font_id, file_path, font_size);

        index++;
    }
}

void SceneLoader::load_buttons(const sol::table& buttons, std::unique_ptr<ControllerManager>& controller_manager) {
    int index = 0;
    while(true) {
        sol::optional<sol::table> has_button = buttons[index];
        if(has_button == sol::nullopt) {
            break;
        }

        sol::table button = buttons[index];

        std::string button_name = button["name"];
        int button_code = button["button_code"];

        controller_manager->add_mouse_button(button_name, button_code);

        index++;
    }
}

void SceneLoader::LoadLayer(std::unique_ptr<Registry> &registry, tinyxml2::XMLElement *layerElement,
                            int tWidth, int tHeight, int mWidth, const std::string &tileSet, int columns)
{
  tinyxml2::XMLElement *xmlData = layerElement->FirstChildElement("data");
  const char *data = xmlData->GetText();

  std::stringstream tmpNumber;
  int pos = 0;
  int tileNumber = 0;

  while (true)
  {
    if (data[pos] == '\0')
    {
      break;
    }
    if (isdigit(data[pos]))
    {
      tmpNumber << data[pos];
    }
    else if (!isdigit(data[pos]) && tmpNumber.str().length() != 0)
    {
      int tileId = std::stoi(tmpNumber.str());
      if (tileId > 0)
      {
        Entity tile = registry->create_entity();
        tile.add_component<TransformComponent>(
            glm::vec2((tileNumber % mWidth) * tWidth,
                      (tileNumber / mWidth) * tHeight) //
        );
        tile.add_component<SpriteComponent>(
            tileSet,
            tWidth,
            tHeight,
            ((tileId - 1) % columns) * tWidth,
            ((tileId - 1) / columns) * tHeight //
        );
      }

      tileNumber++;
      tmpNumber.str("");
    }
    pos++;
  }
}


void SceneLoader::LoadMap(const sol::table map, std::unique_ptr<Registry> &registry)
{
  sol::optional<int> hasWidth = map["width"];
  if (hasWidth != sol::nullopt)
  {
    Game::get_instance().map_width = map["width"];
  }

  sol::optional<int> hasHeight = map["height"];
  if (hasHeight != sol::nullopt)
  {
    Game::get_instance().map_height = map["height"];
  }

  sol::optional<std::string> hasPath = map["map_path"];
  if (hasPath != sol::nullopt)
  {
    std::string path = map["map_path"];

    // Se carga el documento xml que contiene la información del mapa
    tinyxml2::XMLDocument xmlmap;

    if (xmlmap.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS)
    {
      std::cerr << "[SceneLoader] Error loading map XML file" << std::endl;
      return;
    }

    // Extraer la raiz del documento xml
    tinyxml2::XMLElement *root = xmlmap.RootElement();

    // Extraer las dimensiones del mapa
    int tWidth, tHeight, mWidth, mHeight;
    root->QueryIntAttribute("tilewidth", &tWidth);
    root->QueryIntAttribute("tileheight", &tHeight);
    root->QueryIntAttribute("width", &mWidth);
    root->QueryIntAttribute("height", &mHeight);

    // Calcular dimensiones del mapa
    Game::get_instance().map_width = tWidth * mWidth;
    Game::get_instance().map_height = tHeight * mHeight;

    // Se carga el documento con la información de los tiles
    std::string tilePath = map["tile_path"];
    std::string tileName = map["tile_name"];

    tinyxml2::XMLDocument xmltileset;
    xmltileset.LoadFile(tilePath.c_str());

    tinyxml2::XMLElement *xmlTilesetRoot = xmltileset.RootElement();

    // Extraer cantidad de columnas
    int columns;
    xmlTilesetRoot->QueryIntAttribute("columns", &columns);

    // Se obtiene la lista de layers
    tinyxml2::XMLElement *layerElement = root->FirstChildElement("layer");

    while (layerElement)
    {
        std::cout << "loading layer" << std::endl;
      LoadLayer(registry, layerElement, tWidth, tHeight, mWidth, tileName, columns);
      layerElement = layerElement->NextSiblingElement("layer");
    }

    // Se obtiene la lista de object groups
    tinyxml2::XMLElement *objectGroup = root->FirstChildElement("objectgroup");

    while (objectGroup)
    {
      const char *objectGroupName;
      std::string name;
      objectGroup->QueryStringAttribute("name", &objectGroupName);
      name = objectGroupName;

      if (name.compare("colliders") == 0)
      {
        LoadColliders(registry, objectGroup);
      }

      objectGroup = objectGroup->NextSiblingElement("objectgroup");
    }
  }
}

void SceneLoader::LoadColliders(std::unique_ptr<Registry> &registry, tinyxml2::XMLElement *objectGroup)
{
  tinyxml2::XMLElement *object = objectGroup->FirstChildElement("object");

  while (object != nullptr)
  {
    // Declarar variables
    const char *name;
    std::string tag;
    int x, y, w, h;

    // Extraer atributos
    object->QueryStringAttribute("name", &name);
    tag = name;

    // Extraer posición
    object->QueryIntAttribute("x", &x);
    object->QueryIntAttribute("y", &y);

    // Extraer dimensiones
    object->QueryIntAttribute("width", &w);
    object->QueryIntAttribute("height", &h);

    // Crear entidad
    Entity collider = registry->create_entity();
    collider.add_component<TagComponent>(tag);
    collider.add_component<TransformComponent>(
        glm::vec2(x, y));
    collider.add_component<BoxColliderComponent>(w, h);
    collider.add_component<RigidBodyComponent>(false, true, 9999999999.0f);

    object = object->NextSiblingElement("object");
  }
}

void SceneLoader::load_animations(const sol::table& animations, std::unique_ptr<AnimationManager>& animation_manager) {
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasAnimation = animations[index];
        if (hasAnimation == sol::nullopt) {
            break;
        }
        sol::table animation = animations[index];

        std::string animationId = animation["animation_id"];
        std::string textureId = animation["texture_id"];
        int width = animation["w"];
        int height = animation["h"];
        int numFrames = animation["num_frames"];
        int speedRate = animation["speed_rate"];
        bool isLoop = animation["is_loop"];

        animation_manager->add_animation(animationId, textureId, width, height
            , numFrames, speedRate, isLoop);
        
        index++;
    }
}
scene = {
    -- sprites table
    sprites = {
        [0] = 
        {asset_id = "background", file_path = "./assets/images/background_0.png"},
    },

    -- animations table
    animations = {},

    -- sounds table
    sounds = {
        [0] =
        {sound_id = "other_sound",file_path ="./assets/sounds/lazer.mp3"},
    },

    -- music table
    music = {
        [0] =
        {music_id = "menu_music",file_path ="./assets/sounds/GAL_v1.mp3"},
    },

    -- font table
    fonts = {
        [0] = 
        {font_id = "font_0", file_path = "./assets/fonts/highway_gothic.ttf", font_size = 32},
        {font_id = "arcade_classic_font", file_path = "./assets/fonts/prstart.ttf", font_size = 32},
        {font_id = "arcade_classic_large", file_path = "./assets/fonts/prstart.ttf", font_size = 48},
    },
    
    -- actions and keys table
    keys = {
        [0] =
        {name = "up", key = 119}, -- SDLK_w
        {name = "left", key = 97}, -- SDLK_a
        {name = "down", key = 115}, -- SDLK_s
        {name = "right", key = 100}, -- SDLK_d
    },

    -- actions and mouse button table
    buttons = {
        [0] =
        {name = "mouse_left_button", button_code = 1}, -- SDL_BUTTON_LEFT
    },

    -- map table
    maps = {
        -- tileset_path = "../maps/terrain.tsx",
        -- tileset_name = "tileset_0",
        -- path_to_tmx = "../maps/level_01.tmx",
    },

    -- entities table
    entities = {
        [0] =
        -- Background
        {
            components = {
                sprite = {
                    asset_id = "background",
                    width = 3000,
                    height = 3000,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = { x = 0, y = 0},
                    scale = { x = 1.0, y = 1.0},
                    rotation = 0.0
                },
            }
        },
        -- title
        {
            components = {
                text = {
                    text = "Another cool game",
                    font_id = "arcade_classic_large",
                    r = 255, g = 215, b = 0, a = 255  -- Golden color
                },
                transform = {
                    position = { x = 100, y = 50},
                    scale = { x = 1.5, y = 1.5},
                    rotation = 0.0
                },
            }
        },
        -- level 01
        {
            components = {
                clickable = {
                },
                text = {
                    text = "Level  01: Entering the dungeon",
                    font_id = "arcade_classic_font",
                    r = 255, g = 255, b = 255, a = 255  -- White color
                },
                transform = {
                    position = { x = 100, y = 250},
                    scale = { x = 1.2, y = 1.2},
                    rotation = 0.0
                },
                script = {
                    path = "./assets/scripts/goto_level_01.lua",
                },
            },
        },
        -- level 02
        {
            components = {
                clickable = {
                },
                text = {
                    text = "Level  02: Monsters, I guess",
                    font_id = "arcade_classic_font",
                    r = 200, g = 200, b = 200, a = 255  -- Light gray color
                },
                transform = {
                    position = { x = 100, y = 350},
                    scale = { x = 1.2, y = 1.2},
                    rotation = 0.0
                },
            },
        },
        -- level 03
        {
            components = {
                clickable = {
                },
                text = {
                    text = "Level  03: Dinosaur (definitely not a dragon)",
                    font_id = "arcade_classic_font",
                    r = 150, g = 150, b = 150, a = 255  -- Darker gray color
                },
                transform = {
                    position = { x = 100, y = 450},
                    scale = { x = 1.2, y = 1.2},
                    rotation = 0.0
                },
            },
        },
    }

    -- music and sound effect table
}
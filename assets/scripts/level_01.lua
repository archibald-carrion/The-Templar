scene = {
    -- sprites table 
    sprites = {
        [0] =
            {asset_id = "knight_idle", file_path = "./assets/images/knight_idle.png"},
            {asset_id = "knight_jump", file_path = "./assets/images/knight_jump.png"},
            {asset_id = "knight_fall", file_path = "./assets/images/knight_fall.png"},
            {asset_id = "knight_run", file_path = "./assets/images/knight_run.png"},
            {asset_id = "knight_attack", file_path = "./assets/images/knight_attack.png"},
            {asset_id = "terrain", file_path = "./assets/images/dungeon_tileset.png"},
    },
    
    animations = {
        [0] =
            {animation_id = "player_knight_idle", texture_id = "knight_idle", w = 32, h = 38, num_frames = 10, speed_rate = 15, is_loop = true},
            {animation_id = "player_knight_jump", texture_id = "knight_jump", w = 32, h = 38, num_frames = 03, speed_rate = 01, is_loop = true},
            {animation_id = "player_knight_fall", texture_id = "knight_fall", w = 32, h = 38, num_frames = 03, speed_rate = 01, is_loop = true},
            {animation_id = "player_knight_run", texture_id = "knight_run", w = 32, h = 38, num_frames = 10, speed_rate = 15, is_loop = true},
            {animation_id = "player_knight_attack", texture_id = "knight_attack", w = 32, h = 38, num_frames = 4, speed_rate = 15, is_loop = false},
    },

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
        [0] = {name = "up", key = 119},
        {name = "left", key = 97},
        {name = "down", key = 115},
        {name = "right", key = 100}, 
        {name = "jump", key = 32},
        {name = "attack", key = 101}, -- e
    },

    -- actions and mouse button table
    buttons = {
        [0] =
        {name = "mouse_left_button", button_code = 1}, -- SDL_BUTTON_LEFT
    },

    -- map table
    maps = {
        width = 3000,
        height = 3000,
        map_path = "./assets/maps/first_level.tmx",
        tile_path = "./assets/maps/dungeon_tileset.tsx",
        tile_name = "terrain",
    },

    -- entities table
    entities = {
        [0] =

        -- player
        {
            components = {
                animation = {
                    num_frames = 11,
                    frame_speed_rate = 5,
                    is_loop = true
                },
                camera_follow = {},
                tag = {
                    tag = "player",
                },
                box_collider = {
                    width = 32*2,
                    height = 38*2,
                    offset = {x = 0, y= 0},
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 10,
                },
                script = {
                    path = "./assets/scripts/player_knight.lua"
                },
                sprite = {
                    asset_id = "knight_idle",
                    width = 32,
                    height = 38,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = { x = 100, y = 100},
                    scale = { x = 2.0, y = 2.0},
                    rotation = 0.0
                },
                player_velocity = {
                    player_velocity = 150
                }
            }
        },

        -- door second level
        {
            components = {
                tag = {
                    tag = "door",
                },
                box_collider = {
                    width = 64,
                    height = 100,
                    offset = {x = 0, y= 0},
                },
                rigid_body = {
                    is_dynamic = false,
                    is_solid = false,
                    mass = 10,
                },
                script = {
                    path = "./assets/scripts/goto_level_02_door.lua"
                },
                transform = {
                    position = { x = 196*2*16, y = 30*2*16},
                    scale = { x = 1.0, y = 1.0},
                    rotation = 0.0
                },
            }
        },

    }
}
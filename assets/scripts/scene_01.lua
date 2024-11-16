scene = {
    -- sprites table 
    sprites = {
        [0] =
            {asset_id = "frog_idle", file_path = "./assets/images/frog_idle.png"},
            {asset_id = "frog_jump", file_path = "./assets/images/frog_jump.png"},
            {asset_id = "frog_fall", file_path = "./assets/images/frog_fall.png"},
            {asset_id = "frog_run", file_path = "./assets/images/frog_run.png"},
            {asset_id = "terrain", file_path = "./assets/images/terrain.png"},
    },
    
    animations = {
        [0] =
            {animation_id = "player_frog_idle", texture_id = "frog_idle", w = 32, h = 32, num_frames = 11, speed_rate = 15, is_loop = true},
            {animation_id = "player_frog_jump", texture_id = "frog_jump", w = 32, h = 32, num_frames = 01, speed_rate = 01, is_loop = true},
            {animation_id = "player_frog_fall", texture_id = "frog_fall", w = 32, h = 32, num_frames = 01, speed_rate = 01, is_loop = true},
            {animation_id = "player_frog_run", texture_id = "frog_run", w = 32, h = 32, num_frames = 12, speed_rate = 15, is_loop = true},
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
        map_path = "./assets/maps/level_01.tmx",
        tile_path = "./assets/maps/terrain.tsx",
        tile_name = "terrain",
    },

    -- entities table
    entities = {
        [0] =
        -- -- Background
        -- {
        --     components = {
        --         sprite = {
        --             asset_id = "background",
        --             width = 3000,
        --             height = 3000,
        --             src_rect = {x = 0, y = 0},
        --         },
        --         transform = {
        --             position = { x = 0, y = 0},
        --             scale = { x = 1.0, y = 1.0},
        --             rotation = 0.0
        --         },
        --     }
        -- },

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
                    width = 32,
                    height = 32,
                    offset = {x = 0, y= 0},
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 10,
                },
                script = {
                    path = "./assets/scripts/player_frog.lua"
                },
                sprite = {
                    asset_id = "frog_idle",
                    width = 32,
                    height = 32,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = { x = 100, y = 100},
                    scale = { x = 1.0, y =1.0},
                    rotation = 0.0
                },
                player_velocity = {
                    player_velocity = 150
                }
            }
        },
    }
}
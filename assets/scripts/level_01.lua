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
        {asset_id = "frost_t_idle", file_path = "./assets/images/frost_t_idle.png"},
        {asset_id = "frost_t_walk", file_path = "./assets/images/frost_t_walk.png"},
        {asset_id = "frost_t_attack", file_path = "./assets/images/frost_t_attack.png"},
        {asset_id = "shadow_idle", file_path = "./assets/images/shadow_idle.png"},
        {asset_id = "shadow_walk", file_path = "./assets/images/shadow_walk.png"},
        {asset_id = "shadow_attack", file_path = "./assets/images/shadow_attack.png"},
        {asset_id= "bat", file_path = "./assets/images/bat.png"},
        {asset_id= "fireball", file_path = "./assets/images/fireball.png"},
    },
    
    animations = {
        [0] =
        {animation_id = "player_knight_idle", texture_id = "knight_idle", w = 32, h = 38, num_frames = 10, speed_rate = 15, is_loop = true},
        {animation_id = "player_knight_jump", texture_id = "knight_jump", w = 32, h = 38, num_frames = 03, speed_rate = 01, is_loop = true},
        {animation_id = "player_knight_fall", texture_id = "knight_fall", w = 32, h = 38, num_frames = 03, speed_rate = 01, is_loop = true},
        {animation_id = "player_knight_run", texture_id = "knight_run", w = 32, h = 38, num_frames = 10, speed_rate = 15, is_loop = true},
        {animation_id = "player_knight_attack", texture_id = "knight_attack", w = 93, h = 38, num_frames = 6, speed_rate = 15, is_loop = false},
        {animation_id = "enemy1_idle", texture_id = "frost_t_idle", w = 52, h = 58, num_frames = 6, speed_rate = 15, is_loop = true},
        {animation_id = "enemy1_walk", texture_id = "frost_t_walk", w = 62, h = 58, num_frames = 10, speed_rate = 12, is_loop = true},
        {animation_id = "enemy1_attack", texture_id = "frost_t_attack", w = 124, h = 58, num_frames = 14, speed_rate = 12, is_loop = false},
        {animation_id = "enemy2_idle", texture_id = "shadow_idle", w = 24, h = 23, num_frames = 8, speed_rate = 15, is_loop = true},
        {animation_id = "enemy2_walk", texture_id = "shadow_walk", w = 24, h = 23, num_frames = 8, speed_rate = 12, is_loop = true},
        {animation_id = "enemy2_attack", texture_id = "shadow_attack", w = 64, h = 23, num_frames = 13, speed_rate = 16, is_loop = false},
    },

    damage_colliders = {
        [0] =
        { class = "player" },
        { class = "enemy"}
    },

    -- sounds table
    sounds = {
        [0] =
        {sound_id = "other_sound",file_path ="./assets/sounds/lazer.mp3"},
    },

    -- music table
    music = {
        [0] =
        {music_id = "level_01_music",file_path ="./assets/sounds/Grimoire_v2.mp3"},
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
        {name = "shoot", key = 113}, -- q use for fireball
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

    stats = {
        [0] =
        { tag = "player", health = 5, points = 0, damage = 0 },
        { tag = "sword", health = 5, points = 0, damage = 1 },
        { tag = "enemy_1", health = 2, points = 1, damage = 1},
        { tag = "enemy1_attack", health = 0, points = 0, damage = 1},
        { tag = "enemy_2", health = 1, points = 1, damage = 1},
        { tag = "enemy2_attack", health = 0, points = 0, damage = 2},
        { tag = "enemy_3", health = 1, points = 1, damage = 2},
        { tag = "boss", health = 20, points = 10, damage = 1},
        { tag = "boss_attack_p1", health = 0, points = 0, damage = 1},
    },

    -- entities table
    entities = {
        [0] =
        -- music player
        {
            components = {
                script = {
                    path = "./assets/scripts/music_level_01.lua"
                },
            }
        },

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
                    class = "player"
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
                    position = { x = 100, y = 1650},
                    scale = { x = 2.0, y = 2.0},
                    rotation = 0.0
                },
                player_velocity = {
                    player_velocity = 150
                },
                cooldowns = {
                    [0] =
                    { name = "global", seconds = 0.4},
                    { name = "attack", seconds = 0.6}
                }
            }
        },

        -- door second level
        {
            components = {
                tag = {
                    tag = "door",
                    class = "map"
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
                    position = { x = 3008*2, y = 160*2},
                    scale = { x = 1.0, y = 1.0},
                    rotation = 0.0
                },
            }
        },

    }
}
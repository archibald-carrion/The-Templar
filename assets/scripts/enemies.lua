enemies = {
    enemy_1 = {
        components = {
            sprite = {
                asset_id = "frost_t_idle",
                width = 62,
                height = 58,
                src_rect = {x = 0, y = 0},
            },
            animation = {
                num_frames = 6,
                frame_speed_rate = 10,
                is_loop = true
            },
            rigid_body = {
                is_dynamic = true,
                is_solid = true,
                mass = 10,
                velocity = { x = 50, y = 0 }
            },
            box_collider = {
                width = 40*2,
                height = 58*2,
                offset = { x = 0, y= 0 },
            },
            script = {
                path = "./assets/scripts/enemy1.lua"
            },
            cooldowns = {
                [0] =
                { name = "global", seconds = 0.4 },
                { name = "melee", seconds = 0.6 }
            },
            attacks = {
                [0] = { name = "melee", awareness_x = 10, awareness_y = 0 },
            }
        }
    },

    enemy_2 = {
        components = {
            sprite = {
                asset_id = "shadow_idle",
                width = 24,
                height = 22,
                src_rect = {x = 0, y = 0},
            },
            animation = {
                num_frames = 8,
                frame_speed_rate = 10,
                is_loop = true
            },
            rigid_body = {
                is_dynamic = true,
                is_solid = true,
                mass = 10,
                velocity = { x = 80, y = 0 }
            },
            box_collider = {
                width = 24*2,
                height = 23*4,
                offset = { x = 0, y= 0 },
            },
            script = {
                path = "./assets/scripts/enemy2.lua"
            },
            transform = {
                position = { x = 0, y = 0},
                scale = { x = 4.0, y = 4.0},
                rotation = 0.0
            },
            cooldowns = {
                [0] =
                { name = "global", seconds = 1 },
                { name = "melee", seconds = 1 }
            },
            attacks = {
                [0] = { name = "melee", awareness_x = 50, awareness_y = 0 },
            }
        }
    },

    enemy_3 = {
        components = {
            sprite = {
                asset_id = "bat",
                width = 120,
                height = 102,
                src_rect = {x = 0, y = 0},
            },
            animation = {
                num_frames = 4,
                frame_speed_rate = 10,
                is_loop = true
            },
            rigid_body = {
                is_dynamic = true,
                is_solid = false,
                mass = 0,
                velocity = { x = 0, y = 100}
            },
            box_collider = {
                width = 60,
                height = 50,
                offset = { x = 0, y= 0 },
            },
            script = {
                path = "./assets/scripts/enemy3.lua"
            },
            transform = {
                position = { x = 0, y = 0},
                scale = { x = 0.6, y = 0.6},
                rotation = 0.0
            },
            cooldowns = {
                [0] =
                { name = "global", seconds = 1 },
            },
        }
    },
    boss = {
        components = {
            sprite = {
                asset_id = "boss_idle",
                width = 80,
                height = 40,
                src_rect = {x = 0, y = 0},
            },
            animation = {
                num_frames = 16,
                frame_speed_rate = 20,
                is_loop = true
            },
            rigid_body = {
                is_dynamic = true,
                is_solid = true,
                mass = 10,
                velocity = { x = 10, y = 0 }
            },
            box_collider = {
                width = 40*4,
                height = 40*8,
                offset = { x = 0, y= 0 },
            },
            script = {
                path = "./assets/scripts/boss.lua"
            },
            transform = {
                position = { x = 0, y = 0},
                scale = { x = 8.0, y = 8.0},
                rotation = 0.0
            },
            cooldowns = {
                [0] =
                { name = "global", seconds = 1 },
                { name = "none", seconds = 0.5 },
                { name = "melee1", seconds = 0.5 },
                { name = "melee2", seconds = 3 }
            },
            attacks = {
                [0] =
                { name = "none", awareness_x = 150, awareness_y = 0 },
                { name = "melee1", awareness_x = 500, awareness_y = 0 },
                { name = "none", awareness_x = 150, awareness_y = 0 },
                { name = "melee2", awareness_x = 500, awareness_y = 0 },
            }
        }
    },
}
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
                velocity = { x = 1, y = 0 }
            },
            box_collider = {
                width = 40*2,
                height = 58*2,
                offset = { x = 0, y= 0 },
            },
            script = {
                path = "./assets/scripts/enemy1.lua"
            },
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
                scale = { x = 1.0, y = 1.0},
                rotation = 0.0
            },
        }
    }

}
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
                velocity = { x = 70, y = 0 }
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

        }
    }

}
enemies = {
    enemy_1 = {
        components = {
            sprite = {
                asset_id = "frost_t_idle",
                width = 54,
                height = 58,
                src_rect = {x = 0, y = 0},
            },
            animation = {
                num_frames = 6,
                frame_speed_rate = 5,
                is_loop = true
            },
            rigid_body = {
                is_dynamic = true,
                is_solid = true,
                mass = 10,
                velocity = { x = 50, y = 0 }
            },
            box_collider = {
                width = 52*2,
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

        }
    },

    enemy_3 = {
        components = {

        }
    }

}
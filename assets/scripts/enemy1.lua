enemy_states = {
    idle = 1,
    run = 2,
    attack = 3,
    damaged = 4,
    dies = 5,
}

local function enemy_update_animation_state()
    local x_vel, y_vel = get_velocity(this)
    local enemy_state = get_state(this)

    if -0.001 < x_vel and x_vel < 0.001 then
        if enemy_state ~= enemy_states["idle"] then
            enemy_state = enemy_states["idle"]
            change_animation(this, "enemy1_idle")
        end
    end

    -- enemy moving right
    if x_vel >= 0.001 then
        flip_sprite(this, false)
        if enemy_state ~= enemy_states["run"] then
            enemy_state = enemy_states["run"]
            change_animation(this, "enemy1_walk")
        end
    end

    -- enemy moving left
    if x_vel <= -0.001 then
        flip_sprite(this, true)
        if enemy_state ~= enemy_states["run"] then
            enemy_state = enemy_states["run"]
            change_animation(this, "enemy1_walk")
        end
    end

    set_state(this, enemy_state)
end

function update()
    enemy_update_animation_state()
end

function on_collision(other)
    this_tag = get_tag(this)
    other_tag = get_tag(other)

    if other_tag == "wall" or other_tag == "floor" or other_tag == "trap" then
        this_x, this_y = get_position(this)
        this_width, this_height = get_size(this)
        other_x, other_y = get_position(other)
        other_width, other_height = get_size(other)
        this_vel_x, this_vel_y = get_velocity(this)

        if this_vel_x == 0 then
            this_vel_x, this_vel_y = get_buffered_velocity(this)
        end

        if left_collision(this, other) then
            new_vel = this_vel_x * -1
            set_velocity(this, new_vel, this_vel_y)
        elseif right_collision(this, other) then
            new_vel = this_vel_x * -1
            set_velocity(this, new_vel, this_vel_y)
        end
    end
end

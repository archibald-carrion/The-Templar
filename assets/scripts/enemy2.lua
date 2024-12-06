enemy_states = {
    idle = 1,
    run = 2,
    attack = 3,
    damaged = 4,
    dies = 5,
}

local function enemy_update_animation_state(state)
    local x_vel, y_vel = get_velocity(this)

    if -0.001 < x_vel and x_vel < 0.001 then
        if state ~= enemy_states["idle"] then
            state = enemy_states["idle"]
            change_animation(this, "enemy2_idle")
        end
    end

    -- enemy moving right
    if x_vel >= 0.001 then
        flip_sprite(this, false)
        if state ~= enemy_states["run"] then
            state = enemy_states["run"]
            change_animation(this, "enemy2_walk")
        end
    end

    -- enemy moving left
    if x_vel <= -0.001 then
        flip_sprite(this, true)
        if state ~= enemy_states["run"] then
            state = enemy_states["run"]
            change_animation(this, "enemy2_walk")
        end
    end

    set_next_state(this, state)
    set_state(this, state)
end

function update()
    local enemy_state = get_state(this)
    local next_state = get_next_state(this)
    local changed = false

    if enemy_state ~= next_state then
        enemy_state = next_state
        changed = true
    end

    if enemy_state == enemy_states["attack"] then
        if changed then
            change_animation(this, "enemy2_attack")
            set_state(this, enemy_state)
        end
        if get_animation_frame(this) ~= 12 then
            return
        end
    end

    enemy_update_animation_state(enemy_state)
end

function on_collision(other)
    local other_tag = get_tag(other)

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

    if other_tag == "enemy_collider" then
        this_vel_x, this_vel_y = get_velocity(this)
        set_velocity(this, this_vel_x * -1, this_vel_y)
    end
end

function on_damage(other)
    other_class = get_class(other)
    this_class = get_class(this)

    if this_class == other_class then
        return
    end

    other_tag = get_tag(other)
    if other_tag ~= "sword" and other_tag ~= "fireball" then
        return
    end

    damage = get_damage(other)
    health = get_health(this)
    health = health - damage

    set_health(this, health)

    if health <= 0 then
        owner = get_father(other)
        points_earned = get_points(this)
        points = get_points(owner)
        points = points + points_earned
        set_points(owner, points)

        kill_entity(this)
    end

    kill_entity(other)
end

function on_perform(attackName, looking_right)
    local enemy_state = enemy_states["attack"]
    movement = 200
    position = -30

    if looking_right then
        flip_sprite(this, false)
    else
        movement = -1 * movement
        position = -1 * position
        flip_sprite(this, true)
    end

    set_next_state(this, enemy_state)

    create_projectile(this, "enemy1_attack", position, 30, 0, movement, 0, 100, 40, 0.7, true)
end
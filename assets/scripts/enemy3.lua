-- enemy_states = {
--     idle = 1,
--     run = 2,
--     attack = 3,
--     damaged = 4,
--     dies = 5,
-- }

-- local function enemy_update_animation_state()
--     local x_vel, y_vel = get_velocity(this)

--     local state = get_state(this)

--     if -0.001 < x_vel and x_vel < 0.001 then
--         if state ~= enemy_states["idle"] then
--             state = enemy_states["idle"]
--             change_animation(this, "enemy2_idle")
--         end
--     end

--     -- enemy moving right
--     if x_vel >= 0.001 then
--         flip_sprite(this, false)
--         if state ~= enemy_states["run"] then
--             state = enemy_states["run"]
--             change_animation(this, "enemy2_walk")
--         end
--     end

--     -- enemy moving left
--     if x_vel <= -0.001 then
--         flip_sprite(this, true)
--         if state ~= enemy_states["run"] then
--             state = enemy_states["run"]
--             change_animation(this, "enemy2_walk")
--         end
--     end

--     set_state(this, state)
-- end

-- function update()
--     enemy_update_animation_state(state)
-- end

function on_collision(other)
    local other_tag = get_tag(other)

    -- check for top_collision and bottom_collision

    if other_tag == "wall" or other_tag == "floor" or other_tag == "trap" or other_tag == "enemy_collider" then
        this_vel_x, this_vel_y = get_velocity(this)
        set_velocity(this, this_vel_x, this_vel_y* -1)
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
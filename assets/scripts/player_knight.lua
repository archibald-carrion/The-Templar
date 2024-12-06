-- Global variable

player_states = {
    idle = 1,
    run = 2,
    jump = 3,
    fall = 4,
    attack = 5,
}

player_state = player_states["idle"]
player_can_jump = false
player_speed = 3.0 * 64.0 * 1.5
player_jump_force = -3000.0 * 64.0 *1.5
player_attacking = false
player_can_use_fireball = true -- TODO: change to false and only pass to true when the player picks up the fireball powerup or kill X enemies
is_shooting = false

ult_requirement = 3

function attack()
  movement = -500
  position = 50

  if looking_right(this) then
    movement = -1 * movement
    position = -1 * position
  end

  create_projectile(this, "sword", position, 0, 0, movement, 0, 50, 80, 0.15, true)
end

function update()
    local vel_x, vel_y = get_velocity(this)
    vel_x = 0
  
    if is_action_activated("jump") then
        if player_can_jump then
        add_force(this, 0, player_jump_force)
        end
    end

    if is_action_activated("left") then
        vel_x = vel_x - player_speed
    end

    if is_action_activated("right") then
        vel_x = vel_x + player_speed
    end
    
    if is_action_activated("attack") and can_perform_action(this, "attack") then
        if not player_attacking then
            perform_action(this, "attack")
            player_attacking = true
            attack()
            change_animation(this, "player_knight_attack")
            player_state = player_states["attack"]
        end
    end
  
    set_velocity(this, vel_x, vel_y)

    if player_state == player_states["attack"] then
        if get_animation_frame(this) == 5 then
            player_attacking = false
            update_animation_state()
        end
    else
        update_animation_state()
    end

    player_can_jump = false

    -- check if the player is pressing space key to shoot
    if is_shooting  == false then
        ult_charge = get_ult(this)
        if is_action_activated("shoot") and ult_charge >= ult_requirement then
            movement = 500
            if looking_right(this) then
                movement = -movement
            end
            create_projectile_w_a(this, "fireball", 0, 0, 0, movement, 0, 88, 50, 1, false, "fire_ball", 0.5)
            is_shooting = true
        end
        if is_action_activated("shoot") then
            ult_charge = ult_charge - ult_requirement
            set_ult(ult_charge)
            ult_requirement = ult_requirement + 1
        end
    else 
        if not is_action_activated("shoot") then
            is_shooting = false
        end
    end
end

function on_collision(other)
    if get_tag(other) ~= "enemy_wall_1" or get_tag(other) ~= "enemy_wall_2" then
        if get_tag(other) == "floor" then
            local vel_x, vel_y = get_velocity(this)
            if vel_y == 0 then
            player_can_jump = true
            end
        end

        if get_tag(other) == "trap" then
            go_to_scene("game_over")
        end
    end
end

function update_animation_state()
    local x_vel, y_vel = get_velocity(this)

    -- player does not move (player idle)
    if -0.001 < x_vel and x_vel < 0.001 then
        if player_state ~= player_states["idle"] then
            player_state = player_states["idle"]
            change_animation(this, "player_knight_idle")
        end
    end

    -- player moving right
    if x_vel >= 0.001 then
        flip_sprite(this, false)
        if player_state ~= player_states["run"] then
            player_state = player_states["run"]
            change_animation(this, "player_knight_run")
        end
    end

    -- player moving left
    if x_vel <= -0.001 then
    flip_sprite(this, true)
        if player_state ~= player_states["run"] then
            player_state = player_states["run"]
            change_animation(this, "player_knight_run")
        end
    end

    -- player fall
    if y_vel >= 0.001 then
        if player_state ~= player_states["fall"] then
            player_state = player_states["fall"]
            change_animation(this, "player_knight_fall")
        end
    end

    -- player jump
    if y_vel <= -0.001 then
        if player_state ~= player_states["jump"] then
            player_state = player_states["jump"]
            change_animation(this, "player_knight_jump")
        end
    end
end

function on_damage(other)
    other_class = get_class(other)
    this_class = get_class(this)

    if this_class == other_class then
        return
    end

    other_tag = get_tag(other)

    if other_tag == "enemy_3" then
        if can_perform_action(other, "") then
            perform_action(other, "")
        else
            return
        end
    end

    damage = get_damage(other)
    health = get_health(this)
    health = health - damage

    set_health(this, health)

    result = string.find(other_tag, "attack")
    if result then
        kill_entity(other)
    end

    print("health: " .. health)

    if  health <= 0 then
        go_to_scene("game_over")
    end
end
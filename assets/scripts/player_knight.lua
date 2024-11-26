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
player_speed = 3.0 * 64.0
player_jump_force = -3000.0 * 64.0
player_attacking = false


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
    
    if is_action_activated("attack") then
      if not player_attacking then
        player_attacking = true
        change_animation(this, "player_knight_attack")
        player_state = player_states["attack"]
      end
    end
  
    set_velocity(this, vel_x, vel_y)

    -- first check if the current animation is attack
    if player_state == player_states["attack"] then
      -- if the current frame is the last frame of the attack animation
      if get_animation_frame(this) == 3 then
        player_attacking = false
        update_animation_state()
      end
    else
      update_animation_state()
    end

    player_can_jump = false
end



function on_collision(other)
    if get_tag(other) == "floor" then
        local vel_x, vel_y = get_velocity(this)
        if vel_y == 0 then
            player_can_jump = true
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
-- Global variable

player_states = {
    idle = 1,
    run = 2,
    jump = 3,
    fall = 4
}

player_state = player_states["idle"]
player_can_jump = false
player_speed = 3.0 * 64.0
player_jump_force = -3000.0 * 64.0


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
  
    set_velocity(this, vel_x, vel_y)
    update_animation_state()
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
          change_animation(this, "player_frog_idle")
      end
  end
  
  -- player moving right
  if x_vel >= 0.001 then
    flip_sprite(this, false)
      if player_state ~= player_states["run"] then
          player_state = player_states["run"]
          change_animation(this, "player_frog_run")
      end
  end
  
  -- player moving left
  if x_vel <= -0.001 then
    flip_sprite(this, true)
      if player_state ~= player_states["run"] then
          player_state = player_states["run"]
          change_animation(this, "player_frog_run")
      end
  end

  -- player fall
  if y_vel >= 0.001 then
    if player_state ~= player_states["fall"] then
        player_state = player_states["fall"]
        change_animation(this, "player_frog_fall")
    end
  end

  -- player jump
  if y_vel <= -0.001 then
    if player_state ~= player_states["jump"] then
        player_state = player_states["jump"]
        change_animation(this, "player_frog_jump")
    end
  end
end
  

-- is_shooting = false

-- function update()

--     player_velocity = get_player_velocity(this) -- need to update because player can get speed boost
--     fixed_player_velocity = math.sqrt((player_velocity*player_velocity)/2)

--     set_velocity(this, 0, 0);
--     velocity_x = 0
--     velocity_y = 0

--     -- Check if the player is pressing the wasd keys to move the player
--     if is_action_activated("up") then
--         velocity_y = velocity_y + -1
--     end
--     if is_action_activated("left") then
--         velocity_x = velocity_x + -1
--     end
--     if is_action_activated("down") then
--         velocity_y = velocity_y + 1
--     end
--     if is_action_activated("right") then
--         velocity_x = velocity_x + 1
--     end

--     -- Normalize the velocity so that the player moves at the same speed in all directions
--     if velocity_x ~=0 and velocity_y ~= 0 then
--         velocity_x = velocity_x * fixed_player_velocity
--         velocity_y = velocity_y * fixed_player_velocity
--     else
--         velocity_x = velocity_x * player_velocity
--         velocity_y = velocity_y * player_velocity
--     end

--     set_velocity(this, velocity_x, velocity_y)

    
--     -- change the ship rotation based on the direction in which it is moving
--     -- using the set_rotation(this, angle) function
--     -- Calculate and set rotation based on movement direction
--     if velocity_x ~= 0 or velocity_y ~= 0 then
--         -- Calculate angle in radians using atan2
--         local angle = math.atan2(velocity_x, -velocity_y)
--         -- Convert to degrees and adjust for SDL
--         local degrees = angle * (180 / math.pi)
        
--         -- Set the rotation
--         set_rotation(this, degrees)
--     end
    
--     location_x, location_y = get_position(this)

--     -- set the player rotation of game
--     update_player_location(location_x, location_y)

--     -- check if the player is pressing space key to shoot
--     if is_shooting  == false then
--         if is_action_activated("shoot") then
--             shoot_bullet(this)
--             is_shooting = true
--         end
--     else 
--         if not is_action_activated("shoot") then
--             is_shooting = false
--         end
--     end
    
-- end

-- function on_collision(other)
--     this_tag = get_tag(this)
--     other_tag = get_tag(other)
    
--     -- Check if the player is colliding with a wall, and if so don't allow the player to move through the wall
--     if other_tag == "wall" or other_tag == "floor" then
--         this_x, this_y = get_position(this)
--         this_width, this_height = get_size(this)
--         other_x, other_y = get_position(other)
--         other_width, other_height = get_size(other)

--         print("other size: ")
--         print(other_width)
--         print(other_height)
        
--         if top_collision(this, other) then
--             print("top collision")
--             -- Move this entity below the other entity
--             set_position(this, this_x, other_y + other_height)
        
--         elseif bottom_collision(this, other) then
--             print("bottom collision")
--             -- Move this entity above the other entity
--             set_position(this, this_x, other_y - this_height)

--         elseif right_collision(this, other) then
--             print("right collision")
--             -- Move this entity to the left of the other entity
--             set_position(this, other_x - this_width, this_y)

--         elseif left_collision(this, other) then
--             print("left collision")
--             -- Move this entity to the right of the other entity
--             set_position(this, other_x+other_width, this_y)
--         end
--     end

--     -- implement damage to player when colliding with enemy, meteor and such
-- end
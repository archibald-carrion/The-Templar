-- -- Global variable
is_shooting = false

function update()

    player_velocity = get_player_velocity(this) -- need to update because player can get speed boost
    fixed_player_velocity = math.sqrt((player_velocity*player_velocity)/2)

    set_velocity(this, 0, 0);
    velocity_x = 0
    velocity_y = 0

    -- Check if the player is pressing the wasd keys to move the player
    if is_action_activated("up") then
        velocity_y = velocity_y + -1
    end
    if is_action_activated("left") then
        velocity_x = velocity_x + -1
    end
    if is_action_activated("down") then
        velocity_y = velocity_y + 1
    end
    if is_action_activated("right") then
        velocity_x = velocity_x + 1
    end

    -- Normalize the velocity so that the player moves at the same speed in all directions
    if velocity_x ~=0 and velocity_y ~= 0 then
        velocity_x = velocity_x * fixed_player_velocity
        velocity_y = velocity_y * fixed_player_velocity
    else
        velocity_x = velocity_x * player_velocity
        velocity_y = velocity_y * player_velocity
    end

    set_velocity(this, velocity_x, velocity_y)

    
    -- change the ship rotation based on the direction in which it is moving
    -- using the set_rotation(this, angle) function
    -- Calculate and set rotation based on movement direction
    if velocity_x ~= 0 or velocity_y ~= 0 then
        -- Calculate angle in radians using atan2
        local angle = math.atan2(velocity_x, -velocity_y)
        -- Convert to degrees and adjust for SDL
        local degrees = angle * (180 / math.pi)
        
        -- Set the rotation
        set_rotation(this, degrees)
    end
    
    location_x, location_y = get_position(this)

    -- set the player rotation of game
    update_player_location(location_x, location_y)

    -- check if the player is pressing space key to shoot
    if is_shooting  == false then
        if is_action_activated("shoot") then
            shoot_bullet(this)
            is_shooting = true
        end
    else 
        if not is_action_activated("shoot") then
            is_shooting = false
        end
    end
    
end

function on_collision(other)
    this_tag = get_tag(this)
    other_tag = get_tag(other)
    
    -- Check if the player is colliding with a wall, and if so don't allow the player to move through the wall
    if other_tag == "wall_0" or other_tag=="wall_1" then
        this_x, this_y = get_position(this)
        this_width, this_height = get_size(this)
        other_x, other_y = get_position(other)
        other_width, other_height = get_size(other)
        
        if top_collision(this, other) then
            -- Move this entity below the other entity
            set_position(this, this_x, other_y + other_height - 1)
        elseif left_collision(this, other) then
            -- Move this entity to the right of the other entity
            set_position(this, other_x + other_width + 1, this_y)
        elseif right_collision(this, other) then
            -- Move this entity to the left of the other entity
            set_position(this, other_x - this_width - 1, this_y)
        elseif bottom_collision(this, other) then
            -- Move this entity above the other entity
            set_position(this, this_x, other_y - this_height - 1)
        end
    end

    -- implement damage to player when colliding with enemy, meteor and such
end
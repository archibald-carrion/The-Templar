
function on_collision(other)
    this_tag = get_tag(this)
    other_tag = get_tag(other)

    if other_tag == "wall"  or other_tag == "floor" then
        this_x, this_y = get_position(this)
        this_width, this_height = get_size(this)
        other_x, other_y = get_position(other)
        other_width, other_height = get_size(other)
        this_vel_x, this_vel_y = get_velocity(this)

        if this_vel_x == 0 and this_vel_y == 0 then
            this_vel_x, this_vel_y = get_buffered_velocity(this)
        end

        if left_collision(this, other) then
            print("old velocity left col" .. this_vel_x)
            new_vel = this_vel_x * -1
            print("new left right col" .. new_vel)
            set_velocity(this, new_vel, this_vel_y)
        elseif right_collision(this, other) then
            print("old velocity right col" .. this_vel_x)
            new_vel = this_vel_x * -1
            print("new velocity right col" .. new_vel)
            set_velocity(this, new_vel, this_vel_y)
        end
    end

end
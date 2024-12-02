function on_collision(other)
    if get_tag(other) == "player" then
        print("Collision with door 2")
        go_to_scene("level_02")
    end
end
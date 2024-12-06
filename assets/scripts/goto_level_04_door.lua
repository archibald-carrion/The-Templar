function on_collision(other)
    if get_tag(other) == "player" then
        print("Collision with door 3")
        go_to_scene("level_04")
    end
end
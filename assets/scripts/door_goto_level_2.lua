function on_collision(other)
    if get_tag(other) == "player" then
        print("Collision with door 2")
        go_to_scene("level_02")
    end
end

-- TODO: move this function to another file so player cannot just click on the door to go to the next level
function on_click()
    print("Click on door 2")
    go_to_scene("level_02")
end
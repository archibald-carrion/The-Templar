function on_collision(other)
    if get_tag(other) == "player" then
        print("Collision with door 3")
        go_to_scene("level_03")
    end
end

function on_init()
    -- stop all sound from previous scene
    stop_all_sounds()
    reset_camera()
    play_music("level_2_song")
end
function on_init()
    -- stop all sound from previous scene
    --print("[LUA] Stopping all sounds")
    stop_all_sounds()
    --print("[LUA] playing game music")
    reset_camera()
    play_music("menu_music")
end
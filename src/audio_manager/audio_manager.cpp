#include "audio_manager.hpp"
#include <iostream>

AudioManager::AudioManager() {
    // std::cout << "[AUDIOMANAGER] Constructor" << std::endl;
}

AudioManager::~AudioManager() {
    clear_audio();
}

void AudioManager::clear_audio() {
    music_tracks.clear();
    sound_effects.clear();
}

void AudioManager::add_music(const std::string& music_id, const std::string& file_path) {
    Music music(Mix_LoadMUS(file_path.c_str()), sdlMusicDeleter);

    if (music == nullptr) {
        std::cerr << "[AudioManager] Failed to load music: " << Mix_GetError() << std::endl;
        return;
    }
    music_tracks.emplace(music_id, std::move(music));
}

Music AudioManager::get_music(const std::string& music_id) {
    auto it = music_tracks.find(music_id);
    if (it != music_tracks.end()) {
        return it->second;
    }
    std::cerr << "[AudioManager] Music ID not found: " << music_id << std::endl;
    return nullptr;
}

void AudioManager::add_sound_effect(const std::string& sound_id, const std::string& file_path) {
    Mix sound(Mix_LoadWAV(file_path.c_str()), sdlMixDeleter);
    if (sound == nullptr) {
        std::cerr << "[AudioManager] Failed to load sound effect: " << Mix_GetError() << std::endl;
        return;
    }
    sound_effects.emplace(sound_id, std::move(sound));
}

Mix AudioManager::get_sound_effect(const std::string& sound_id) {
    auto it = sound_effects.find(sound_id);
    if (it != sound_effects.end()) {
        return it->second;
    }
    std::cerr << "[AudioManager] Sound ID not found: " << sound_id << std::endl;
    return nullptr;
}

void AudioManager::play_music(const std::string& music_id, int loops) {
    Music music = get_music(music_id);
    if (music != nullptr) {
        if (Mix_PlayMusic(music.get(), loops) == -1) {
            std::cerr << "[AudioManager] Failed to play music: " << Mix_GetError() << std::endl;
        }
    }
}

void AudioManager::play_sound_effect(const std::string& sound_id, int loops) {
    Mix sound = get_sound_effect(sound_id);
    if (sound != nullptr) {
        if (Mix_PlayChannel(-1, sound.get(), loops) == -1) {
            std::cerr << "[AudioManager] Failed to play sound effect: " << Mix_GetError() << std::endl;
        }
    }
}

void AudioManager::stop_music(const std::string& music_id) {
    Music music = get_music(music_id);
    if (music != nullptr) {
        Mix_HaltMusic();
    }
}

void AudioManager::stop_sound_effect(const std::string& sound_id) {
    Mix sound = get_sound_effect(sound_id);
    if (sound != nullptr) {
        Mix_HaltChannel(-1);
    }
}

void AudioManager::stop_all_sounds() {
    // std::cout << "[AUDIOMANAGER] Stopping all sounds" << std::endl;

    // stop all sound effects
    Mix_HaltChannel(-1);

    // stop all music
    Mix_HaltMusic();
}

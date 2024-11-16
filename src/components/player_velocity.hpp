#ifndef PLAYER_VELOCITY_HPP
#define PLAYER_VELOCITY_HPP


/**
 * @struct PlayerVelocity
 * @brief The PlayerVelocity struct contains the velocity of the player entity.
 */
struct PlayerVelocity {
    int player_velocity; // velocity of the player, used to know how much to move the player

    /**
     * @brief Construct a new Player Velocity object
     * @param player_velocity The velocity of the player
     */
    PlayerVelocity(int player_velocity = 0) {
        this->player_velocity = player_velocity;
    }
};

#endif // PLAYER_VELOCITY_HPP
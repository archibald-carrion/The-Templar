#ifndef PLAYER_SCORE_HPP
#define PLAYER_SCORE_HPP


/**
 * @struct PlayerScore
 * @brief The PlayerScore struct contains the current score of the player entity.
 */
struct PlayerScore {
    int player_score; // score of the player, used to keep track of the player's score

    /**
     * @brief Construct a new Player Score object
     * @param player_score The score of the player
     */
    PlayerScore(int player_score = 0) {
        this->player_score = player_score;
    }
};

#endif // PLAYER_SCORE_HPP
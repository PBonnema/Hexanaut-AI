export module Hexanaut:Player;

// import :Position;
// import :PlayerMove;
// import :GameState;
import std;

struct PlayerMove;
export struct GameState;

// Represents a player. This class is part of the game state and is immutable.
export class Player {
public:
    Player();
    explicit Player(const std::array<double, 2>& position);

    PlayerMove choose_move(const GameState& game_state) const;

    // Returns a copy of the player that has moved at the given speed along the given direction relative to this player's position.
    Player move(double speed, double direction) const;

private:
    const std::array<double, 2> position_;
};

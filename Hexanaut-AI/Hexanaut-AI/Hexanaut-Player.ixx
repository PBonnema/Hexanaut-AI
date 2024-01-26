export module Hexanaut:Player;

import :fwddecl;
import :Position;

// Represents a player. This class is part of the game state and is immutable.
export class Player {
public:
    Player();
    explicit Player(const Position& position);

    PlayerMove choose_move(const GameState& game_state) const;

    // Returns a copy of the player that has moved at the given speed along the given direction relative to this player's position.
    Player move(double speed, double direction) const;

private:
    const Position position_;
};

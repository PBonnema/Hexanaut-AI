module;

#include <optional>

export module Hexanaut:Player;

import :fwddecl;
import :Position;
import :PolyLine;

// Represents a player. This class is part of the game state.
export class Player {
public:
    explicit Player(const Position& position, double direction_radians);

    PlayerMove choose_move(const GameState& game_state) const;

    // Moves the player at the given speed along the given direction relative to it's current position.
    PolyLine move(double speed, double direction_radians, const Position& map_size);

    std::optional<Position> check_exited_own_territory() const;
    Position get_position() const;

private:
    Position position_;
    double direction_radians_;
    PolyLine territory_border_;
    std::optional<PolyLine> tail_;
};

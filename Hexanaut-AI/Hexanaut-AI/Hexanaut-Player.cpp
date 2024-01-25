module Hexanaut:Player;

import :GameState;
import :PlayerMove;
// import :Position;
import std;

Player::Player(): position_{ }
{
}

Player::Player(const std::array<double, 2>& position): position_{ position }
{
}

PlayerMove Player::choose_move(const GameState& game_state)
{
    const PlayerMove move{ 0.0 };
    return move;
}

Player Player::move(double speed, double direction)
{
    // Calculate delta vector
    // Add delta vector to position
    return Player{ std::array<double, 2>{ 1, 1 } };
}

module;

#include <complex>

module Hexanaut:Player;
import :Player;

import :GameState;
import :PlayerMove;
import :Position;

Player::Player(): position_{ }
{
}

Player::Player(const Position& position): position_{ position }
{
}

PlayerMove Player::choose_move(const GameState& game_state) const
{
    const PlayerMove move{ 0.0 };
    return move;
}

Player Player::move(double speed, double direction) const
{
    const Position delta{ std::cos(direction) * speed, std::sin(direction) * speed };
    return Player{ Position{ position_[0] + delta[0], position_[1] + delta[1] } };
}

module Hexanaut:Player;
import :Player;

import :GameState;
import :PlayerMove;
import :Position;

import std;

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
    // Calculate delta vector
    // Add delta vector to position
    return Player{ Position{ 1, 1 } };
}

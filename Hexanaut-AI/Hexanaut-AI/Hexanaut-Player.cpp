module;

#include <algorithm>
#include <complex>
#include <numbers>

module Hexanaut:Player;
import :Player;

import :GameState;
import :PlayerMove;
import :Position;
import :PolyLine;

Player::Player(const Position& position, const double direction_radians) :
    position_{ position },
    direction_radians_{ direction_radians }
{
}

PlayerMove Player::choose_move(const GameState& game_state) const
{
    const PlayerMove move{ 0.0 };
    return move;
}

PolyLine Player::move(const double speed, const double direction_radians, const Position& map_size)
{
    const auto old_position = position_;

    // Move the player
    position_.x += std::cos(direction_radians) * speed;
    position_.y += std::sin(direction_radians) * speed;

    // Clamp the player position to the map boundaries
    position_.x = std::clamp(position_.x, 0.0, map_size.x);
    position_.y = std::clamp(position_.y, 0.0, map_size.y);

    // If the player has hit a wall, change the direction to be parallel to the wall
    if (position_.x == 0.0 || position_.x == map_size.x)
    {
        if (direction_radians > 0.0 && direction_radians < std::numbers::pi)
        {
            direction_radians_ = std::numbers::pi / 2.0;
        }
        else
        {
            direction_radians_ = 3.0 * std::numbers::pi / 2.0;
        }
    }

    if (position_.y == 0.0 || position_.y == map_size.y)
    {
        if (direction_radians > std::numbers::pi / 2.0 && direction_radians < 3.0 * std::numbers::pi / 2.0)
        {
            direction_radians_ = std::numbers::pi;
        }
        else
        {
            direction_radians_ = 0;
        }
    }

    // TODO handle edge cases where the player is in a corner


    // Also need to update the player movement objects in the tree. But will that then result in 2 pieces of movement?
        // One for reaching the wall, and one for moving alongside the wall?
        // This could potentially be even 3 pieces if the player also hits a corner in the same step.
        // Or more if the corners are really close by and the player hits multiple corners at once. (but maps shouldn't really have such corners).

    // Return the path the player has taken
    return PolyLine{ std::vector{ old_position, position_ } };
}



std::optional<Position> Player::check_exited_own_territory() const
{
    return {};
}

Position Player::get_position() const
{
    return position_;
}

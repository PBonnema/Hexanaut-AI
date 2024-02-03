module;

#include <algorithm>
#include <vector>
#include <memory>

module Hexanaut:Game;
import :Game;

import :GameState;
import :Player;
import :PlayerMove;
import :Position;

HexanautGame::HexanautGame(const int player_count, const double player_speed, const double turn_speed_degrees) :
    game_state_{ std::make_unique<GameState>(std::vector<Player>(player_count)) },
    player_speed_{ player_speed },
    turn_speed_degrees_{turn_speed_degrees }
{
}

bool HexanautGame::step()
{
    // Ask each player for his move this step
    std::vector<Player> moved_players;
    for (const auto& player : game_state_->players)
    {
        // TODO, give the player a copy of the game state with limited visibility (his screen). Screensize depends on speed.;
        // TODO Spatial query; everything within rectangle. Cuts off polygons.
        PlayerMove move = player.choose_move(*game_state_);
        move.turn_angle_degrees = clamp_turn_angle(move.turn_angle_degrees, turn_speed_degrees_);
        moved_players.emplace_back(player.move(player_speed_, move.turn_angle_degrees));
    }

    // Resolve the game state now that we know what each player wants to do
    game_state_ = resolve_player_movement(*game_state_, moved_players);
        
    // Returns a boolean indicating whether the game ended this step
    return false;
}

std::unique_ptr<GameState> HexanautGame::resolve_player_movement(
    const GameState& game_state,
    const std::vector<Player>& moved_players)
{
    // First, update the tree with all movements: player position has changed
    // Player radius/hitbox??

    
    // Resolve player-boundary collisions; Just bounds checking
        // Means updating player direction
    // Resolve player exiting their territory; Spatial query; Line (player movement) intersecting some polygon boundary
        // Means starting a capture = start a tail; Update the tree
    // Resolve player entering their territory; Spatial query; Line (player movement) intersecting some polygon boundary
        // Means ending a capture = ending a tail
        // Player gains new territory; Spatial query if doing cells. Otherwise, just merge polygon of the tail into territory polygon.
            // Player increase level/speed
        // Other players might lose territory; Spatial query if doing cells. Otherwise, just merge polygon of the tail into territory polygon.
            // Players lose level/speed
    // Extend the tail if still outside of territory; Update the tree
    // Resolve player-player collisions; Spatial query; Line intersecting any of other lines (player movement)
        // Means both players die and their territory and tails disappear
    // Resolve player-tail collisions; Spatial query; Line (player movement) intersecting some polygon boundary
        // means 1 player dies
        // The other player gets a portion of his terrain in a certain radius; Spatial query; Get all polygons in a certain large area. Also query for cells if doing cells.
    // Check end game condition; Spatial query... sort of. Counting number of cells or total area of territory.

    // If a player dies, take note of the step number and territory size and update his state to dead.; Spatial query... sort of

    // TODO what if a tail collision happens in the same step the capture finishes?
        // By ordering the actions as above, the player capturing wins
        // If a player exits his territory while his tail is collided on the same step, he dies.
    
    auto new_game_state = std::make_unique<GameState>(moved_players);
    return new_game_state;
}

double HexanautGame::clamp_turn_angle(double turn_speed, double max_turn_speed)
{
    return std::clamp(turn_speed, -max_turn_speed, max_turn_speed);
}

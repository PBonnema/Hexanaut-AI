module;

#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>

module Hexanaut:Game;
import :Game;

import :GameState;
import :Player;
import :PlayerMove;
import :Position;

import RTree;

HexanautGame::HexanautGame(const int player_count, const double player_speed, const double turn_speed_radians, const Position& map_size) :
    game_state_{ std::make_unique<GameState>(std::vector<Player>(player_count)) },
    player_speed_{ player_speed },
    turn_speed_radians_{ turn_speed_radians },
    map_size_{ map_size }
{
}

bool HexanautGame::step()
{
    // Ask each player for his move this step
    std::unordered_map<Player*, PlayerMove> moves;
    for (auto&& player : game_state_->players)
    {
        // TODO, give the player a copy of the game state (or just the Tree?) with limited visibility (his screen). Screen size depends on speed.
        // TODO Spatial query; everything within rectangle. Cuts off polygons.
        moves[&player] = player.choose_move(*game_state_);
    }

    // Resolve the game state now that we know what each player wants to do
    resolve_player_movement(moves);

    // Returns a boolean indicating whether the game ended this step
    return false;
}

void HexanautGame::resolve_player_movement(const std::unordered_map<Player*, PlayerMove>& player_moves)
{
    // The tree will contain 3 things, all in the form of lists of connected lines:
        // Player movement (list of a single line with just he player movement vector) (actually not single in the case of corners)
        // Territory edge: connected list of lines that ends at the start
        // Player tail: set of all movements outside of territory so far.

    for (auto&& [player, move] : player_moves)
    {
        const double turn_angle_radians = clamp_turn_angle(move.turn_angle_radians, turn_speed_radians_);
        PolyLine player_movement_line = player->move(player_speed_, turn_angle_radians, map_size_);

        // Remove the player movements objects from the previous step from the tree.

        // Update the RTree with the new player movement object.
        player_movements_tree_.insert(PlayerPolyLineRTreeEntry{ player_movement_line, player });
    }

    // Resolve player exiting their territory
        // Means starting a capture = start a tail; Add the tail to the tree
    resolve_player_exiting_own_territory();

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
        // Optional: The other player gets a portion of his terrain in a certain radius; Spatial query; Get all polygons in a certain large area. Also query for cells if doing cells.
    // Check end game condition; Spatial query... sort of. Counting number of cells or total area of territory.

    // If a player dies, take note of the step number and territory size and update his state to dead.; Spatial query... sort of

    // TODO what if a tail collision happens in the same step the capture finishes?
        // By ordering the actions as above, the player capturing wins. That should be fine.
        // If a player exits his territory while his tail is collided with on the same step, he dies.
}

void HexanautGame::resolve_player_exiting_own_territory()
{
    // for (auto&& player : moved_players)
    // {
    //     // std::optional<Position> exit
    //     // If player exited their own territory
    //         // Find intersection point of their movement line with their territory border
    //         // Create a new tail for them, starting at the intersection to their new position.
    //         // Store it in the player object.
    //         // Add it to the tree
    // }
}

double HexanautGame::clamp_turn_angle(double turn_speed, double max_turn_speed)
{
    return std::clamp(turn_speed, -max_turn_speed, max_turn_speed);
}

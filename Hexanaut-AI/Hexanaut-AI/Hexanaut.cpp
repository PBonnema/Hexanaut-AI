module;

#include <vector>
#include <memory>

module Hexanaut;

import :GameState;
import :Player;
import :PlayerMove;
import :Position;

HexanautGame::HexanautGame(const int player_count, const double player_speed) :
    game_state_{ std::make_unique<GameState>(std::vector<Player>(player_count)) },
    player_speed_{ player_speed }
{
}

bool HexanautGame::step()
{
    // Ask each player for his move this step
    std::vector<Player> moved_players;
    for (const auto& player : game_state_->players)
    {
        const PlayerMove move = player.choose_move(*game_state_);
        moved_players.emplace_back(player.move(player_speed_, move.angle_degrees));
    }
    game_state_ = resolve_player_movement(*game_state_, moved_players);
        
    // Returns a boolean indicating whether the game ended this step
    return false;
}

std::unique_ptr<GameState> HexanautGame::resolve_player_movement(
    const GameState& game_state,
    const std::vector<Player>& moved_players)
{
    auto new_game_state = std::make_unique<GameState>(moved_players);
    return new_game_state;
}

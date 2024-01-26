module;

#include <memory>

export module Hexanaut;

export import :GameState;
export import :Player;
export import :PlayerMove;

export class HexanautGame {
public:
    HexanautGame(int player_count, double player_speed);

    bool step();

private:
    static std::unique_ptr<GameState> resolve_player_movement(const GameState& game_state, const std::vector<Player>& moved_players);

    std::unique_ptr<GameState> game_state_;
    double player_speed_;
};

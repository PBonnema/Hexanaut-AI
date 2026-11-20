module;

#include <memory>
#include <unordered_map>

export module Hexanaut:Game;

import :fwddecl;
import :Position;

import RTree;

export class HexanautGame {
public:
    HexanautGame(int player_count, double player_speed, double turn_speed_radians, const Position& map_size);

    bool step();

private:
    void resolve_player_movement(const std::unordered_map<Player*, PlayerMove>& player_moves);
    void resolve_player_exiting_own_territory();

    static double clamp_turn_angle(double turn_speed, double max_turn_speed);

    std::unique_ptr<GameState> game_state_; // TODO do we want this to be on the stack instead?
    double player_speed_;
    double turn_speed_radians_;
    Position map_size_;
    RTree<PlayerPolyLineRTreeEntry> player_movements_tree_;
    RTree<PlayerPolyLineRTreeEntry> player_tails_tree_;
    RTree<PlayerPolyLineRTreeEntry> player_territory_boundaries_tree_;
};

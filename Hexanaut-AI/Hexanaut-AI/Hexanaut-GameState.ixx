module;

#include <vector>

export module Hexanaut:GameState;

import :fwddecl;

// The game state is immutable.
export struct GameState {
    const std::vector<Player> players;
};

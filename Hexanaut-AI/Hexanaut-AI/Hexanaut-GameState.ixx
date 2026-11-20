module;

#include <vector>

export module Hexanaut:GameState;

import :fwddecl;

// The game state is not immutable because the objects RTree reference player objects in the game state.
// Copying the game state would require copying the player objects and updating the whole tree, which would be expensive.
export struct GameState {
    std::vector<Player> players;
};

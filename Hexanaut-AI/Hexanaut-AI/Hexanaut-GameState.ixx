
export module Hexanaut:GameState;

import std;
// import :Player;

class Player;

// The game state is immutable.
export struct GameState {
    const std::vector<Player> players;
};
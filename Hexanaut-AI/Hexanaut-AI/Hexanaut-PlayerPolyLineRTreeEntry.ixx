export module Hexanaut:PlayerPolyLineRTreeEntry;

import :fwddecl;
import :PolyLine;

export struct PlayerPolyLineRTreeEntry
{
    Player* player;
    PolyLine poly_line;
};

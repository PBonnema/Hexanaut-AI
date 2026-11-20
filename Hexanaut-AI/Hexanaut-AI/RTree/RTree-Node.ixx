module;

#include <vector>

export module RTree:Node;

import :fwddecl;

export template<typename TEntry>
class Node
{
public:
    bool is_leaf() const;

private:
    std::vector<Node> children_;
    std::vector<TEntry> entries_;
};

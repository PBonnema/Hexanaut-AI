export module RTree;

import :fwddecl;
import :Node;

export template<typename TEntry>
class RTree
{
public:
    void insert(const TEntry& entry);

private:
    Node<TEntry> root_;
};

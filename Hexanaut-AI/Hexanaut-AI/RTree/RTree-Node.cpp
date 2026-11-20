module RTree:Node;
import :Node;

template <typename TEntry>
bool Node<TEntry>::is_leaf() const
{
    assert(children_.empty() != entries_.empty());
    return children_.empty();
}

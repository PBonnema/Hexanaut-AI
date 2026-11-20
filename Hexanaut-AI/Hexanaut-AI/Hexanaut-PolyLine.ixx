module;

#include <span>
#include <vector>

export module Hexanaut:PolyLine;

import :fwddecl;

// Represents a connected set of line segments on the map, as a list of positions connected by an imaginary line.
// If the list ends at the start, it forms a polygon.
export class PolyLine
{
public:
    explicit PolyLine(std::span<const Position> line_segments = {});

    bool intersects(const PolyLine& other) const;

    std::span<const Position> get_line_segments() const;

private:
    static bool do_line_segments_intersect(const std::pair<const Position*, const Position*>& a, const std::pair<const Position*, const Position*>& b);
    static int calculate_orientation(const Position& p, const Position& q, const Position& r);
    static bool on_segment(const Position& p, const Position& q, const Position& r);

    std::vector<Position> line_segments_;
};

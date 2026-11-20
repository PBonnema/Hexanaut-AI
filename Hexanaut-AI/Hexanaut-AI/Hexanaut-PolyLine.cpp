module;

#include <ranges>
#include <utility>

module Hexanaut:PolyLine;
import :PolyLine;

import :Position;

PolyLine::PolyLine(std::span<const Position> line_segments)
    : line_segments_(line_segments.begin(), line_segments.end())
{
}

bool PolyLine::intersects(const PolyLine& other) const
{
    // The poly lines intersect if any of their line segments intersect
    // TODO optimize with the RTree

    const Position* previous_a = &line_segments_.front();
    for(auto&& a : line_segments_ | std::views::drop(1))
    {
        const Position* previous_b = &other.get_line_segments().front();
        for(auto&& b : other.get_line_segments() | std::views::drop(1))
        {
            if (do_line_segments_intersect({ previous_a, &a }, { previous_b, &b }))
            {
                return true;
            }
            previous_b = &b;
        }
        previous_a = &a;
    }

    return false;
}

std::span<const Position> PolyLine::get_line_segments() const
{
    return line_segments_;
}

bool PolyLine::do_line_segments_intersect(const std::pair<const Position*, const Position*>& a, const std::pair<const Position*, const Position*>& b)
{
    // https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
    const int o1 = calculate_orientation(*a.first, *a.second, *b.first);
    const int o2 = calculate_orientation(*a.first, *a.second, *b.second);
    const int o3 = calculate_orientation(*b.first, *b.second, *a.first);
    const int o4 = calculate_orientation(*b.first, *b.second, *a.second);

    // General case
    if (o1 != o2 && o3 != o4)
    {
        return true;
    }

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && on_segment(*a.first, *b.first, *a.second)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && on_segment(*a.first, *b.second, *a.second)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && on_segment(*b.first, *a.first, *b.second)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && on_segment(*b.first, *a.second, *b.second)) return true;

    return false;
}

// Finds the orientation of the points p, q, and r.
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int PolyLine::calculate_orientation(const Position& p, const Position& q, const Position& r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/ for details of this calculation.
    const double value = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (value == 0)
    {
        // Collinear
        return 0;
    }

    // Clock or counter-clock wise
    return value > 0 ? 1 : 2;
}

// Given three collinear points p, q, r, the function checks if point q lies on line segment 'pr'
bool PolyLine::on_segment(const Position& p, const Position& q, const Position& r)
{
    return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
           q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
}

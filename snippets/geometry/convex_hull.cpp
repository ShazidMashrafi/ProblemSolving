struct Point
{
    int x, y;
    bool operator<(const Point &other) const
    {
        return x == other.x ? y < other.y : x < other.x;
    }
    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }
};
 
int orientation(Point a, Point b, Point c)
{
    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0)
        return 0;             // colinear
    return (val > 0) ? 1 : 2; // clock or counterclockwise
}
 
vector<Point> convex_hull(vector<Point> pts)
{
    if (pts.size() <= 1)
        return pts;
    sort(all(pts));
    vector<Point> lower, upper;
 
    for (auto p : pts)
    {
        while (lower.size() >= 2 &&
               orientation(lower[lower.size() - 2], lower[lower.size() - 1], p) != 2)
            lower.pop_back();
        lower.push_back(p);
    }
 
    for (int i = pts.size() - 1; i >= 0; i--)
    {
        auto p = pts[i];
        while (upper.size() >= 2 &&
               orientation(upper[upper.size() - 2], upper[upper.size() - 1], p) != 2)
            upper.pop_back();
        upper.push_back(p);
    }
 
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), all(upper));
    return lower;
}
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
// find_by_order(k) : returns iterator to kth smallest element (0-indexed)
// order_of_key(v)  : returns number of elements strictly smaller than v

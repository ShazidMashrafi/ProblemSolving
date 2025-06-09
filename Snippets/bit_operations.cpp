// __builtin_popcountll(n); -> counts number of set bits
// check bit (n & (1LL << ith))
// n set bit number -> (1LL << n) - 1
// set bit -> [ n | (1LL << ith) ];
// unset bit -> [ n & (~(1LL << ith)) ];
// to uppercase -> [ 'a' ^ 32 ];
// flip the kth bit -> X = X ^ (1LL << k);
// Use 1LL when shifting bits : (1LL << x)
Some properties of bitwise operations:
 a|b = a^b + a&b
 a^(a&b) = (a|b)^b
 b^(a&b) = (a|b)^a
 (a&b)^(a|b) = a^b
Addition:
 a+b = a|b + a&b
 a+b = a^b + 2(a&b)
Subtraction:
 a-b = (a^(a&b))-((a|b)^a)
 a-b = ((a|b)^b)-((a|b)^a)
 a-b = (a^(a&b))-(b^(a&b))
 a-b = ((a|b)^b)-(b^(a&b))
bool isPowerof2(int n){ return (!(n & (n - 1)) && n); }
int toggleBit(int n, int ith) { return n ^ (1 << ith);}
int numOfDigits(int n) { return floor(log10(n) + 1); }

/* Inverse : (n^-1)%m = (n^m-2)%m
Ex: Inverse of x would be,
BinaryExponentiation(x, MOD-2);
For normal constrain just divide by x(number) */
int BinaryExponentiation(int x, int y)
{
  int res = 1;
  while(y > 0){
    if(y & 1) res *= x; // MOD
    y >>= 1; // -> y /= 2;
    x *= x; // MOD
  } // MOD for larger numbers
  return res;
}

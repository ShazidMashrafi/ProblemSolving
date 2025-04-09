#include <bits/stdc++.h>
using namespace std;
int rnd(int a, int b)
{
    return a + rand() % (b - a + 1);
}
int main() 
{
    int w = rnd(1, 100);
    cout<<w<<endl;
}
#include<bits/stdc++.h>
using namespace std;
//https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/A
//errores: hay que suar long long

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int64_t n,h,w;
    cin >> w >> h >> n;

    // l no se cumple // r se cumple
    int64_t l=0, r=max(h,w)*n;
    r=1;
    while(   !((r/h)*(r/w) >= n) ) r*=2;

  // 0 0 0 0 0 0 0  1 1 1  1 1 1 1 1
    while( r>l+1 ){
        int64_t m = (r+l)/2;
        if(  ( (m/h)*(m/w) >= n) ) {   // cuantos caben en uno de tam  ,m   m/h * m/w
            r = m;
        }else{
            l = m;
        }
    }
    cout << r << '\n';
}

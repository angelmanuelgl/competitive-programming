#include<bits/stdc++.h>
using namespace std;
//https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/C

int64_t n,x,y; // x<=y
bool sePuedeHacern( int t ){
    int cant = 0;
    if( t>=x ){
        cant++;
        t-=x;
        cant += t/x;
        cant += t/y;

        return cant>=n;

    }else{
        return false;
    }

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);



    cin >> n >> x >> y;
    if( x> y) swap(x,y);

    // 0 0 0 0 0 0 1 1 1 1

    //l no se pude, r si se puede
    int l=0, r=1;

    while( !sePuedeHacern(r) ) r*=2;

    while( l+1<r ){ //queremos l+1=r
        int m = (l+r)/2;
        if( sePuedeHacern(m) ) r = m;
        else l =m;
    }
    cout << r << '\n';

}

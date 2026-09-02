#include<bits/stdc++.h>
using namespace std;


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n=10;
    vector<int> vec={1,4,9,13,17,19,23,29,32,34};
    n = vec.size();


    ///binary serach
    int l=0;
    int r=n-1;
    bool ok = false;
    int x = 13;
    while( r>=l ){
        int m = (l+r)/2;
        if( vec[m] == x ){
            ok = true;
            break;
        } else if ( vec[m] < x )
            l = m+1;
        else if( vec[m] > x )
            r = m-1;
    }
    if( ok ) cout << "YES\n";
    else cout << "NO";



    ///find closest in array
    // l=-1 r=n // buscar hasta que l y r sean adyacentes
    // min i : vec[x]>=x // vec[l]<x   vec[r]>=x  // return r
    // max i : vec[x]<=x // vec[l]<=x   vec[r]>x  // return l




    ///buscar el primer elemento bueno
    vector<int> f={0,0,0,0,0,1,1,1,1,1};
    n = vec.size();
    l=0;
    r=n-1;
    while( r>l+1 ){
        int m = (l+r)/2;
        if( f[m] == true )
            r = m;
        else
            l = m;
    }
    cout << r << "\n";



    ///BS in \R


}

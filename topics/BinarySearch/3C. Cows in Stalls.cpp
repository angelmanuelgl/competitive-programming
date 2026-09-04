#include<bits/stdc++.h>
using namespace std;

int n,k;
set<int64_t> a;

bool ansMayorIgual( int64_t m ){
    int64_t stall=*a.lower_bound(0);
//    cout << '\n' << stall << '\n';

    for( int i=1; i<=k-1; i++ ){
        stall+=m;
        auto xd = a.lower_bound( stall );
        if( xd == a.end() ) return false;
        stall = *xd;

//        cout << stall << '\n';
    }

    return true;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    cin >> n >> k;

    int x;
    for( int i=0; i<n; i++ ){
        cin >> x;
        a.insert(x);
    }

    // 1 1 1 1 1 1 1 1 1 1 1 1 1 1  0 0 0 0 0 0
    // l<=ans // ans < r
    int64_t l=0,r=1;
    while( ansMayorIgual(r) ) r*=2;

    for( int i=0; i<=20; i++ ){
        int xd= ansMayorIgual(i);
//        cout <<  "---> " << i << ' ' << xd <<  '\n';
    }

    while( l+1 < r ){
        int64_t m = (l+r)/2;
        if( ansMayorIgual(m) ) l = m;
        else r = m;

    }

    cout << l << '\n';
}

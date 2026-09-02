#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;

bool debug =  true;
#define DEBUG if(debug)



const int MOD = 998244353;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    // ifstream cin("in.txt");

    int n; cin >> n;
    ll a[n], b[n];

    for( ll &x : a ) cin >> x;
    for( ll &x : b ) cin >> x;

    // for( ll &x : a ) cout << x << ' ';
    // for( ll &x : b ) cout << x << ' ';
    // cout << '\n';

    for( int i=0; i<n; i++){
        ll pos = i+1;
        a[i] *= -(pos * (n+1-pos)) ;
        // 10 ^ ( 6+6+5 )
    }

    sort( a, a+n );
    sort( b, b+n );

    ll ans = 0;
    for( int i=0; i<n; i++ ){
        a[i] %= MOD;
        ans -= ( a[i]*b[i] % MOD );
        if( ans > MOD ) ans -= MOD;
    }
    cout << ans << '\n';
}
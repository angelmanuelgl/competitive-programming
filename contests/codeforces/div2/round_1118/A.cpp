/*  
    * contest: Codeforces Round 1118 (Div. 2)
    * problem: A. Odd Eraser
    * topic: 
    * https://codeforces.com/contest/2258
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- Type Aliases ---
typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

// --- Short Macros ---
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()



// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //

// uso :  g++ -DLOCAL K.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.txt");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int t; cin >> t;

    while(t--){
        int n; cin >> n;
        
        ll a, b,x[n];

        for( int i=0; i<n; i++) 
            cin >> x[i];
      
        a = x[0];
        b = x[n-1];

        if( n == 1){
            cout << x[0] << "\n";
            continue;
        }

        ll ans = gcd(a,b);

        cout << ans <<"\n";
    }
}
/*  
    * Contest: Codeforces Round 1118 (Div. 2)
    * URL: https://codeforces.com/contest/2258
    * Problem: B1. Carrot Chopdown (Easy Version)

    * topic: 
    * Algorithm: 
    * Complexity: O(M)

    * Status: ACCEPT
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


// --- DEBUGER SETUP ---
#ifdef LOCAL
    bool debug = true;
#else
    bool debug = false;
#endif

#define DEBUG if(debug)
#define NODEBUG if(!debug)

// Overload for std::pair
template<typename A, typename B>
ostream& operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.fi << ", " << p.se << ')';
}
// Overload for Containers (excluding std::string) via SFINAE
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream &os, const C &v) {
    string sep;
    for(const T &x : v) os << sep << x, sep = " ";
    return os;
}
// Logger Function
#define print(...) logger (#__VA_ARGS__,__VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values){
    if( !debug ) return;
    cout << "[Debug]\n\t" << vars << " = ";
    string d = "[";
    (..., (cout << d << values, d = "] ["));
    cout << "]\n";
}

const int MOD = 1e9 + 7;


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
        int n, m; cin >> n >>m;
        vll cnt(m+2, 0); 
        vll acumm(m+2, 0);
        
        ll maxi =0, total = 0, x;
        for( int i=0; i<n; i++){
            cin >> x;
            // cuantas zanahoras de cada longitud
            cnt[x]++; 
            maxi = max(maxi, x);
            total++;
        }

        for( int i=1; i<=m; i++){
            acumm[i] = acumm[i-1] + cnt[i];
        }

        print( cnt);
        print( acumm );

        // provar cada corte
        ll ans = 0;
        for( int i=1; i<=maxi; i++){
            // cuantas de longitud i quedan despues del corte
            
            // #{ a_k : a_k >= i }
            ll cnt_i = total - acumm[i-1];
            // los qeu tenian el dolble del tam
            if( i*2 <= m)
                cnt_i += cnt[i*2];

            ans = max( ans, cnt_i);
        }

        cout << ans << "\n";
    }
}
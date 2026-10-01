/*  
    * Contest: Codeforces Round 1109 (Div. 3)
    * URL: https://codeforces.com/contest/2244
    * Problem: D. Yaroslav and Productivity

    * Topic: constructive algorithms  | greedy | math 
    * Algorithm: - b_1 < b_2 < ... b_i < b_{i+1} < .. < b_m   
                 - note that we can choicen the sing of [b_i, b_{i+1}]
                   independently of the choice of sing for the others 
    * Complexity:  O( M log M + N) for each test case

    * Status: ACCEPTED
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

// start implementation 2:30
// finish 2:50
// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int t; cin  >> t;

    while( t-- ){
        int n,m; cin >> n >> m;

        vi val(n+1);
        val[0] = 0; 
        for( int i=1; i<=n; i++) cin >> val[i];
        vll post(m); for( ll &x: post) cin >> x;


        print( val);
        print( post);
        // acumulado for range sum
        vll acumm(n+2,0);
        for( int i=1;  i<=n; i++){
            acumm[i] = acumm[i-1] + val[i];
        }

        // we want segments [1,b_1] [b_1 +1, b_2] ...  [b_i + 1,  b_{i+1}]
        sort( all(post));
  

        // abs val for each segmetn
        ll ans = 0;
        int l = 1, r;
        for( int i=0; i<m; i++){
            r = post[i];
            ll sumaRango = acumm[r] - acumm[l-1];
            print( l,r, sumaRango);
            ans += abs( sumaRango );
            l = r+1;
        }
        // por si quedaron
        if( post[m-1] != n){
            r = n;
            l = post[m-1]+1;
            ll sumaRango = acumm[r] - acumm[l-1];
            print( l,r, sumaRango);
            ans += sumaRango ;
        }

        cout << ans << "\n";

    }

    
}
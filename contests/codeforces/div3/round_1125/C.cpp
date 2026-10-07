/*  
    * Contest: Codeforces Round 1125 (Div. 3)
    * URL: https://codeforces.com/contests/2275
    * Problem: C - Unrequited Love
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
    #define print(...) logger (#__VA_ARGS__,__VA_ARGS__)
#else
    bool debug = false;
    #define print(...)
#endif

#define DEBUG if(debug)
#define DEBUG1 DEBUG cout <<
#define DEBUG2 DEBUG1 "\n" << 
#define DEBUG3 DEBUG1 "\n";
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


// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int t; cin >> t;

    while(t--){
        int n; cin >> n;
        vi a(n); 


        for( int &x: a) cin >> x;
        // contamos cuantas valores diferentes hay
        map<int,int> cnt;
        vi vals;
        for( int i=0; i+4<n; i++){
            int v = a[i] + a[i+2] - a[i+4];
            cnt[v]++;
            DEBUG1 v << " ";
            if( cnt[v]== 1) vals.pb(v);
        }
        DEBUG3

        // contamos cuantas repeticiones tiene cada una
        map< int, int> repe;
        for( int i=0; i+4<n; i++){
            int v = a[i] + a[i+2] - a[i+4];
            for( int next :{2,4}){
                if( ! (i+next + 4  < n) ) continue;
                int other =  a[i+next] + a[i+next+2] - a[i+next+4];
                if( other == v ) repe[v]++;
            }
        }

        // vamos cuamulado la repsuesat
        ll ans = 0;
        for( int i=0; i<sz(vals) ; i++){
            int v = vals[i];
            ll apariciones = 1ll*cnt[v];
            ll repeticiones = 1ll*repe[v];
            ll parejas = apariciones * (apariciones-1) / (2ll);
            ll total = parejas - repeticiones;
            ans += total;
        }

        cout << ans << "\n";

    }

} 
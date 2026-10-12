/*  
    * Contest: 
    * URL: 
    * Problem: 

    * Topic: 
    * Algorithm: 
    * Complexity: 

    * Status: 
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

// g++-16 -DLOCAL -Wl,-stack_size,0x20000000 I.InversionInsight.cpp
// para cualquer n con x = 190 basta
// para n > =21 con 100 basta
// para n>=54 con MAXx = 22 nasta <-- NOS E cehjar bien 
const int MAXN = 500;
const int MAXK = 1e3;
const ll MAXREALK = 4e18;

ll dp[MAXN+1][MAXN+1];
ll maxkn[MAXN+1];

// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif
    

    ll maxKval = 0;
    
    int n; 
    n = MAXN;
    for( int i=1; i<=n; i++ ) dp[i][0] = 1;
    // for( int i=1; i<=n; i++ ) dp[i].pb(1);

    ll acum = 0;
    // llenar dp
    for( int i=2; i<=n ;i++){
        acum = 1;
        DEBUG cout << "n = " << i << " :\n";
        for( int k=1; k<= min( (i-1)*i/2 , MAXK ); k++){
            ll posans = dp[i][k-1] + dp[i-1][k];
            if( k- i >=0 ) posans -= dp[i-1][k-i];
            
            // dp[i].pb( posans );
            dp[i][k] = posans;
            
            acum += posans;
            
            maxkn[i] = k;
            DEBUG1 dp[i][k] << "  "; 
            if( acum > MAXREALK ){  
                break;
            }

            
        }
        DEBUG3;
        DEBUG cout << " -> " <<  i << " " << maxkn[i] <<  " " << maxKval  << "\n";
        maxKval = max( maxKval, maxkn[i]);
    }

    print( maxkn );
    // DEBUG{
    // for( int i=1; i<=n; i++){
    //     cout << i << " :\n";
    //     for( int k=0; k<= (i-1)*i/2; k++) cout << dp[i][k] << " "; 
    //     DEBUG3;
    // }


}
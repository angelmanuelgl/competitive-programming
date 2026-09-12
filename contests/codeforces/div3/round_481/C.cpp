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


// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif


    #ifdef LOCAL
    int t; cin >> t;
    while(t--){
    #else

    #endif
    
    int n, m; cin >> n >>m;

    // romms in each dormitory
    vll a(n); for( ll &ai:a) cin >> ai;
    
    // letters
    vll b(m); for( ll &bi:b ) cin >> bi;
    

    ll acum = 0;
    set<ll> acumulados; acumulados.insert(0);
    map<ll,int> acumm2dormitory; acumm2dormitory[0] = 1;

    for( int i=0; i<n; i++){
        acum += a[i];

        acumulados.insert(-acum);
        acumm2dormitory[acum] = i+2;
    }

    for( int i=0; i<m; i++){
        auto ptr = acumulados.upper_bound( -b[i]);
        ll rooms_before_dormitory = (-1)*(*ptr);
        int dormitory_idx = acumm2dormitory[rooms_before_dormitory];

        ll room_idx = b[i] - rooms_before_dormitory;

        cout << dormitory_idx << " " << room_idx << "\n";
    }


    
    
    #ifdef LOCAL
    }
    #else

    #endif
}
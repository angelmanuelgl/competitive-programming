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

    int n, k, ri; cin >>  n >> k;

    vi r;
    vpii r_sort;
    for( int i=0; i<n; i++){
        cin >> ri;
        r_sort.pb( {ri,i} ); 
        r.pb( ri);
    }
    sort( all(r_sort) );

    // para cada elemento contar cuantos menores hay
    vi contador(n,0);
    int cnt = 0;
    for( int i=1; i<n; i++){
        int r_act = r_sort[i].fi;
        int idx_act = r_sort[i].se;
        int r_ant = r_sort[i-1].fi;

        if( r_ant <  r_act) cnt = i;
        
        contador[ idx_act ] = cnt;

    }

    map<int,int> descontar;
    int x,y;
    for( int i=0; i<k; i++){
        cin >> x >> y;
        x--; y--;
        // ninguno puede ser mentor de ninguno
        if( r[x] == r[y] ) continue;
        
        //  x o y es el mentor
        int mentor;
        if( r[x] > r[y]  ) mentor = x;
        else mentor = y;
        
        if( !descontar.count( mentor ) ) descontar[mentor] = 1;
        else descontar[ mentor ]++;
    }

    print(contador);
    print(descontar);

    for( int i=0; i<n; i++){
        int ans = contador[i];
        if( descontar.count(i) )
            ans -= descontar[i];

        cout << ans << " \n"[i==n-1];
    }


    #ifdef LOCAL
    }
    #else

    #endif
    
}
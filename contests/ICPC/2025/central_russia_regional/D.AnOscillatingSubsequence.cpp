/*  
    * Contest: ICPC Central Russia Regional Contest, 2025
    * URL: https://codeforces.com/gym/106189
    * Problem: D. An oscillating subsequence
    * Topic: 
    * Algorithm: 
    * Complexity: 
    * Status: 
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- --- --- --- Type Aliases --- --- --- ---
typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

// --- --- --- --- Short Macros --- --- --- ---
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define rep(i,a,b) for( int i=a; i< (b); ++i )

const int MOD = 1e9 + 7;

// --- --- --- --- LOGGER SETUP --- --- --- --- 
// Daclare before   
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream &os, const C &v);
// Overload for std::pair
template<typename A, typename B>
ostream& operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.fi << ", " << p.se << ')';
}
// Overload for Containers (excluding std::string) SFINAE
template<typename C, typename T>
ostream& operator<<(ostream &os, const C &v) {
    string sep;
    for(const T &x : v) os << sep << x, sep = " ";
    return os;
}
// Colors
constexpr const char *RST="\033[0m", *GREEN="\033[1;32m", 
*YELLOW="\033[1;33m",*CYAN="\033[1;36m",*RED="\033[1;31m";
// Logger Function
template<typename ...Args>
void logger(const char* col, string vars, Args&&... values){
    cerr << col << '[' << vars << "] =" << RST;
    ((cerr << " [" << values << ']'), ...);
    cerr << '\n';
}

// --- --- --- --- DEBUGGER SETUP --- --- --- ---    
#ifdef LOCAL
    #define DEBUG   if (true)
    #define SALTO   (cerr << '\n')  
    #define LOG(...)   logger("", #__VA_ARGS__, __VA_ARGS__)
    #define LOGC(c, ...) logger(c, #__VA_ARGS__, __VA_ARGS__)    
    #define COL(c, ...) (cerr << c << __VA_ARGS__ << RST << '\n')
#else
    #define DEBUG   if (false) 
    #define SALTO
    #define LOG(...)
    #define LOGC(...)
    #define COL(...)
#endif

// // // // // // // // // // // // // // // // // // // // //

#define lsb(S) ((S)&(-S))
struct  fenwick_tree
{
    int n;
    vpii BIT;
    fenwick_tree( int _n) : n(_n){
        BIT.resize(n+1,{0,-1});
    }
    void add( int pos, pii x){
        while(pos<=n){
            BIT[pos] = max(BIT[pos],x);
            pos += lsb(pos);
        }
    }
    
    pii maxi( int pos){
        if( pos <=0 ) return {0,-1};
        pii res = {0,-1};
        while( pos ){
            res = max( res, BIT[pos]);
            pos -= lsb(pos);
        }
        return res;
    }
};
 
 
#define CRECE 0
#define DECRECE 1
 


// for f in {a..n}; do cp template.cpp $f.cpp; done
// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #endif

        int n; cin >> n;
 
    vi a(n+1);
    rep( i, 1, n+1){
        cin >> a[i];
    }
 
    vi vals = a;
    sort(all(vals));
    vals.erase( unique(all(vals)), vals.end() );
 
    vi valsr = vals;
    reverse( all(valsr) );
    int m = sz(vals);
 
 
    map<int,int> valr_2_idx;
    map<int,int> val_2_idx;
    rep(i, 0,sz(vals)){
        val_2_idx[ vals[i]  ] = i+1;
    }
    rep(i, 0,sz(vals)){
        valr_2_idx[ valsr[i] ] = i+1;
    }
    
 
    // auxsiliares
    fenwick_tree left(m+2), right(m+2);
 
    // dp
    pii dp[n+2][2];
 
    // para el primero simepre se peude
    // dp[0][ ] = 0;
    pii ans = {0,-1};
    rep( i, 1, n+1){
        int idx = val_2_idx[ a[i] ];
        int idxr = valr_2_idx[ a[i] ];
 
 
        // dp[i][CRECE] = left.maxi(idx-1) + 1;
        // dp[i][DECRECE]=  right.maxi(idxr-1) + 1;
 
        dp[i][CRECE] = left.maxi(idx-1);
        dp[i][DECRECE]=  right.maxi(idxr-1);
        dp[i][CRECE].fi +=1;
        dp[i][DECRECE].fi +=1;
 
        pii posans = max( dp[i][CRECE],  dp[i][DECRECE] );
        ans = max( ans, posans );
       
        left.add( idx,  {dp[i][DECRECE].fi, i} );
        right.add( idxr,  {dp[i][CRECE].fi, i}  );
    
    }
    
    if( ans.fi<3){
        cout << "0\n";
        return 0;
    }

    int tipo = -1, ultimo = - 1;
    rep(j, 0, 2)rep( i, 1, n+1){
        if( tipo!=-1 ) break;
        if( dp[i][j] == ans){
            tipo = j;
            ultimo = i;
            break;
        }
    }

    LOG( tipo, ultimo);


    vi anss;
    while( ultimo != -1){
        anss.pb(ultimo);
        ultimo = dp[ultimo][tipo].se;
        tipo = !tipo;
        LOG(ultimo, tipo);
    }
    
    reverse(all(anss));
    cout << ans.fi << "\n";
    
    rep( i, 0, ans.fi){
        cout << anss[i] -1 << " \n"[ i == ans.fi-1];
    }

 
    

}

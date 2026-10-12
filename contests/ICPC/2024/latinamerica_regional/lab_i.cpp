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

struct per{
    int inv;
    vi arr;
    bool const operator<(const per &other) {
        if( inv < other.inv  ) return true;
        if( inv > other.inv ) return false;
        for( int i=0; i<sz(arr); i++){
            if( arr[i] < other.arr[i] ) return true;
            if( arr[i] > other.arr[i] ) return false;
        }
        // iguales no s eucmple  this < other
        return false;
    }

};

int inversiones( vi arr){
    int n =sz(arr);
    int ans = 0;
    for( int i=0; i<n; i++){
    for( int j=i+1; j<n; j++){
        // i < j
        if( arr[j] < arr[i]) ans ++;
    }}
    return ans;
}

int per_inv( int n, int k){
    if( k == 0 ) return 1;
    if( k == 1) return n-1;
    if( k== 2) return (n-1)*(n-2)/2 + n-2;
    if( k== 3) return (n-3) + (n-2)* (n-2)  + (n-1)*(n-2)*(n-3)/6;
    return -1;
}

// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif
    
    

    int N; cin >> N;
    cout << "CORRECT:\n";
   for( int n=1; n<=N; n++){

    vi arr(n); iota(all(arr),1);

    vector<per> ans;
    vi cntinv( (n-1)*(n)/2 +1, 0 );
    do{
        // print( arr);
        int inv = inversiones(arr);
        cntinv[inv] ++;
        ans.push_back( {inv, arr});
        next_permutation( all(arr) );    
    } 
    while(( !is_sorted( all(arr) ) ));
    DEBUG3 DEBUG3
    
    sort(all(ans));
    int ant = -1;
    for( int i=0; i<sz(ans); i++){
        // if(  ans[i].inv  != ant ) cout << "\n";
        // cout << i+1 << "\t: " << ans[i].inv << "  " << ans[i].arr << "\n";
        ant =  ans[i].inv ;
    }  

    cout << n << ": \n";
    for( int i=0; i<sz(cntinv); i++){
        // cout << i << "    "  <<     cntinv[i] << " ";
        cout << cntinv[i] << " ";
        // cout << i << " -> " << per_inv(n,i) << "\n";
        // if( i > 5) break;
    }
    cout << "\n";
    }
}
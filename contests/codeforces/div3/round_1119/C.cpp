/*  
    * Contest: Codeforces Round 1119 (Div. 3)  (ONLINE)
    * URL: https://codeforces.com/contests/2259
    * Problem: 

    * Topic: 
    * Algorithm: 
    * Complexity: 

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

    while( t-- ){

        int n; cin >> n;
        vi arr(n);
        for( int &a: arr) cin >> a;

        bool thereis1 = false;
        for( int i=0; i<n; i++){
            if( arr[i] == 1){
                thereis1 = true;
                break;
            }
            if( arr[i] == -1){
                if( thereis1 ) arr[i] =0;
                else{
                    arr[i] = 1;
                    break;
                }
            }
        }

        thereis1 = false;
        for( int i=n-1; i>=0; i--){
            if( arr[i] == 1){
                thereis1 = true;
                break;
            }

            if( arr[i] == -1){
                if( thereis1 ) arr[i] =0;
                else{
                    arr[i] = 1;
                    break;
                }
            }
        }

        for( int &a : arr) if( a== -1) a=0;

        for( int i=0; i<n; i++){
            cout << arr[i] << " \n"[i == n-1];
        }
        
    }

    
}
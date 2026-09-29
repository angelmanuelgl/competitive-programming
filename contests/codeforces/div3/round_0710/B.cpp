/*  
    * Contest: Codeforces Round 710 (Div. 3)
    * URL: https://codeforces.com/contest/1506/countdown
    * Problem: B. Partial Replacement
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
        int n,k; cin >> n >> k;
        string s ; cin >> s;

        // contmos cuantos hay y entoncotramos el ultimo y primero
        int cntx = 0;
        int first = -1;
        int last = -1;
        for( int i=0; i<n; i++){
            if( s[i] == '*'  ) cntx++;
            if( first == -1 && s[i] =='*'){
                first = i;
            }
        }

        for( int i=n-1; i>=0; i--){
            if( last == -1 && s[i] == '*'){
                last = i;
            }
        }

        // casos especiales
        if( cntx <= 2){
            cout << cntx << "\n";
            continue;
        }

        // llenado gredy
        int puestos = 2;
        int last_x = first;
        int last_asteristo = -1;
        for( int i=0; i<n; i++){
            if( i<= first ) continue;
            if( i>= last ) continue;
            // ya pasammos el primer * que ahi va un x

            if( s[i] == '*'){
               last_asteristo = i;
            }
           
            // sin la distancia entre x es mayor a k
            // tenemos que poner uno en el utlimo * que vimos
            int dist = i - last_x + 1;
            if( dist > k){      
                s[ last_asteristo ] =  'x';
                last_x = last_asteristo;
                puestos++;
            }
            
          
        }

        cout << puestos << "\n";

    }
}
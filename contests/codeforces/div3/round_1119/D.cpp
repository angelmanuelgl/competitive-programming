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

        // int n; cin >>  n;
        // vi a(n), uniq;
        // map<int,bool> check;
        // for( int & ai : a){
        //     cin >> ai;
        //     if( !check.count(ai)){
        //         checl[ai] = true;
        //         uniq.pb(ai);
        //     }
        // }

        // int m = sz(uniq);
        // sort( all(uniq) );
        // map<int, int> ai_2_idx;
        // for( int i=0; i< m; i++){
        //     ai_2_idx[ uniq[i]  ] = i;
        // }

        // // contar cuantas hay
        // vi cnt(m,0);
        // for( int i=0; i<n; i++){
        //     cnt[ ai_2_idx[ a[i] ]  ]++;
        // }

        int n; cin >> n;
        vi a(n);
        int cnt_cero = 0, cnt_no_cero= 0;

        
        for( int & ai : a){
            cin >> ai;
            if( !ai ) cnt_cero++;
            else cnt_no_cero++;
        }


        // los tres MEX son necesariamente 0
        if( cnt_cero == 0){
            cout << "YES\n";
            for( int i =0 ; i<n; i++){
                cout << "A";
            }
            cout << "\n";
            continue;
        }
        // dos MEX son necesariamente 0 y uno es algo mayor igual  a 1
        if( cnt_cero == 1 ){
            cout << "NO\n";
            continue;
        }

        // si tenemos dos ceros simepre podemos hacer respuesta
        bool ceroAcheck = false;
        cout << "YES\n";
        for( int i=0; i<n; i++){
            if( a[i] == 0 ){

                if( ceroAcheck  ) cout << "B";
                else{
                    cout << "A";
                    ceroAcheck = true;
                }
            } 
            else{
                cout << "C";
            }
           
        }
          cout << "\n";

        


        
    }

    
}
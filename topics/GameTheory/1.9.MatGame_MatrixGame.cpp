/*  
    * Contest:  Game theory training sessions | CS
    * URL: https://www.spoj.com/problems/MATGAME/
    * Problem: MATGAME - Matrix Game

    * Topic: Game Theory | Game Theory | Grundy Numbers
    * Algorithm: - O(M) calculate each Grundy number for each 1,..,N games
                 - are there N positions
                    - for calculate GN in O(M) for v1,v2,...,v_{m-1}, v_{m}
                    - we calculate GN[  v_{m} ] then GN[ v_{m-1}, v_{m}  ], then ...
                    - from right to left
                 - Calculate the XOR of all elements
                 - if it's zero, i have winning move
                 - if it's non-zero, i do not have winning move
                

    * Note: I was redding de comments because i didn't undertand the
                 test cases and I read "Hint: calculate your grundy numbers based on the current number and the number to the right of it"
                  Sice I was already was calculate the Grundy numbers, i didn't pay mucho attention to it
                 but later, i was trying to simplify the calculations  of Grundy numbers and I saw
                 0XY <- 1XY <- 2XY <- 3XY <- ... <- K-1 XY <- KXY <- K+1 XY <= K+2 XY <- ...
                 where K is grundy[ XY ] then I thought "aha, that's what the hint was for"
    * Complexity: O( M * N )

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






int calculate_GN( vi & v ){
    // quitar 0s
    vi v2;
    for(int x : v ) if(x) v2.pb(x);
    swap( v,v2);

    // estado final
    if( !sz(v) ) return 0;

    print(v);
    // XYZ
    int n = sz(v);
    // grundy[Z]
    int grundyAnterior = -1;
    int grundyActual = v[n-1];
    for( int i=n-2; i>=0 ; i--){
        swap( grundyActual, grundyAnterior);

        // calcular grundy YZ conociendo grundy Z
        int Y = v[i];
        print(Y, grundyActual, grundyAnterior);
        if( Y <= grundyAnterior ) grundyActual = Y-1;
        else if( Y > grundyAnterior ) grundyActual = Y;

        print(Y, grundyActual, grundyAnterior);
        
    }
    return grundyActual;
}


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
        int n,m,x; cin >> n >> m;

        print(n,m);
        int elXor = 0;
        for( int i=0; i<n; i++){
            vi thisgame;
            for( int j=0; j<m; j++){
                cin >> x;
                if(x) thisgame.pb(x);
                print(x);
            }
            int thisGrundyNumber = calculate_GN( thisgame );
            elXor ^= thisGrundyNumber;
            
            print(thisgame);
            print( thisGrundyNumber );
        }

        cout << ( (elXor)?"FIRST\n":"SECOND\n");
        DEBUG cout << "\n\n";
    }
}
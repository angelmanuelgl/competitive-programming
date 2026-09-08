/*  
    * Contest: Game theory training sessions| CS
    * URL: codeforces.com/contest/1943/problem/A
    * Problem:  A. MEX Game 1

    * Topic: Game Teory
    * Algorithm:  We iterate through the frequency arrar, looking for
                  - 1er element with value of 0
                  - 2nd element with vale of 1
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
        const int MAXN = 11;
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
        const int MAXN = 200005;
    #endif
    

     int t;  cin >> t;

    while( t-- ){
        int n; cin >> n;
        vi a(n), cnt(MAXN, 0);
        for( int & ai: a){ 
            cin >> ai;
            cnt[ai]++;
        }
        print(cnt);


        // solo se podra hasta que ya hayan consecutivos
        int consecutivos = 0;
        while(  cnt[consecutivos]  >= 1 ) consecutivos++;


        // Alice siempre peude agarrar los que tengan 2 o mas repetio
        // si solo tiene un repetido, alice solo puede agarrar uno de esos
        // en su primer turno
        // entonces llegar ahasta justo el segundo elemnto con solo 1 reptido
        int contador_de_1 = 0;
        int idx = -1;
        while( contador_de_1 <2 && idx <=consecutivos ) 
            contador_de_1 += ( cnt[++idx] == 1 );
        

        // la respuesta es el tope que pase antes
        int maxMex = min(consecutivos, idx);
        cout << maxMex << "\n";

    }
    
}
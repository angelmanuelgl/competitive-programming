/*  
    * Contest: Codeforces Round 713 (Div. 3)
    * URL: https://codeforces.com/contest/1512
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


int to_int( char c){
    if( c== '0') return 0;
    if( c== '1') return 1;
    return 2;
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

    
    int t; cin >> t;

    print(t);
    while(t--){
        DEBUG1 "\n\n- - - -- - - -- - - - - - \n";
        int a, b;  cin >> a >> b;
        string s; cin >> s;

        print( s,a,b);

        // rellenar los que son obligatorido
        int n = sz(s);
        bool posible = true;
        for( int i=0 ; i< (n+1)/2; i++){
         
                
            if( s[i] == '?' )
                s[i] = s[n-1-i];
            else if(s[n-1-i] == '?') 
                s[n-1-i] = s[i];

            else if( s[i] != s[n-1-i] ){
                posible = false;
            }
        }


        DEBUG1 s << "\n";
        // contar
        vi cnt(3,0);
        for( char c: s) cnt[ to_int(c) ]++;


        if( cnt[0] > a ) posible = false;
        if( cnt[1] > b ) posible = false;

        print(cnt);

        if( !posible){
            cout << "-1\n"; 
            continue;
        }

        // ver cuantos huecos psoibles
        int huecos = cnt[2];
        int new_a = a - cnt[0];
        int new_b = b - cnt[1];


        print( new_a, new_b);

        // si los dos son congruentes a 1 // no s epeude
        // porque sioempre se agrega 2 al conteno, excepto en uno
        if( new_a%2 == 1 && new_b%2 == 1){
            cout << "-1\n"; continue;
        }


        // si a o b alguno es impar pero tenemos una catidad par de huevos
        if( (new_a%2 == 1 || new_b%2 == 1)  && huecos%2==0 ){
             cout << "-1\n"; continue;
        }

        

      

        // sabemos que es posible llenarlo s
        

        // vemos quien es le impar
        int mid = -1;
        if(  new_a%2 == 1 ){ mid = 0, new_a--; s[ n/2 ] = '0'; }
        if(  new_b%2 == 1 ){ mid = 1, new_b--; s[ n/2 ] = '1' ; }

        print( new_a, new_b);

          DEBUG1 s << "\n";

        // las cantidades que queremos llenar son ambas pares
        for( int i=0 ; i<=n/2; i++){
            if( s[i] != '?') continue;  

            if( new_a > 0 ){
                s[i] = s[n-1-i] = '0';
                new_a-=2;
            }else{
                s[i] = s[n-1-i] = '1';
                  new_a-=2;
            }

        }

        cout << s << "\n";


    }
}
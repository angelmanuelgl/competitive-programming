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


int is_the_max( vi &b, int id_max, int maxi){

    ll sum = 0;
    for( int i=0; i< sz(b); i++ ){
        if( i == id_max) continue;
        sum += 1ll* b[i];
    }

    // vemos si hay un elemnto x tal que la suma de los demas es el maximo
    for( int i=0; i< sz(b); i++){
        if( i == id_max) continue;

        ll this_sum = sum - b[i];
        if( this_sum == maxi ) return i;
    }

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

    
    int t; cin >> t;


    while(t--){
        int n; cin >> n;
        vi b(n+2); for( int &x: b) cin >> x;


        auto it= max_element(all(b));
        int maxi = *it;
        int id_max = distance(b.begin(), it);
        print( maxi, id_max, b[id_max]  );

        int i_x = is_the_max( b, id_max, maxi  );

        int x;

        // si si ya sabemos el maximo, y quien es x
        if( i_x != -1){
            x = i_x;
        }
        // maxi no es le maximo // entonces el maximo es x
        // el maximo es el seugno amximo
        if( i_x == -1){
            // tomamos x y lo quitamos
            x =  b[id_max];
            i_x = id_max;
            b[id_max] = 0;

            // tomamos el maximo verdadero
            it= max_element(all(b));
            maxi = *it;
            id_max = distance(b.begin(), it);

            print( maxi, id_max, b[id_max]  );

            // se debe cumplir que la suma de todos
            // excetpo el maxi y el x es el 
            
            ll sum = 0;
            for( int i=0; i< sz(b); i++ ){
                if( i == id_max || i == i_x) continue;
                sum += 1ll* b[i];
            }

            if( sum !=  maxi ){
                cout << "-1\n"; continue;
            }

  
        }
        // los quitmaos 
        b[i_x] = 0;
        b[id_max] = 0;

        print( b) ;
        for( int i=0; i<n+2; i++){
            if( !b[i] ) continue;
            cout << b[i] << " \n"[i==n+1];
        }
        if( b[n+1] == 0  ) cout << "\n";
      
    }
}
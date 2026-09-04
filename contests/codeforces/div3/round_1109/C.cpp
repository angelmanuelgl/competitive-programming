/*  
    * Contest: Codeforces Round 1109 (Div. 3)
    * URL: https://codeforces.com/contest/2244
    * Problem: 

    * Topic: Simulacion
    * Algorithm: Connected Componets, bukets, sorting
    * Complexity: O(Nlog N)

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

// const int MAXN = 7;
const int MAXN = 200005;

int n;
vi xy(2);


// isSwappable[i] = isSwappable[j] => pdoemos swap(i,j) 
// ademas tienen un indice indicando a que componenrte contexa pertencen
vi isSwappable(MAXN);
void isSwappable_fill( int nodo, int repre){
    // o es -1 o es repre
    // no puede ser un valor disinto a repre
    // porque no peude se run valor distinto de repre?
    if( isSwappable[nodo] != -1 ) return;
    if( nodo < 0 || n <= nodo ) return;
    // marcarlo
    isSwappable[nodo] = repre;

    for( int sig=-1; sig<=1; sig+=2){
    for( int j=0; j<=1; j++){
        // a donde me puedo mover
        int mov = sig * xy[j];

        int pos =  nodo + mov;
        if( pos < 0 || pos >= n) continue;

        isSwappable_fill( pos, repre);
    }
    }
    
  
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

    while( t-- ){
        cin >> n >> xy[0] >>xy[1];
        vi arr(n);

        for( int & a: arr ) cin >> a;

        print(arr);
        print(xy);
        
        // rellenar con -1
        fill( isSwappable.begin() , isSwappable.begin()  + (n+2), -1 );

        print(isSwappable);

        int cnt_comp_conexas = 0;
        for( int i=0; i<n; i++){
            // ya esta en algun conjunto
            if( isSwappable[i] != -1) continue;
            //
            // isSwappable[i] = cnt_comp_conexas;
            isSwappable_fill(i, cnt_comp_conexas);

            cnt_comp_conexas++;
            DEBUG cout <<  i << ":\n";
            print(isSwappable);

        }
        print(isSwappable);
        

        

        // ordenamos todos los conjutnos que se peudan ordenar
        vector<int> comp_conexas [cnt_comp_conexas];

   

        for( int i=0; i<n; i++){
            int idx_comp_conexa = isSwappable[i];
            comp_conexas[idx_comp_conexa].pb( arr[i] );
        }


        for( int i=0; i<cnt_comp_conexas; i++){
            DEBUG cout << "la " << i << " -esima comp conx" <<"\n";
            print( comp_conexas[i] );

            sort( all(comp_conexas[i]) );

            print( comp_conexas[i] );
        }


        // vamos recreando el arreglo ordenado
        vi salida(n);

        vi idx_en_cc( cnt_comp_conexas, 0);

        print( idx_en_cc );

        for( int i=0; i<n; i++){
            int idx_cc = isSwappable[i];
            
            DEBUG cout <<  " i " << i << ", idx_cc: " << idx_cc;
            DEBUG cout <<  ",  i dx_en_cc " << idx_en_cc[idx_cc] << "\n";
            salida[i] = comp_conexas[idx_cc][ idx_en_cc[idx_cc] ];
            idx_en_cc[idx_cc]++;
        }

        print(salida);

        bool isPosible = true;

        for( int i=0; i<n; i++){
            if( salida[i] != i+1) isPosible = false;
        }

        if( isPosible ) cout << "YES\n";
        else cout << "NO\n";


        DEBUG cout << "\n";
    }


    
}
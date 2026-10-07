/*  
    * Contest: 2024-2025 ICPC Latin American Regional Programming Contest
    * URL: https://codeforces.com/gym/105505
    * Problem: E. Evereth Expedition

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


// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int n; cin >> n;
    vi a(n+1); 
    vi b, idxb_to_idxa;
    for(int i=1; i<=n; i++){
        cin >> a[i];
        if( a[i] ){ 
            b.pb(a[i]);    
            idxb_to_idxa.pb(i);
        }
    }
    print(a);


    // VERFICIAR SI CRECE Y LEUGO DECRECE
    
    bool decreciendo = false;
    int m = b.size();
    bool esposible = true;
    // si todos fueron inleibles
    if( m == 0 ){
        for( int i=1; i<=n; i++) cout << i << " \n"[i==n];
        return 0;
    }
    // tenemos almenos 1

    // suiponemos que simepr ecrece hasta que pase lo contrari
    for(int i=1; i<m; i++){
        // marcar en el primer decrecimiento
        if( b[i-1] > b[i] ) decreciendo = true;
        // si no respeta etapa de decreciemiento
        if( decreciendo && b[i-1] < b[i] ) esposible = false;
    }

    if( !esposible ){
        cout << "*\n";
        return 0;
    }


    // CONSTRUIR MAPEO

    // poner como 1 2 3 4 ... n-1 n n-1 .. 3 2 1
    vi mape(n+1);

    // nos dice que indice le corresponde
    vi decre_to_map(n+1);
    iota(all(mape),0 );
    for( int i=n-1; i>=1; i--){
        decre_to_map[i] = sz(mape); 
        mape.pb(i);
    } 
    int smap  = sz(mape);

    // MAPEAR
    print(mape);
    print(decre_to_map);

    vector<bool> esta_usado(n+1,false); // numeros
    vector<bool> used(2*n,false); // mapeo
    vector<int> creciendo(n+1,-1); //
    print(used);
    decreciendo = false;
    // el primero siempre esta en la etapa de creciendo
    used[ b[0]  ] = true;
    esta_usado[ b[0] ]  = true; 
    creciendo[ idxb_to_idxa[0] ] = 1;

    for(int i=1; i<m; i++){
        if( b[i-1] > b[i] ){
            decreciendo = true;      
        }
        esta_usado[ b[i] ] = true;
        creciendo[ idxb_to_idxa[i] ] = (decreciendo)?0:1;

        // creciendo
        if( !decreciendo ){
            used[ b[i]  ] = true;
        }
        if( decreciendo ){
            used[ decre_to_map[ b[i] ] ] = true;
        }
    }

    print(mape);
    print(used);
    print(creciendo);



    int idx = 1;
    vi ans = a;
    for( int i=1; i<=n; i++){

        print( i, idx, ans[i]);
        print( ans );
        print( esta_usado );
        if( ans[i] == 0 ){
            while( idx < smap  && esta_usado[ mape[idx] ]  ) idx++;
            
            // si no enocntramos ninguno que no este usado no es posible
            if( ( idx == smap-1 && esta_usado[ mape[idx] ]) || idx >=smap ){
                cout << "*\n";
                return 0;
            }

            ans[i] = mape[idx];
            esta_usado[ mape[idx] ] = true;
            idx++;
        }else{
            if( creciendo[ i ]  ) idx = ans[i]+1;
            else idx = decre_to_map[ ans[i]] +1;
            print( creciendo[ ans[i] ], idx   );
        }
        print( i, ans);
    }
    print(a);
    print(ans);

    // si de csualdiad me deje alguno sinusar
    for( int i=1; i<= n; i++){
        if( !esta_usado[ i ] ){
            cout << "*\n";
            return 0; 
        }
    }

    // ve rsi cumple crece y decrece 
    bool respuesta_correcta = true;
    bool ans_decreciendo = false;
     // suiponemos que simepr ecrece hasta que pase lo contrari
    for(int i=1; i<=n; i++){
        // marcar en el primer decrecimiento
        if( ans[i-1] > ans[i] ) ans_decreciendo = true;
        // si no respeta etapa de decreciemiento
        if( ans_decreciendo && ans[i-1] < ans[i] ) respuesta_correcta = false;
    }

    if( !respuesta_correcta ){
        cout << "*\n";
        return 0;
    }


    for( int i=1; i<= n; i++){
        cout << ans[i] << " \n"[i==n];
    }
}
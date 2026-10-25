/*  
    * Contest: 2023-2024 ACM-ICPC Latin American Regional Programming Contest
    * URL: https://codeforces.com/gym/104736
    * Problem: K. Keen on Order
    * Topic: bitmask | bitset | bitmask | DP | dp on multiples
    * Complexity: O( 2^K * N   + N^2) | k<25
    * Status: ACCEPTED
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- --- --- --- Type Aliases --- --- --- ---
typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

// --- --- --- --- Short Macros --- --- --- ---
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define rep(i,a,b) for( int i=a; i< (b); ++i )

const int MOD = 1e9 + 7;

// --- --- --- --- LOGGER SETUP --- --- --- --- 
// Daclare before   
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream &os, const C &v);
// Overload for std::pair
template<typename A, typename B>
ostream& operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.fi << ", " << p.se << ')';
}
// Overload for Containers (excluding std::string) SFINAE
template<typename C, typename T>
ostream& operator<<(ostream &os, const C &v) {
    string sep;
    for(const T &x : v) os << sep << x, sep = " ";
    return os;
}
// Colors
constexpr const char *RST="\033[0m", *GREEN="\033[1;32m", 
*YELLOW="\033[1;33m",*CYAN="\033[1;36m",*RED="\033[1;31m";
// Logger Function
template<typename ...Args>
void logger(const char* col, string vars, Args&&... values){
    cerr << col << '[' << vars << "] =" << RST;
    ((cerr << " [" << values << ']'), ...);
    cerr << '\n';
}

// --- --- --- --- DEBUGGER SETUP --- --- --- ---    
#ifdef LOCAL
    #define DEBUG   if (true)
    #define SALTO   (cerr << '\n')  
    #define LOG(...)   logger("", #__VA_ARGS__, __VA_ARGS__)
    #define LOGC(c, ...) logger(c, #__VA_ARGS__, __VA_ARGS__)    
    #define COL(c, ...) (cerr << c << __VA_ARGS__ << RST << '\n')
#else
    #define DEBUG   if (false) 
    #define SALTO
    #define LOG(...)
    #define LOGC(...)
    #define COL(...)
#endif


#define is_on(S,j) (S & (1<<(j)) )
#define clear_bit(S,j) (S & ~(1<<(j)) )
#define clear_lsb(S) ( (S) & (S-1))

#define INF 1000
// // // // // // // // // // // // // // // // // // // // //

bool todos( int k, vi &aparece, vi & usados ){
    rep( i , 1, k+1 ){
        if( usados[i] ) continue;
        if( !aparece[i] ) return false;
    }
    // si aparecieron todos los que deben aparecer
    return true;
}



// for f in {a..n}; do cp template.cpp $f.cpp; done
// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #endif
    

    int n,k;
    cin >> n >> k;

    vi v(n); for( int &x:v) cin >> x;


    /* 
       --- --- --- --- VER CUANDO NO ES POSIBLE --- --- --- ---
       esto acota a k
    */

    // para k : k(k+1)/2 > n no se puede
    LOG(v);
    
    // O ( N^2 )
    vi aparece(k+1,0);
    vi usados(k+1,0);
    vi ans;
    rep( i, 0, n){
        LOG( i, aparece, ans, usados);
        // si es la primera vez que lo vemos despues del reseteo
        aparece[ v[i] ]++;

        // O(n) - > en totoal O( n^2 )
        bool yatodos = todos(k, aparece, usados);

        // la primera vez que aparecen todos
        // O(n * k n/k) = O(n^2)
        if( yatodos ){
            COL(YELLOW, "reseteo");
            // nos tomamos el utlimo
            ans.pb( v[i] );
            usados[ v[i] ] = true;

            // resetear
            fill( all(aparece), 0);
        }

        LOG( i, aparece, ans, usados);
        SALTO;
    }
    
    LOG("agregados", ans);

    

    // si llegamos al final y nos quedaron elementos
    if( sz(ans) < k  ){
        // poner los que no se usaron
        rep(i, 1, k+1){
            if( !usados[i] ) ans.pb(i);
        }
        LOG(ans);
        rep(i, 0, k){
            cout << ans[i] << " \n"[i==k-1];
        }
        return 0;
    }

    COL(GREEN, "\n\npaso la primer prueba");

    // AHORA APARTIR DE AHORA K < 25
    
    /* 
       --- --- --- --- PRECALCULO --- --- --- ---
    */
    
    
    // siguiente[x][i] = el primer indice del primer valor x en [i,..,n-1]
    //                  

    // O( N K )
    vvi siguiente( k+1, vi(n+1,INF) );
    rep(x , 1, k+1){
        // la sigueinte aparicion de x en n,n-1]
        siguiente[x][n] = INF;

        // rellenamos desde atras
        for( int i=n-1; i>=0; i--){

            siguiente[x][i] = siguiente[x][i+1];
            // si aparece en [i,..,n-1]
            if( v[i] == x ) siguiente[x][i] = i;
        }
    }


    rep(x, 1, k+1){
        LOG( x, siguiente[x]  );
    }

    /* 
       --- --- --- --- DP on MULTIPLOS --- --- --- ---    
    */

    // ahora hacemos nuestra dp
    int MAXS = (1<<k); // 2^k
    int FILL = MAXS-1;
    vi dp_indice(MAXS, -2);
    vi dp_who(MAXS,-1);

    // dp[ s ] = el indice mas chico tal que [0,...,i] cumple que tiene todas las 
    // permutaicones de los elemntos de s

    // LOG( bitset<6>(MAXS)  );
    // LOG( bitset<6>(FILL)  );

    SALTO; SALTO;
    dp_indice[0] = -1; // el vacio
    
    rep(s, 1, MAXS){
        //provamos poner cada elemnto de s al final
        LOGC(CYAN,  bitset<6>(s));

        // provar poner dada valor i al final // solo que i+1
        // proque i va de 0 a k-1, y lso numeros van de 1 a ks
        rep(i,0,k){
            int val = i+1;
            if( !is_on(s,i) ) continue;
            
            int z = clear_bit(s,i); // z = s / { vi }
            int acaba_en = dp_indice[z];
            
            int poner_este = INF;
            if( acaba_en+1 <= n  ){
                poner_este = siguiente[ val ][ acaba_en + 1];
                LOG("if", val , acaba_en + 1, poner_este);
            }
           
            if( poner_este > dp_indice[s] ){
                dp_indice[s] = poner_este;
                dp_who[s] = val; 
            }
            LOG(  bitset<6>(z) , dp_indice[z], poner_este );
        
        }
        LOG( bitset<6>(s), dp_indice[s],dp_who[s] );

        SALTO; SALTO;
    }

    if( dp_indice[FILL] <= n){
        cout << "*\n"; return 0;
    }

    COL(RED, "falta recosnutirr el arreglo que no aparec");
    LOG( n,k, v);
    SALTO; SALTO;


    /* 
       --- --- --- --- DAR RESPUESTA --- --- --- ---
       - verificar si para toda permutacion se cumple que esta en el arreglo
       - o construir una que no este
    */
    
    // bsucamos el subconjunto mas chico que no tiene una permutaicon
    int s= 1;
    while( dp_indice[s] < INF ){
        s++;
    }
    LOG( bitset<6>(s), dp_indice[s], dp_who[s]);
    

    vi usados_per(k+1, 0);
    vi per;
    // agregamos cualqueir permutaiocn de s dejando dp_who[s] al final
    int z = s;
    do{
        int aqui_falla = dp_who[z];
        per.pb( aqui_falla );
        z = clear_bit(z, aqui_falla-1);
        usados_per[aqui_falla]++;
    }
    while( z );
    
    LOG( per,usados);

    reverse( all(per) );
    

    // agregamos el resto
    rep( val, 1, k+1){
        if( usados_per[val]) continue;
        per.pb(val);
    }
    LOG( per, usados_per);


    rep(i, 0, k){
        cout << per[i] << " \n"[i==k-1];
    }
    

}
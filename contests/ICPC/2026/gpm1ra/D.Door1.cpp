/*  
    * Contest: 2026 ICPC Gran Premio de Mexico 1ra Fecha
    * URL: https://codeforces.com/gym/106495
    * Problem: D. Door 1

    * Topic: Probability | DP 
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


#define MAXN 505
#define MAXK 14 // maxBaterias
#define MAXH 14 // maxHambre
#define GETMAX(a,b) a = max(a,(b))

// info
int horasPorSobrevivir, maxBaterias, iniBaterias, maxHambre;
double pBateria[MAXN], pComida[MAXN], pEnvenenarse[MAXN], pFerretLight[MAXN];

// dp
/* dp[i,s,h,g] = maxima probabilidad de sobrevivir desde el inicio de la hora i hasta el final,
               con s baterias, han pasado h horas sin comer y g apariciones giganteFerret
*/
double dp[MAXN][MAXK][MAXH][MAXN]; 
bool dpcheck[MAXN][MAXK][MAXH][MAXN]; // inicializado con false por defecto


double dpr( int i, int s, int h, int g ){
    // si encontramos linternas y ya estabamos llenos
    if( s > maxBaterias ) s = maxBaterias;

    //  --- --- --- casos bases  --- --- -- 
    // si tenemos menos de 0 linternas seguro es porque venimos de un light ferret 
    // debimos morrir 
    if( s < 0 ) return 0.0;
    
 

    // si estuvimos mucho timepo sin comer
    if( h >= maxHambre ) return 0.0;
 
    // si ya sobrevivimos las horas necesarias, la probabilidad de sobrevivir es 1
    if( i > horasPorSobrevivir  ) return 1.0;

   
    // --- --- --- ya calculado  --- --- ---
    // regresar  
    if( dpcheck[i][s][h][g] ) return dp[i][s][h][g];


    // --- --- ---  calcular dp[i][s][h][g] --- --- --- 

    // --- --- probabilidades en el momento i --- --- 
    double pBat = pBateria[i];
    double pNoBat = 1.0 -pBateria[i];

    double pCom = pComida[i];
    double pNoCom = 1.0 -pComida[i];

    double pNoEnv = 1.0 -pEnvenenarse[i];

    double pComer = pCom *  pNoEnv;

    double pLF = pFerretLight[i];
    double pNoLF = 1.0 -pFerretLight[i];

    int pVivirLF = (s>=2)? 1 : 0;

    // probabilidad de que aparezca giganteFerret en la hora i
    // dado que han aparecido g veces en las i-1 horas anteriores
    // p = ( g + 1 )/ ( (i-1) + 2  )
    double pGF =  ( 1.0 + g ) / ( 1.0 +i ); 
    double pNoGF = 1.0 - pGF;  


    // --- --- revisar cada opcoon --- --- 
    dp[i][s][h][g] = 0.0;

    // --- ---  OPCION 1 --- --- 
    // --- --- esconderse -- ---
    double p_vivir_si_me_escondo = 0;
    // aparecio el gigant Ferret
    p_vivir_si_me_escondo += pGF * dpr(i+1, s, h+1, g+1); 
    // no aparecio el gigant Ferret
    p_vivir_si_me_escondo += pNoGF * dpr(i+1, s, h+1, g); 

    // si es mejor opcion, ent actualizar
    GETMAX( dp[i][s][h][g], p_vivir_si_me_escondo);


    // --- ---  OPCION 2  --- --- 
    // --- --- buscar baterias --- -- 
    double p_vivir_salir_por_baterias = 0.0;
    // no aparece el gigant ferret (1-p)

    // aparece el light ferrer -2 // encuentro bateria +1
    p_vivir_salir_por_baterias += pNoGF * pLF*pVivirLF* pBat* dpr(i+1,s-1,h+1,g);
    // aparece el light ferrer -2 // no encuentro bateria +0
    p_vivir_salir_por_baterias += pNoGF * pLF*pVivirLF* pNoBat* dpr(i+1,s-2,h+1,g);
    // no aparece el light ferrer -0 // encuentro bateria +1
    p_vivir_salir_por_baterias += pNoGF * pNoLF* pBat* dpr(i+1,s+1,h+1,g);
    // no aparece el light ferrer -0 // encuentro bateria +0
    p_vivir_salir_por_baterias += pNoGF * pNoLF* pNoBat* dpr(i+1,s,h+1,g);

    // si es mejor opcion, ent actualizar
    GETMAX( dp[i][s][h][g], p_vivir_salir_por_baterias);


    // --- ---  OPCION 3  --- --- 
    // --- --- buscar comer --- -- 
    double p_vivir_salir_por_comida = 0.0;
    // no aparece el gigant ferret (1-p)

    // aparece el light ferrer -2 // encuentro bateria comida y no me enveneno
    p_vivir_salir_por_comida += pNoGF * pLF*pVivirLF* pComer * dpr(i+1,s-2,0,g);
    // aparece el light ferrer -2 // no encuentro comida
    p_vivir_salir_por_comida += pNoGF * pLF*pVivirLF* pNoCom * dpr(i+1,s-2,h+1,g);
    // no aparece el light ferrer -0 // encuentro bateria comida y no me envenenor
    p_vivir_salir_por_comida += pNoGF * pNoLF* pComer * dpr(i+1,s,0,g);
    // no aparece el light ferrer -0 //no encuentro comida
    p_vivir_salir_por_comida += pNoGF * pNoLF* pNoCom * dpr(i+1,s,h+1,g);

    GETMAX( dp[i][s][h][g], p_vivir_salir_por_comida);

    
    // dar la mejor solucion
    dpcheck[i][s][h][g] = true;
    return dp[i][s][h][g]; 
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

    // intput
    cin >> horasPorSobrevivir >> maxBaterias >> iniBaterias >> maxHambre;
    for( int i=1; i<=horasPorSobrevivir; ++i){
        cin >> pBateria[i] >> pComida[i] >> pEnvenenarse[i] >> pFerretLight[i];
    }

    // recursivivamente llamar
    double ans = dpr(1,iniBaterias,0,0);

    // repsuesta
    cout << fixed << setprecision(12) << ans << "\n";

    
}
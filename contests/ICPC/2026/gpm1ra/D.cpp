/*
    * https://codeforces.com/gym/106495/problem/D
    * 2026 ICPC Gran Premio de Mexico 1ra Fecha
    * upsolving  D. Door 1
    * angelmanuelgl

*/

#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define sz(x) (int)(x).size()

#ifdef LOCAL
    bool debug = true;
#else
    bool debug = false;
#endif

#define DEBUG if(debug)
#define NODEBUG if(!debug)




#define MAXN 505
#define MAXK 14 // maxBaterias
#define MAXH 14 // maxHambre

// info
int horasPorSobrevivir, maxBaterias, iniBaterias, maxHambre;
double pBateria[MAXN], pComida[MAXN], pEnvenenarse[MAXN], pFerretLight[MAXN];

// dp
double dp[MAXN][MAXK][MAXH][MAXN]; // dp[i,s,h,g] = maxima probabilidad de sobrevivir desde el inicio de la hora i hasta el final,
                                  //               con s baterias, han pasado h horas sin comer y g apariciones giganteFerret
bool dpcheck[MAXN][MAXK][MAXH][MAXN];



void act( double &a, double b){
    a = max(a,b);
}

string sangria = "";

double dpr( int i, int s, int h, int g  ){
    // --- ya calculado ---- 
    if( dpcheck[i][s][h][g] ) return dp[i][s][h][g]; 


    // ---  --- --- ver que no nos pasemos --- --- --- ---- 
    
    // si encontramos linternas y ya estabamos llenos
    if( s > maxBaterias ) s = maxBaterias;
    if( dpcheck[i][s][h][g] ) return dp[i][s][h][g]; 
    // si tenemos menos de 0 linternas seguro es porque venimos de un light ferret y debimos morrir // esto no deberia pasar
    if( s < 0 ) return 0.0;

    // si nos estuvimos mucho timepo sin comer
    if( h >= maxHambre ){
        dp[i][s][h][g] = 0;
        dpcheck[i][s][h][g] = true;
        return 0.0;
    } 
    if( dpcheck[i][s][h][g] ) return dp[i][s][h][g]; 
    // si ya sobrevivimos las horas necesarias, la probabilidad de sobrevivir es 1
    if( i > horasPorSobrevivir  ){
        dp[i][s][h][g] = 1.0;
        dpcheck[i][s][h][g] = true;
        return 1.0;
    }

        
    DEBUG{
        cout << sangria << "+calculando dp[" << i << "][" << s << "][" << h << "][" << g << "] \n";
        if( dpcheck[i][s][h][g]  ) cout << sangria << "-dp ya calculado: " << dp[i][s][h][g] << "\n";
         // aumentar sangria para la siguiente llamada recursiva
        if( !dpcheck[i][s][h][g]  ) sangria += "   ";
    }
  

    // calcular dp[i][s][h][g]
    double pBat = pBateria[i];
    double pNoBat = 1.0 -pBateria[i];

    double pCom = pComida[i];
    double pNoCom = 1.0 -pComida[i];

    double pNoEnv = 1.0 -pEnvenenarse[i];

    double pLF = pFerretLight[i];
    double pNoLF = 1.0 -pFerretLight[i];

    double pGF =  ( 1.0 +g) / (1.0 +i); // probabilidad de que aparezca giganteFerret en la hora i+1, dado que han aparecido g veces en las i horas anteriores
    double pNOGF = 1.0 - pGF;  
 
    // --- ---- ---- ----  opcion 1: esconderse --- ---- ---- ---- 
    // valEsp 
    double valEsp = 0.0;
    if(h+1 < maxHambre )  valEsp += pGF * dpr(i+1, s, h+1, g+1); // aparecio el gigant Ferret
    if(h+1 < maxHambre )  valEsp += pNOGF * dpr(i+1, s, h+1, g); // no apareio el gigant Ferret
    act(dp[i][s][h][g], valEsp ); 
    

    // --- ---- ---- ----  opcion 2: salir a buscar bateria --- ---- ---- ---- 
    // valEsp si no aparece el gigant Ferret
    valEsp = 0.0;
    // aparece light ferret -2 // encontraste bateria +1 
    if( s>=2 &&  h+1 < maxHambre) valEsp += pLF * pBat * dpr(i+1, s-1, h+1, g);

    // aparece light ferret -2 // NOencontraste bateria +0
    if( s>=2 &&  h+1 < maxHambre) valEsp += pLF * pNoBat * dpr(i+1, s-2, h+1, g);

    // no aparece light ferret -0 // encontraste bateria +1
    if( h+1 < maxHambre) valEsp += pNoLF * pBat * dpr(i+1, s+1, h+1, g);

    // no aparece light ferret -0 // NO encontraste bateria +0
    if( h+1 < maxHambre) valEsp += pNoLF * pNoBat * dpr(i+1, s, h+1, g);

    // probabildiad de que no apareca el giganFerret * valEsp
    act(dp[i][s][h][g], pNOGF* valEsp );
    

    // --- ---- ---- ---- opcion 3: salir a buscar comida --- ---- ---- ---- 
    // valEsp si no aparece el gigant Ferret
    valEsp = 0.0; 
    // aparece light ferret -2 // encontraste comida // no te envenenaste
    if( s>=2 ) valEsp += pLF * pCom * pNoEnv * dpr(i+1, s-2, 0, g);

    // aparece light ferret -2 // NO encontraste comida 
    if( s>=2  &&  h+1 < maxHambre) valEsp += pLF * pNoCom * dpr(i+1, s-2, h+1, g);

    // no aparece light ferret -0 // encontraste comida // no te envenenaste
    valEsp += pNoLF * pCom * pNoEnv * dpr(i+1, s, 0, g);

    // no aparece light ferret -0 // NO encontraste comida +0 
    if( h+1 < maxHambre) valEsp += pNoLF * pNoCom * dpr(i+1, s, h+1, g);
 
    // val_esp = probabildiad de que no apareca el giganFerret * valEsp
    act(dp[i][s][h][g], pNOGF* valEsp );
    

    DEBUG{
        sangria = string(sangria.size()-3, ' '); // dismuuir sangria para regresar a la  llamada recursiva anterior
        cout << sangria << "-calculando dp[" << i << "][" << s << "][" << h << "][" << g << "] = " << dp[i][s][h][g] << "\n";
    }

    dpcheck[i][s][h][g] = true;
    return dp[i][s][h][g];
}
// uso :  g++ -DLOCAL K.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.txt");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    // --- input ---
    cin >> horasPorSobrevivir >> maxBaterias >> iniBaterias >> maxHambre;
    
    int n = horasPorSobrevivir;

    for( int i=1; i<=horasPorSobrevivir; ++i){
        cin >> pBateria[i] >> pComida[i] >> pEnvenenarse[i] >> pFerretLight[i];
    }

    DEBUG cout << "input leido \n";

    DEBUG{
        cout << "horaspor sobrevivir: " << horasPorSobrevivir << ", maxBaterias: " << maxBaterias << ", iniBaterias: " << iniBaterias << ", maxHambre: " << maxHambre << "\n";
    }
    // --- ---- casos bases --- --- ---
    memset(dp, 0, sizeof(dp)); // inicializar dp con 0.0
    memset(dpcheck, 0, sizeof(dpcheck)); // inicializar dpcheck con false
    for( int s=0; s<=maxBaterias; ++s){
        for( int h=0; h<=maxHambre; ++h){
            for( int g=0; g<=n; ++g){
                dp[ n+1 ][s][h][ g ] = 1.0; // si ya sobrevivimos las n+1 horas, la probabilidad de sobrevivir es 1
                dpcheck[ n+1 ][s][h][ g ] = true;
            }
        }
    }
    DEBUG cout << "casos bases llenados\n";
    
    // llamar recursivamente dp
    dpr(1,iniBaterias,0,0);
    DEBUG cout << "dp calculado\n";

    // respuesta
    cout << fixed << setprecision(12) << dp[1][iniBaterias][0][0] << "\n";


}
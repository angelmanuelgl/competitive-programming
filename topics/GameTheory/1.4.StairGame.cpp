/*  
    * Contest: Game theory training sessions | CS
    * URL: https://cses.fi/problemset/task/1099
    * Problem:  Stair Game

    * Topic: Game Teory
    * Algorithm: Juego de Nim para posciones pares, se pueden ignorar las posiciones impares
    * Complexity: O(n) n - cantidad de escalones

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

#define PERDEDOR 0
#define GANADOR 1


bool calculado[10][10][10][10][10][10];
int estado[10][10][10][10][10][10];

int calcular_estado( int x, int y, int z, int w, int a, int b){
    if( calculado[x][y][z][w][a][b] ) return estado[x][y][z][w][a][b];

    
    for( int i=1; i<=x; i++)
        if( calcular_estado(x-i,y,z,w,a,b) == PERDEDOR ) return GANADOR;


    for( int i=1; i<=y; i++)
        if( calcular_estado(x+i,y-i,z,w,a,b) == PERDEDOR ) return GANADOR;

    for( int i=1; i<=z; i++)
        if( calcular_estado(x,y+i,z-i,w,a,b) == PERDEDOR ) return GANADOR;

    for( int i=1; i<=w; i++)
        if( calcular_estado(x,y,z+i,w-i,a,b) == PERDEDOR ) return GANADOR;

    
    for( int i=1; i<=a; i++)
        if( calcular_estado(x,y,z,w+i,a-i,b) == PERDEDOR ) return GANADOR;

    for( int i=1; i<=b; i++)
        if( calcular_estado(x,y,z,w,a+i,b-i) == PERDEDOR ) return GANADOR;
    
    return PERDEDOR;
}

void aux(int x){
    if( x==200) cout << "X ";
    else if( x) cout << x << " ";
    else cout << "_ ";
}

void imprimir( int i1, int i2, int i3, int i4, int i5=0, int i6=0, bool salto = true){
    aux(200);
    aux(i1);
    aux(i2);
    aux(i3);
    aux(i4);
    aux(i5);
    aux(i6);
    cout << (calcular_estado( i1,i2,i3,i4,i5, i6) ? "G" : "P") << " ";


    if(salto) cout << "\n";
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
    // estado perdedor
    estado[0][0][0][0][0][0] = PERDEDOR;
    calculado[0][0][0][0][0][0] = true;

    DEBUG{

    int tam = 4;
    
    cout << "pPOSICIONES IMPARES \n";
    tam =5; 
    for( int i1=1; i1<=tam; i1++) imprimir(0, i1,0, 0, 0, 0, true);
    for( int i1=1; i1<=tam; i1++) imprimir(0, 0, 0, i1,0, 0, true);
    for( int i1=1; i1<=tam; i1++) imprimir(0, 0, 0, 0, 0,i1, true);


    cout << "POSICIONES IMPARES MIXTAS\n";
    tam = 2; 
    for( int i3=0; i3<=tam; i3++){
    for( int i2=0; i2<=tam; i2++){
    for( int i1=0; i1<=tam; i1++){
        imprimir(0,i1,0,i2,0, i3, true);
    }}}



    cout << "POSICIONES PARES\n";
    tam =4; 
    for( int i1=1; i1<=tam; i1++) imprimir(i1,0, 0, 0, 0, 0, true);
    for( int i1=1; i1<=tam; i1++) imprimir(0, 0, i1,0, 0, 0, true);
    for( int i1=1; i1<=tam; i1++) imprimir(0, 0, 0, 0,i1, 0, true);

    cout << "POSICIONES PARES MIXTAS\n";
    tam =3; 
    for( int i3=0; i3<=tam; i3++){
    for( int i2=0; i2<=tam; i2++){
    for( int i1=0; i1<=tam; i1++){
        imprimir(i1,0,i2,0, i3, 0, false);

        cout << ": " ;

        int suma;        
        suma = i1^i2^i3;
        cout << suma << " ";

        cout << "\n";
    }}}


    } // end debug

    DEBUG{
    cout << "TEST RAPIDO PARA EVALUAR IDEA:\n";
    int tam = 3;
    for( int i6=0; i6<=2; i6++){
    for( int i5=0; i5<=2; i5++){
    for( int i4=0; i4<=tam; i4++){
    for( int i3=0; i3<=tam; i3++){
    for( int i2=0; i2<=tam; i2++){
    for( int i1=0; i1<=tam; i1++){
        imprimir(i1,i2,i3,i4, i5, i6, false);

        cout << ": " ;

        int suma;        
        suma = i1^i3^i5;
        cout << suma << " ";

        cout << "\n";
    

    }}}}}}

    } // end degubg


    // ESTO ES LA SOLUCION // EL RESTO SE PUEDE IGNORAR
    int t; cin >> t;

    while( t-- ){
        int n; cin >>n;
        vi p(n+1); 
        
        int paridad = 0, elxor = 0;
        for(int i=1; i<=n; i++ ){
            cin >> p[i];
           
            if( paridad )
                elxor ^= p[i];


            paridad = !paridad;
        } 
        if( elxor ) cout <<"first\n";
        else cout << "second\n";
        

    }
    
}
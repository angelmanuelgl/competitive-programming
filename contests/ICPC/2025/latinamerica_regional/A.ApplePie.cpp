
/*  
    * Contest: 2025-2026 ICPC Latin American Regional Programming Contest
    * URL: https://codeforces.com/gym/106178
    * Problem: A. Apple Pie
    * Topic: graph | Euler path
    * Algorithm: check if exists an  Euler path form L_p to R_1
    * Complexity: O( n^2 )

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


// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //


int calcular_grados_impar( int n, vvi & used, vi & grad ){
    grad.resize(n,0);

    // contar el grado
    for( int i=0; i<n; i++){
        for( int j=0; j<i; j++ ){
            if(  used[i][j] ) continue;
            grad[i]++; grad[j]++;
        }
    }
    // contar cuantos hay con grado impaar
    int cnt = 0;
    for( int i=0; i<n; i++)
        if( grad[i]%2 ) cnt++;

    return cnt;
}

#define TODO_VISITADO 102


int ver_conexidad( int n, vvi & used, vi & grad ){
    // lsita de adyacneica
    vvi ady(n);
    for( int i=0; i<n; i++){
        for( int j=0; j<i; j++ ){
            if(  used[i][j] ) continue;
            ady[i].pb(j);
            ady[j].pb(i);
        }
    }

    
    
    for( int i=0; i<n; i++) print(ady[i]);

    /// hacer dfs
    vector<bool> visited(n,false);
    // los que ya usaron todas sus atistas estan visitados
    for( int i=0; i<n; i++) if(grad[i] == 0) visited[i] = 1;

    // tomar algunoq ue no haya sido visitado
    int ini = -1;
    for( int i=0; i<n; i++)if( !visited[i]  ){
        ini = i;
        break;
    }
    // todo esta visitado
    if( ini == -1 ) return TODO_VISITADO;
    // for( int i=0)

  
    print(visited);
    print(ini);


    vector<bool> marcado(n,false);
    // BFS marcando visitados
    vi p(n,-1);
    vi q = {ini};
    for( int i=0; i<sz(q); i++){   
        int u = q[i];
        visited[u] = true; 
        if( ! marcado[u] ){
            for( int v: ady[u]){
                visited[v] = true; 
                if( v == p[u]) continue;
                
                if( marcado[v]) continue; 
                p[v] = u;
                q.push_back(v);
            }
        }
        marcado[u] = true;
    }

    print(visited);

    // si no viist alguno es disconex
    for( int i=0; i<n; i++)if( !visited[i]  ) return false;

    return true;

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

    // // COMENTAR 
    // int t; cin >> t; 
    // while( t-- ){ 
    // // COMENTAR
    
    int n, p, q; cin >> n;
    
    cin >> p;
    vi L(p);
    for( int & x: L ) cin >>x;

    cin >> q;
    vi R(q);
    for( int &x: R) cin >> x;

    
    if( n > 2 && n%2 == 0 ){
        cout << "N\n";
        return 0;
    }

    // marcar como usados los que ya tenemos
    vvi used( n, vi(n,0) );

    print(n,p,q, L, R);

    // izquierdo
    for( int i=1; i< p; i++){
        int a = L[i], b = L[i-1];
        a--; b--; 
        used[a][b]++;
        used[b][a]++;
    }
    int start = -1;
    if( p >= 1) start = L.back()-1;

    // derecho
    for( int i=1; i< q; i++){
        int a = R[i], b = R[i-1];
        a--; b--; 
        used[a][b]++;
        used[b][a]++;
    }
    int end = -1;
    if( q >= 1) end = R[0]-1;


    for( int i=0; i<n; i++) print( used[i]);
    print( start, end);

    // si de casulidad en algun momento los usados sonmayores a dos
    int cntUsed = 0;
    for( int i=0; i<n; i++){
        for( int j=0; j<i; j++ ){
            if(  used[i][j] > 1 ) cntUsed++;
        }
    }
    for( int i=0; i<n; i++) if(used[i][i])cntUsed++;
   
    // entre L y R ya repiten aristas
    if( cntUsed){
        cout << "N\n";
        return 0;
    }

  

    vi grad;
    int grad_impar = calcular_grados_impar( n, used, grad );
    

    print(grad);
    // si de  no hay camino euleriano // no se va a poder
    if( ! ( grad_impar == 0 || grad_impar == 2) ){
        cout << "N\n";
        return 0;
    }


    // revisar conexidad

    // ver si es conexo
    int isconexos = ver_conexidad(n, used, grad);

    print( isconexos );

    // si de casualidad ya estaba todo completo
    if( isconexos == TODO_VISITADO ){
     
        print( start, end);
        if( start == -1 || end == -1 ){
            cout << "Y\n";
            return 0;
        }

        // pasa solo 17 casos
        // // notar que no podemos poner la arista (start - end)
        cout << "N\n";
        return 0;

        // pasa solo 36 casos
        // no hay nada enmedio, asi que fin de L coninde incio R
        // 
        cout << ( (start == end)?"Y\n":"N\n");
        return 0;
    }

    // ver si too es conexo
    if( !isconexos ){    
        cout << "N\n"; return 0;
    }


    // casos

    // si puede comenzar y terminar en cualqueira
    // siempre se puede
    if( start == -1 && end == -1){
        cout << "Y\n";
        return 0;
    }

    // si el cominezo esta fijo pero el final peude ser cualqueira
    if( start != -1 && end == -1){
        // si hay un ciclo, siempre se puede
        if( grad_impar == 0 && grad[start] >=2){
            cout << "Y\n";
            return 0;
        }
        // si no es un ciclo, start debe ser inicio o fin (grado impar)
        if( grad_impar == 2){
            cout << ( (grad[start]%2==1) ? "Y\n": "N\n" );
            return 0;
        }
    }
    // si el final esta fijo pero el comienzo puede se rcualqueira
    if( start == -1 && end != -1){
        // si hay un ciclo, siempre se puede
        if( grad_impar == 0 && grad[end] >=2){
            cout << "Y\n";
            return 0;
        } 
        // si no es un ciclo, end debe ser inicio o fin (grado impar)
        if( grad_impar == 2){
            cout << ( (grad[end]%2==1) ? "Y\n": "N\n" );
            return 0;
        } 
    }

    // si ambos el comienzo y el final son el mismo
    if( start != -1 && end != -1){
        print( start, grad[start]);
        print( end, grad[end]);

        // si hay un ciclo, 
        if( grad_impar == 0){
            // el comienzo uy el final deben ser el mismo
            cout <<  ( (start == end && grad[start] >=2)? "Y\n" : "N\n" );
            return 0;
        }
        // si no es un ciclo, start y end debe ser inicio o fin (ambos grado impar)
        if( grad_impar == 2){
            bool sepuede =  (grad[start]%2==1 && grad[end]%2==1);
            sepuede = sepuede && (start != end);
            cout << ( sepuede? "Y\n": "N\n" );
            return 0;
        } 
    }

    DEBUG cout << "\n\n";


    // creoq eu se me debio escapar algun caso
    cout << "N\n";

    // } // COMENTAR
}
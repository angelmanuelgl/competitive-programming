/*
    * DFS
    * E. Cactus
    * https://codeforces.com/contest/231/problem/E
    * angelmanuelgl
*/

#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
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

const int MOD = 1e9 + 7;

#define is_on(S,j) (S & (1<<(j)))


// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// uso :  g++ -DLOCAL K.cpp

const int MAXN = 1e5 +2;
// const int MAXN = 10000;
struct Cactus{
    
    vi listAdy[MAXN];
    
    int n;
    void init(int nn){
        n = nn;
    }

    void push_back( int u, int v){
        listAdy[u].pb(v);
        listAdy[v].pb(u);
    }

    /*
        Encontrar ciclos
    */
    enum ESTADO{ NO, VISITANDO, TERMINADO};
    int padre[MAXN]; // 0 o -1 no padre // 1 - n si padre
    int estado[MAXN]; // 0 no visitado // 1 visitando // 2 terminado
    int cntCiclos = 0; // 
    

    int id_cactus2id_tree[MAXN];
    int cactus2tree( int id){
        return id_cactus2id_tree[id];
    }
    /*
        Deterctar ciclos
        para cada nodo marcamos al ciclo al que pertenece
    */
    void dfs( int u, int p ){
        estado[u] = ESTADO::VISITANDO;
        padre[u] = p;

        // ver sus vecinos
        for( int vecino : listAdy[u]){
            if(vecino == p) continue;

            // si aun no esta visitado
            if( estado[vecino] == ESTADO::NO ) {
                dfs( vecino, u);
            }
            
            // si llegamos a un nodo que se esta visitando entonces hay un ciclo
            else if( estado[vecino] == ESTADO::VISITANDO ){        
                int id_ciclo = cntCiclos;
                int nodo_inicio = vecino;
                int nodo_actual = u;
                
                
                while( true ){
                    id_cactus2id_tree[ nodo_actual ] = id_ciclo;
                    
                    if( nodo_actual == nodo_inicio ) break;
                    nodo_actual =  padre[nodo_actual];
                }

               
               cntCiclos++; 
            }

            // esto no deberia pasar por la estrucutra del cactus
            // si no tendiramos cosas como A --- B --- C --- A con A,B,C ciclos
            else if( estado[vecino] == ESTADO::TERMINADO){

            }
        }
        
        // segun yo no hace falta esto porque al terinar de procesar un nodo 
        // es imposible que te lo vuelvasa enotra, por la esttructura del cactus pero ok
    
        estado[u] = ESTADO::TERMINADO;
    }

    /*
        Construir arbol donde cada nodo es un ciclo o bien un nodo
        

        -> va de 0 a numeros de nodos en el tree
        int id_cactus2id_tree[MAXN];
            ciclos           nodos
        [0, cntCilcos) [cntCilcos, cnt_nodos_tree)
    */
    vi tree_listAdy[MAXN];
    int peso_en_tree[MAXN];
    int cnt_nodos_tree;
    void construirArbol(){
        memset(estado, ESTADO::NO, sizeof(estado) );
        memset(padre, 0, sizeof(padre) );

        for( int i=0; i<MAXN; i++) id_cactus2id_tree[i] = -1;

        dfs(1, -1);


        // asignar ids
        cnt_nodos_tree = cntCiclos;
        for( int u=1; u<=n; u++){
            // -- si no pertenece a un ciclo crear nodo
            if(  id_cactus2id_tree[u] == -1){
                id_cactus2id_tree[u]  = cnt_nodos_tree;
               
                cnt_nodos_tree++;
                
            }
            // -- si es un ciclo
            else{
                // id del ciclo
                int id_tree = id_cactus2id_tree[u];
                peso_en_tree[ id_tree ] = 1;
            }
            

        }

        // asignar aristas
        for( int u=1; u<=n; u++){
            for( int vecino: listAdy[u]){
                // ids en el tree
                int u_id_tree =  id_cactus2id_tree[u];
                int vecino_id_tree =  id_cactus2id_tree[vecino];


                // evita procesar la arista bidireccional dos veces
                if( vecino_id_tree < u_id_tree) { 
                    tree_listAdy[ vecino_id_tree  ].pb( u_id_tree );
                    tree_listAdy[ u_id_tree  ].pb( vecino_id_tree );
                }
            }
        }

        // no debeira ha
    }

    void mostrarArbolConstruido(){
        DEBUG{
            cout << "\n MAPEO DE INDICES\n";
            cout << "Cactus\tTree\n";
            for( int i=1; i<=n; i++){
                cout << i  << "\t" <<  id_cactus2id_tree[i] << "\n";
            }

            cout << "\nLISTA DE ADYACENCIA\n";
            for( int i=0; i<cnt_nodos_tree; i++){
                cout << i  << " =  { " ;
                for( int vecino : tree_listAdy[i])
                    cout << vecino << " ";
                cout << " }\n";
            }
            cout << "\n";
        }
    }
};

const int LOG_MAXN = 21;
struct LCA{
    int depth[MAXN];
    int suma_pesos[MAXN];
    int P[LOG_MAXN+1][MAXN];

    vi tree[MAXN];
    int pesos[MAXN]; 
    
    void build( int n, vector<int> adj[], int pesosss[]){
        for(int i = 0; i <= n; ++i) {
            tree[i] = adj[i]; 
            pesos[i] = pesosss[i];
        }

        precalc( 0,-1, 0, 0 );
    }

    void precalc( int u, int p, int d = 1, int pesoActual = 0){
        depth[u] = d;
        suma_pesos[u] = pesoActual + pesos[u];
        P[0][u] = p;

        for( int k=1; k<=LOG_MAXN; k++){
            if( P[k-1][u] != -1)
                P[k][u] = P[ k-1 ][  P[k-1][u] ];
            else    
                P[k][u] = -1;
        }
            

        for( int hijo : tree[u]) if(p!= hijo)
            precalc(hijo, u, d+1 , suma_pesos[u]);
    }

    int get_lca( int a, int b){
        if( depth[b] < depth[a] ) swap(a,b);

        int dif = depth[b] - depth[a];
        for( int k = LOG_MAXN; 0<=k;  k--){
            if( is_on(dif, k) ) 
                b = P[k][b];
        }

        if(a == b ) return a;

        for( int k = LOG_MAXN; 0<=k; k--){
            if( P[k][a] != P[k][b]){
                a = P[k][a];
                b = P[k][b];
            }
        }
        return P[0][a];
    }

    /*
        El peso nos indica el numero de ciclso
    */
    int caminoMinimoPesado( int a, int b){
        int lca = get_lca(a, b);
        int pesoEnCamino = suma_pesos[a] + suma_pesos[b] - 2 * suma_pesos[lca] + pesos[lca];
        return  pesoEnCamino;
    }
    


};

int main(){
    #ifdef LOCAL
        ifstream cin("in.txt");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int n, m; cin >> n >> m;

    // leer el input cactus
    Cactus g; g.init(n);
    
    DEBUG cout << "inicializado g\n";

    int u,v;
    for( int i=0; i<m; i++){
        cin >> u >> v;
        g.pb(u,v);
    }
    
    DEBUG cout << "cactus leido\n";

    // construir el arbol apartir del cactus
    g.construirArbol();

    
    DEBUG cout << "tree contruido\n";

    g.mostrarArbolConstruido();

    // usar LCA con pesos para calcular caminso entre nodos
    LCA lca;
    lca.build( g.cnt_nodos_tree, g.tree_listAdy , g.peso_en_tree);

    DEBUG cout << "LCA precalculado\n";

    // precaclular potencias de dos mod 1000000007 
    ll pow2[MAXN]; pow2[0] = 1;
    for( int i=1; i<MAXN; i++){
        pow2[i] =  (pow2[i-1] * 2) % MOD;
        // DEBUG cout << pow2[i] <<  " \n"[i==MAXN-1];
    }


    DEBUG cout << "precalculadopotencias 2\n";
    // queries
    int q; cin >> q;

    while( q-- ){
        int a_cactus,b_cactus; cin >> a_cactus >> b_cactus;

        DEBUG cout << "indices en cactus: " << a_cactus << " " << b_cactus << "\n";
        int a_tree = g.cactus2tree(a_cactus);
        int b_tree = g.cactus2tree(b_cactus);

        DEBUG cout << "indices en tree: " << a_tree << " " << b_tree << "\n";

        int cnt_ciclos = lca.caminoMinimoPesado(a_tree, b_tree);

        ll caminosPosibles = pow2[cnt_ciclos];

        cout << caminosPosibles << "\n";

    }
}
/*
    * Domintator Tree
    * https://codeforces.com/gym/101741/problem/L
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




// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// uso :  g++ -DLOCAL K.cpp


struct Edge{
    int to, id;
};

struct Episode{
    int x,y,z; //  tres nodos
};


// const int MAXN = 200;
const int MAXN = 2e5+2;
struct grafo{
    int n;
    vector<Edge> listAdy[MAXN];
    bool visited[MAXN]; // nodos
    bool used[MAXN]; // aristas
    vector<Episode> ans;

    void init(int nn){
        n = nn;
    }

    void push_back( int u, int v , int id){
        listAdy[u].pb( {v, id} );
        listAdy[v].pb( {u, id} );
    }

    /*  --- DFS ---
        procesar hijos (no p)
        encontrar Episodes x-y-z // con y = u
        procesar nodo u
    */
    // devuelve un nodo true o false si dejo disponible la arista (u,p)
    bool dfs( int u, int p ){

        int padre_edge_id = -1;
        visited[u] = true;

        // vamos guardanod las aristas x-u-z //
        vector< Edge >  aristasParaEsteNodo;

        // para cada vecino
        for( auto edge_vecino : listAdy[u] ){
            int vecino = edge_vecino.to;
            int id_edge = edge_vecino.id;

            // ignorar al padre
            if( vecino == p ){
                padre_edge_id = id_edge;
                continue;
            }

            // ignorar a nodos que ya tomaron esa arista
            if( used[id_edge] ) continue;

            
            // si el nodo fue visitado es una back-edge
            // u mas profundo que vecino => toma la arista
            if( visited[vecino] ) {
                used[id_edge] = true;
                aristasParaEsteNodo.pb( edge_vecino );
            }
            // es un Tree-Edge
            else{

                // bool dejoDisponibleLaArista = dfs(vecino, u);
                
                // dfs en hijos y ver si uso la arista
                dfs(vecino, u);
                bool dejoDisponibleLaArista = !used[  id_edge ];

                // si no la uso esta dispobinle
                if( dejoDisponibleLaArista){
                    aristasParaEsteNodo.pb( edge_vecino );
                }
            }
        }

        
        // emparejamos las aristas
        int cnt = sz(aristasParaEsteNodo);

        for( int i=0; i < cnt-1; i+=2 ){
            Edge edge_1 = aristasParaEsteNodo[i];
            Edge edge_2 = aristasParaEsteNodo[i+1];
            int x = edge_1.to;
            int z = edge_2.to;

            ans.pb({x,u,z});
        }


        // caso cnt impar
        // si nos sobro una arista // emparejamos la arista restante con la del padre
        if( cnt %2 == 1){
            if( p != -1  ){
                Edge edge_final = aristasParaEsteNodo[cnt-1];
                int x = edge_final.to;

                ans.pb( {x,u,p} );

                // marcamos como usada y quitamos
                used[  padre_edge_id ] = true;
                return false;
            }
        }

        // caso cnt par
        // quedaronn todas emparejadas y la arista del padre desemparejada
        return true;

    }

    void dfs(){
        memset( visited, 0, sizeof(visited) );
        memset( used, 0, sizeof(used) );

        // pasar por todas las componentes conexas
        for( int i=1; i<=n; i++){
            if( visited[i] ) continue;
            dfs(i, -1);
        }
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
    
    grafo g;

    g.init(n);

    for( int i=0; i<m; i++){
        int u,v; cin >> u >> v;
        g.pb(u,v, i+1);
    }

    g.dfs();
    // cout
    cout << g.ans.size() << "\n";
    for( const auto& epis : g.ans ){
        cout << epis.x << " " << epis.y << " " << epis.z << "\n";
    }

}
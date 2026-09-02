/*
    * DFS 
    * E. Pairs of Pairs
    * https://codeforces.com/contest/1391/problem/E
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

const int MAXN = 500005;
// const int MAXN = 500;
struct DFStree
{
    // EL ORGINAL
    int n,m;
    vi listAdy_original[MAXN];

    
    // TREE
    int RAIZ = 1;
    int padre[MAXN], depth[MAXN];
    bool visitado[MAXN];

    vector<int> depth2nodos[MAXN];
    
    int max_depth = 0;
    int nodoMasAbajo = -1;

    void input(){
        cin >> n >> m;
        
        // LIMPIEZA
        for( int i=1; i <= n; i++ ){
            listAdy_original[i].clear();
            depth2nodos[i].clear();
            visitado[i] = false;
            // padre[i] = 0;
            // depth[i] = 0;
            max_depth = 0;
            nodoMasAbajo = -1;

        }



        // INPUT 
        int u,v;
        for( int i=0; i<m; i++){
            cin >> u >> v;
            listAdy_original[u].pb(v);
            listAdy_original[v].pb(u);
        }  

    }


    void dfs( int u, int p, int d ){
        visitado[u] = true;
        padre[u] = p;
        depth[u] = d;
        depth2nodos[d].pb(u);
        

        if( d > max_depth ){
            max_depth  = d;
            nodoMasAbajo = u;
        }

        // ver sus vecinos
        for( int vecino : listAdy_original[u]){
            if( vecino == p) continue;
            if( visitado[vecino] ) continue;
            
            dfs(vecino, u, d+1);
        }    
    }


    void construirDFStree(){
        // memset(visitado, 0, sizeof(visitado));

        dfs(1,0,1);

       
    } 

    void responder(){
        int techon2 = (n+1)/2;

        // camino mas larho
        if( max_depth >= techon2){
            cout  << "PATH\n";

            int actual = nodoMasAbajo;
            vi camino;
            while( true){
                camino.pb(actual);
                if( actual == RAIZ) break;
                actual = padre[ actual ];
            }

            int L = camino.size();
            cout << L << "\n";
            for( int i=0; i < L; i++){
                cout << camino[i] <<  " \n"[i==L-1];
            }
        }


        // emparejar
        else{
            cout <<"PAIRING\n";

            vpii parejas;

            // para cada profundaidad
            for( int i=1; i <=max_depth; i++){
                int sz = depth2nodos[i].size();

                for( int j=0; j+1 < sz; j+=2){
                    int u = depth2nodos[i][j];
                    int v = depth2nodos[i][j+1];
                    parejas.pb( {u,v} );
                }
            }


            cout << parejas.size() << "\n";
            for( const auto & p : parejas){
                cout << p.fi <<  " " << p.se << "\n";
            }
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
    int t; cin >> t;

    DFStree myArbol;
    while( t-- ){
      
        DEBUG cout << "caso " << t << "\n";
   
        myArbol.input();

        myArbol.construirDFStree();


        myArbol.responder();

        DEBUG cout << "end caso " << t << "\n\n";
    }
    
   

}
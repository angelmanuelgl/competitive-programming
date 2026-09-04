#include<bits/stdc++.h>]
#define NMAX 10'005
using namespace std;


int n,m,d;

struct edge{
    int from =-1;
    int to =-1;
    int64_t val = 0;
};

int64_t dist[NMAX+1];
//del 1 al  0 // solo usando aristas con valor menor igual a maxVal
int64_t BFS( int64_t maxVal,  vector<edge> grafo[]){

//
//    for( int i=1; i<=n; i++ ){
//        cout << i << " : ";
//        for( auto x : grafo[i]) cout << x.to << ',' << x.val << "  ";
//        cout << '\n';
//    }

    fill(dist, dist + NMAX, LLONG_MAX);
    dist[ 1 ] = 0;

    bool vis[n+1];
    memset( vis, 0 , sizeof(vis) );

    queue<int> cola;
    cola.push( 1 );


    while( !cola.empty() ){
        int act = cola.front();
        cola.pop();

        if( vis[act] ) continue;
        vis[ act ] = true;

        for( edge e: grafo[act] ){
            if( e.val > maxVal ) continue;

            if(  dist[ e.to ] <= dist[ e.from ] +1 ) continue;

            dist[ e.to ] = dist[ e.from ] +1;
            cola.push( e.to );
        }

    }

    return dist[n];
}

bool ansMenorIgual( int m , vector<edge> grafo[] ){
    int dist = BFS( m, grafo );
    if(  dist==-1 ) return false;
    if( dist > d ) return false;
    return true;
}


int main(){
//    ios_base::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);

    cin >> n >> m >> d;

    vector<edge> grafo[n+1];

    int a,b;
    int64_t c;
    for( int i=0; i<m; i++ ){
        cin >> a >> b >> c;
        grafo[a].push_back( {a,b,c} );
        grafo[b].push_back( {b,a,c} );
    }

    // 0 0 0 0 0 0 0 1 1 1 1 1 1  1
    // l no se puede pues las aristas tienen peso mayor igual 0
    // r si se puede
    // l < ans // ans <= r

    int64_t l=-1, r=1;
    while( !ansMenorIgual(r, grafo) ) r*=2;


//     cout << "l: "<< l << "   r: " << r << '\n';

//    for( int i=0; i<=20; i++ ){
//        int xd= BFS(i, grafo);
//        cout <<  "---> " << i << ' ' << xd <<  '\n';
//        for( int j=1; j<=n; j++ ) cout << j << "  " << dist[j] << "    ";
//        cout << '\n';
//    }


    while( l+1< r){
        int64_t m = (l+r)/2;

        if( ansMenorIgual(m, grafo) ) r = m;
        else l = m;

    }

    //el valor minimo de todos los posibles caminos del maximo es r
    int64_t minMaxVal = r;
    //cout << minMaxVal << '\n';


    //recuperar respuesta
    vector<int> ans;
    ans.push_back( n );

    int act = n;
    int disAct = dist[ act ];
    while( act!= 1 ){
        for( edge e: grafo[act] ){
            if( e.val<= minMaxVal && dist[e.to] == disAct-1  ){
                ans.push_back( e.to );
                disAct--;
                act = e.to;
                continue;
            }
        }
    }

    int tam = ans.size()-1;

    cout <<  tam << '\n';
    for( int i=tam; i>=0; i-- ) cout << ans[i] << " \n"[i==0];

}

#include<bits/stdc++.h>
#define MAXN (100'005)

using namespace std;

int n;
double v[MAXN],x[MAXN];

// T=min{ T(x) : x en la linea } <= m
// El infimo es menor que m si existe un elemento menor que m en el conjnto
// equiv existe x tal que T(x) <= m
// equiv existe x tal que   max( |x_i-x|/v_i: i ) <= m
// equiv existe x tal que  |x_i-x|/v_i <= m  para toda i
// equiv existe x tal que  |x-x_i| <= mv_i   para toda i
// equiv existe x tal que   x en [x_i - mv_i, x_i + mv_i]   para toda i
// equiv INTERSECCION_i [x_i - mv_i, x_i + mv_i] es no vacio
//bool T_esMenorIgualQue( double m ){
//    if( m<0 ) return false;
//    vector< pair<double,int> > intervalos;
//    for( int i=0; i<n; i++ ){
//        intervalos.push_back( { x[i]-m*v[i] ,1}  ); //abre
//        intervalos.push_back( { x[i]+m*v[i] ,-1}  ); //cierra
//    }
//    sort( intervalos.begin(), intervalos.end() );
//
//    int abiertos=0;
//    for( auto  i: intervalos ){
//        abiertos +=  i.second;
//        if( abiertos == n ) return true;
//    }
//    return false;
//}
bool T_esMenorIgualQue( double m ){
    if( m<0 ) return false;

    double menorQueCierra = 1e10;
    double mayorQueAbre = -1e10;

    for( int i=0; i<n; i++ ){
        mayorQueAbre = max( mayorQueAbre, x[i]-m*v[i] );
        menorQueCierra = min( menorQueCierra, x[i]+m*v[i] );
        if( menorQueCierra < mayorQueAbre   ) return false;
    }
    return true;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n; //peronas
    for( int i=0; i<n; i++ ) cin >> x[i] >> v[i];

    //queremos encotrar el timepo minimo que tardan en reunirse en un punto
    // T=min{ T(x) : x en la recta  }
    // donde T(x) es el tiempo que tardan en llegar al punto x
    // T(x) = max(  |x_i-x|/v_i : i=0,1,..,n-2 )


    // l <= T < r
    // en l seg no se puede reunir // en r segundos si
    double l=-1, r=1;
    while(  !T_esMenorIgualQue(r)  ) r*=2;

    // hasta 2*10^9  precision 10^6 //aprox 50
    for( int i=0; i<=60; i++ ){
        double m = (l+r)/2;
//        cout << l << ' ' << m << ' ' << r << ' ' << T_esMenorIgualQue(m) <<'\n';
        if( T_esMenorIgualQue(m) ) r = m;
        else l = m;

    }

    cout  << setprecision(8) << l << '\n';

}

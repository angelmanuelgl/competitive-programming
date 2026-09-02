#include<bits/stdc++.h>
#define MAXN 1005
using namespace std;


int m,n; // globos // trabajdores
int t[MAXN],y[MAXN],z[MAXN];


//calcula el tiempo que le toma inflar m globos al assistant i y ve si puede
bool sePuedeInflar( int m, int i, int time ){
    int descanso = m/y[i];
    int delta = 0;
    if( m%y[i]==0 ) delta = z[i];
    return (descanso*z[i] + m*t[i] - delta) <= time ;
}


// devuelve x=la cantidad de globos que puede inflar el assistant i
int cuantosInfla( int t, int i){
    //si se puede inflar l globos (l<=x) // no se puede inflar r globos (x<r)
    int l=0, r=1;
    while( sePuedeInflar(r,i,t) ) r*=2;

    while( l+1<r ){ //queremos l+1=r
        int m = (l+r)/2;
        if( sePuedeInflar(m,i,t) ) l = m;
        else r = m;
    }
    return l;
}

//suma cuantos puede inflar cada assistants
bool sePuedenInflar_m( int t ){
    int cantidad = 0;
    for( int i=0; i<n; i++ ){
        cantidad+=cuantosInfla(t,i);
        if( cantidad>= m ) return true;
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> m >> n ;

    for( int i=0; i<n; i++ ) cin >> t[i] >> y[i] >> z[i];


    //en tiemepo l no se puede //  en tiempo r si se puede
    int l=-1, r=1; //INCREIBLE XD tenia l=0 y no jalaba
    while( !sePuedenInflar_m(r) ) r *= 2;

    while( l+1<r ){ //queremos l+1=r
        int m = (l+r)/2;
        if( sePuedenInflar_m(m) ) r = m;
        else l = m;
    }
    cout << r << '\n';


    //se puende inflar en r minutos
    int cantidad = 0;
    for( int i=0; i<n; i++ ){
        int infla = cuantosInfla( r, i);

        if( cantidad >= m ){
            infla = 0;
        }else if( cantidad+infla > m ){
            infla = m - cantidad;
        }
        cantidad+=infla;
        cout << infla  << " \n"[i==n-1];
    }



//    cout << "\n\nDEBUG\n" ;
//
//    for( int i=0; i<20; i++ ){
//        cout << i<< " :  ";
//        for( int j=0; j<n; j++ ) cout << cuantosInfla(i, j) << " \n"[j==n-1];
//    }
//
//    for( int i=0; i<30; i++){
//        cout << i << ": " << sePuedenInflar_m( i ) << "\n";
//    }



}

/*
    12 3
    2 1 3
    3 2 2
    3 2 1

1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
i X d d d i X d d d i X d d d i X d d d i X d d d i X d d d
i i X i i X d d i i X i i X d d i i X i i X d d i i X i i X d d
i i X i i X d i i X i i X d i i X i i X d i i X i i X d

0 1 3 3 3 5 6 6 6 7 8 9 10

*/

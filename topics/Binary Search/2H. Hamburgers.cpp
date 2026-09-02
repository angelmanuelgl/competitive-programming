#include<bits/stdc++.h>
using namespace std;

int xd( char c ){
    if( c == 'B') return 0;//bread
    if( c == 'S') return 1;//sausage
    if( c == 'C') return 2;//cheese
}

int64_t tiene[3];
int64_t cadauna[3];
int64_t precios[3]; //basta con int
int64_t dinero;

bool sePuedeHacer( int64_t m ){ //numeros de cousils
    int64_t gasto=0;
    for( int i=0; i<3; i++ ){
        if( m*cadauna[i] <= tiene[i] ) continue;
        gasto += ( m*cadauna[i] - tiene[i]) * precios[i];
    }
//    cout <<  m << ": " << gasto << ' ' << dinero <<  '\n';
    return gasto<=dinero;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s; cin >> s;
    for( int i=0; i<s.size(); i++ ){
//        cout << s[i] << ' ' << xd( s[i] ) << "\n";
        cadauna[ xd( s[i] ) ]++;

    }

//    for( int i=0; i<3; i++ ) cout << cadauna[i];


    for( int i=0; i<3; i++ ) cin >> tiene[i];
    for( int i=0; i<3; i++ ) cin >> precios[i];

    cin >> dinero;


    // se pueden hacer l hamburguesas // no se puede hacer r hamburguesas
    int64_t l=0, r=1;
    while( sePuedeHacer(r) ) r*=2;

    while( l+1< r ){
        int64_t m = (l+r)/2;
        if( sePuedeHacer(m) ) l = m;
        else r = m;
//        cout << l << ' ' << r << '\n';
    }

    cout << l << '\n';

}

#include<bits\stdc++.h>
#define MAXN 200005
using namespace std;

int quitados[MAXN];
string t,p;
int n,m;

//dado la cantidad de quitados te dice si p es subsecuencia
// de t, considerando las que ya se quitaron
bool esSubsecuencia( int q ){
//    cout << "debug " << q << ": \n";
//    if( q > t.size() ) return false;
//    cout << q << '\n';
    int i=0; // t
    int  j=0; // p
    while( j < p.size()  && i < t.size() ){
        if( quitados[i] <= q ){ //ignota
            i++;
            continue;
        }
//        cout << "  " << j << ' ' << p[j] << ' ';
//        cout << i << ' ' << t[i] << ' ';


        if( p[j] == t[i] ){
            i++;
            j++;
//            cout << "SI\n";
        }else{ //prueba la siguyeinte
            i++;
//            cout << "No\n";
        }
    }

//    cout << '\n' <<  ( j == p.size() ) << '\n';
    if( j == p.size() ) return true;
    return false;
}

int main(){
//    ios_base::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);

    cin >> t >> p;

    int n = t.size();
    int m = p.size();

    // quita[ i ] = cuando quitamos el i
    int quita;
    for( int i=1; i<=n; i++ ){
        cin >> quita;
        quitados[ quita-1 ] = i;
    }
//    for( int i=0; i<n; i++ ) cout << quitados[i] << " \n"[i==n-1];

    //quitando l letras de t se encontrar a la subcadena p
    //quitando r letras de t NO se encontrar a la subcadena p
    int l=0, r=1;

//    cout << esSubsecuencia(0) << '\n';
//    cout << esSubsecuencia(1) << '\n';
//    cout << esSubsecuencia(2) << '\n';
//    cout << esSubsecuencia(3) << '\n';
//    cout << esSubsecuencia(4) << '\n';

    while( esSubsecuencia( r ) ) r*=2;

    while( l+1< r ){
        int m = (l+r)/2;
        if( esSubsecuencia( m ) ) l = m;
        else r = m;
    }
    cout << l << '\n';

}

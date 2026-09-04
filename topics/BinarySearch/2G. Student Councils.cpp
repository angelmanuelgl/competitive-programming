#include<bits/stdc++.h>
#define NMAX 55
using namespace std;

int k,n; //cada cousil tiene k // hay n grupos
int64_t a[NMAX];// numero de estudiantes

bool sePuedeFormar( int64_t m ){ //numeros de cousils
    int64_t sum = 0;
    for( int i=0; i<n; i++ ) sum += min( a[i], m );
    return ( sum >=k*m );
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> k >> n;

    for( int i=0; i<n; i++ ) cin >> a[i];

    // se pueden formar l cousils // no se puede formar r cousils
    int64_t l=0, r=1;
    while( sePuedeFormar(r) ) r*=2;

    while( l+1< r){
        int64_t m = (l+r)/2;

        if( sePuedeFormar(m) ) l = m;
        else r = m;
    }

    cout << l << '\n';

}

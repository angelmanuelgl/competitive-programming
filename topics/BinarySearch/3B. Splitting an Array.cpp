#include<bits/stdc++.h>
using namespace std;

int n,k;
vector<int> a;

bool ansMenorIgual( int64_t m  ){
    //if( m>n ) return false;

    int64_t sumAct=0, intervalos=1;
    for( int i=0; i<n; i++ ){


        if( sumAct + a[i] <= m ){
            sumAct = sumAct + a[i];
        }
        else{
            intervalos++;

            sumAct = a[i];

            if(  sumAct > m ) return false;
        }

        if( intervalos >k ) return false;
    }

    return (intervalos <= k);

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    cin >> n >> k;
    a.resize(n);

    for( int &i : a ) cin >> i;

    // l no se puede // r se puede
    // l < ans // ans <=r
    int64_t l=0, r=1;
    while(  !ansMenorIgual(r) )r*=2; // hasta que sea falso !(ans<=r), es decir ans<=r


//    for( int i=0; i<=20; i++ ){
//        cout << i << ' ' << ansMenorIgual(i) << '\n';
//    }


    while( l+1 < r ){
        int64_t m = (l+r)/2;

//        cout << "l: " <<  l << "  r: " <<  r << " m: " <<  m << " " << ansMenorIgual(m) << '\n';

        if(  ansMenorIgual(m) ) r = m;
        else l = m;
    }

    cout << r << '\n';

}

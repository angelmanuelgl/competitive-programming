#include<bits/stdc++.h>
using namespace std;

//x^2 + sqrt(x) = c
// llegar a c nos toma a lo mas log_2(10^10)= 33.2
//presision 10^6 log_2(10^6)= 20

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long double c; cin >> c;

    // l < x // x < c
    long double l=0, r=c;

    for( int i=0; i<=80; i++ ){
        long double m = (l+r)/2;
        if( m*m + sqrt(m) < c  ) l = m;
        else r = m;
    }
    cout << fixed << setprecision(20) << r << '\n';

}

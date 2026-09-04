#include<bits/stdc++.h>
using namespace std;

long double f(long double x){
    return x*x;
}



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    double y = 123456789.0;  // valor que buscamos
    double N = 1e9;
    double eps = 1e-9;

    double l = 0.0, r = N;
    while(r - l > eps){
        double m = (l + r) / 2.0;
        if(  f(m) < y ) l = m;
        else r = m;
    }

    cout << fixed << setprecision(15);
    cout << "x ~    " << (l+r)/2.0 << "\n";
    cout << "sqrt(y)" << sqrt(y ) << "\n";
    cout << "f(x) ~ " << f((l+r)/2.0) << "\n";
    cout << "y  " << y << "\n";


}

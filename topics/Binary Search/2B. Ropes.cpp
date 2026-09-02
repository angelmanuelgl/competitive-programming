#include<bits/stdc++.h>
#define NMAX 10'005
using namespace std;
//https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/B

int n,k;
double ropes[NMAX];


bool isposiblecut( double x ){
    int cantidad =0;

    for( int i=0; i<n; i++ ){
        cantidad+= floor(ropes[i]/x);
        if( cantidad >= k ) return true;
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    for( int i=0; i<n; i++ ) cin >> ropes[i];

    // 1 1 1 1 1 1  1 0 0 0 0 0 0

    // l se cumple // r no se cumple
    double l=0, r=10'000'005;
    //while(  abs(l-r)> 1e-5 ){ //falto mas precision supongo
    for( int xd=0; xd<100; xd++ ){
        double m =(l+r)/2;

        if( isposiblecut(m) ){
            l = m;
        }else{
            r = m;
        }
    }
    cout << fixed << setprecision(20) <<  l << '\n';
}

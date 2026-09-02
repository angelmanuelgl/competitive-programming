#include<bits/stdc++.h>
using namespace std;


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    int n,k;
    cin >> n >> k;


    int arr[n];
    for( int i=0; i<n; i++ ) cin >> arr[i];

    /// print the maximum index of an array element not greater than the given one.
    /// el maximo que es menor igual
    int x;
    while(k--){
        cin >> x;
        //l es menor igual y r es mayor
        int l=-1 , r=n;  //arr[-1]=-\infty arr[n]=\infty \c /
        while( l+1<r ){
            int m = (l+r)/2;
            if( arr[m] <= x ) l= m;
            else r= m;
        }
        cout << r << '\n'; //era l+1
    }

}

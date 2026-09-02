#include<bits/stdc++.h>
using namespace std;


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    int n; cin >> n;

    int arr[n];
    for( int i=0; i<n; i++ ) cin >> arr[i];
    sort( arr, arr+n );

    int k; cin >> k;
    int x,y;\

    while(k--){
        cin >> x >>y; //buscar cuantos nuymeros hay de [x,y]


        //buscar el indice del ultimo menor ESTRICTO que x
        int l=-1 , r=n;  //l es menor estricto  y r es mayorigual
        while( l+1<r ){
            int m = (l+r)/2;
            if( arr[m] < x ) l= m;
            else r= m;
        }
        int LL= l;


        //buscar el indice del primer mayor ESTRICTO que y
        l=-1 , r=n;
        while( l+1<r ){
            int m = (l+r)/2;
            if( arr[m] <= y ) l= m;
            else r= m;
        }
        int RR= r;


        cout << RR-1 -LL << '\n';
    }

}

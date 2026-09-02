// https://leetcode.com/problems/count-the-number-of-inversions/
/// CONTAR NUMERO DE INVERSIONES DE UN ARREGLO
/// === numero de swaps adyacentes para ordenarlo
/// O( N log N )


#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define sz(x) (int)(x).size()

const int MOD = 1e9 + 7;



/// Contar inversiones de una permutacion
long long contar_inversiones(   vi &arr, int l, int r ){
    // si tenemos un elemento ==> 0 inversiones
    if(   r-l <= 1 ) return 0;

    int mid = (l+r)/2;
    ll inversiones = 0;

    inversiones += contar_inversiones(arr, l, mid);
    inversiones += contar_inversiones(arr, mid, r);

    // merge
    vi tmp;
    int i=l, j =mid;
    while(   i< mid && j < r  ){
        // mitad LEFT
        if( arr[i] <= arr[j] ) tmp.pb(arr[i++]);
        // mitad RIGHT
        else{
            tmp.pb( arr[j++] );
            // todos los elemtnos i, ... , mid-1  son mayores arr[j]
            inversiones += (mid -i);
        }
    }
    // poner el resto
    while(  i< mid ) tmp.pb(   arr[i++] );
    while(  j< r ) tmp.pb(   arr[j++] );

    // copiar en el original
    for(  int k=l; k<r; k++ ) arr[k] =  tmp[k-l];

    return inversiones;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;
    vi arr(n); for( int &x: arr)cin >>x;

    cout << contar_inversiones(arr, 0,n) << '\n';
}

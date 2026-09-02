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

// start programar 4:36
// acepted 5:18 

const int MAXN = 2e5 + 5;
const int BLOCK_SIZE = 450;// sqrt( 2e5)

ll a[MAXN];
ll block_sum[MAXN / BLOCK_SIZE + 5];
int n,q;

void construir(){
    memset( block_sum, 0, sizeof(block_sum));
  /*   for( int i=0; i<n; i++){
        block_sum[ i/BLOCK_SIZE  ] +=a[i];
    } */
}

ll query_val( int i){
    return a[i] +  block_sum[ i/BLOCK_SIZE  ];
}

void query_update( int l, int r, ll val){
    int cl = l / BLOCK_SIZE;
    int cr = r / BLOCK_SIZE;
    if( cl == cr ){
        for(  int i=l; i<=r; i++) a[i]+=val;
    }else{
        int fin = min( (cl+1)*BLOCK_SIZE - 1, r) ;
        for( int i=l; i<=fin; i++ ) a[i]+=val;
        for( int i=cl+1; i<cr; i++ ) block_sum[i]+=val;
        for( int i=cr*BLOCK_SIZE; i<=r; i++ ) a[i]+=val;
    }
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);



    int tipo,i,j;
    ll u;

    cin >> n >> q;

    
    memset( a, 0, sizeof(a));
    for( int i=0; i<n; i++) cin >> a[i];
    construir(); 

 
    //for( int i=0; i<n; i++)  cout <<  i << " " <<  query_val( i ) << "\n";

     /*for( int i=0; i<n; i++)  cout <<  a[ i ] << " "; 
    cout << "\n";
    for( int i=0; i<n; i++)  cout <<  block_sum[ i ] << " "; 
    cout << "\n";
     */

    while(q--){
        cin >> tipo; 

        if( tipo == 1 ){
            cin >> i >> j >> u;
            query_update( i-1, j-1, u );
            //for( int i=0; i<n; i++)  cout <<  i << " " <<  query_val( i ) << "\n";

        }else if( tipo == 2){
            cin >> i;
            cout  << query_val( i - 1) <<'\n';

        }

    }
        


    

}


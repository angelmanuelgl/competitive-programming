/*  
    * Contest: 2025-2026 ICPC Northwestern European Regional Programming Contest 
               (NWERC 2025)
    * URL: https://codeforces.com/gym/106495
    * Problem: E. Erratic Lights

    * Topic: Math |Probability | Linearity of Expectation | Binomial Distribution
    * Algorithm: - Greddy ELimination, Binomial Coefficient / Combinatorics
    * Complexity: Time( N ) Space( N^2 ) for pascal Triangle // N <= 100

    * Status: ACCEPTED
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- Type Aliases ---
typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

// --- Short Macros ---
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()


// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //

int idx( char c){
    if( c == 'r') return 0;
    if( c == 'g') return 1;
    return 2;
}

void calc_binom( vvll & binom, int N){
    binom.resize( N+1, vll(N+1)  );

    for( int n=0; n<=N ; n++){
        binom[n][0] = binom[n][n] = 1;
        for( int k=1; k<n; k++){
            binom[n][k] = binom[n-1][k-1] + binom[n-1][k];
        }
    }
}

// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif


    // we count the frequencies
    int n; cin >> n;
    int freq[3] = {};
    
    char c;
    for( int i=0; i<n; i++){
        cin >> c;
        freq[  idx(c) ]++;
    }

    // sort indices / frequencies without loss of generality
    // target order: r <= b <= g
    sort( freq, freq+3 );
    int r = freq[0], g=freq[1], b=freq[2];

    // CASE 0
    // if all lights already have the same color
    if(  r == 0 && g == 0 ){
        cout << fixed << setprecision(7) << 0 << "\n";
        return 0;
    }

    // CASE 1
    // if  r == 0  // Two colors present
    // Goal: Transform all 'g' lights into 'b'
    if( r == 0){
        // the expected number of times  one (g) transforms
        // into specific other (b)
        // E[ T ] = sum_{i=1}^{\infty} i * (2/3)^{i-1} * (1/3)
        // E[ T ] = 3

        // if you think about favorable cases over total case
        // P[ T == i ] = 2^{i-1} / 3^i 

        // if you think about Each touch is an Bernoulli independent trial
        // with success probability = 1/3 
        // T ~ Geom(p)
        // => P[ T == i ] = (1 - p)^{i-1} * p = (2/3)^{i-1} * (1/3)
        int transform_one = 3;

        // for each g transforms
        cout << transform_one * g <<"\n";
        return 0;
    }

    // CASE 2
    // three colors present
    // Goal: Transform 'r' lights into either 'g' or 'b'

        // expected number of touches to trasnform a single light  (r)
        // into ANY other color (g o b)
        // E[T] = sum_{i=1}^{\infty} i*  (1/3)^{i-1} (2/3)
        // E[T] = 3/2

        // if you think about favorable cases over total case
        // P[ T == i ] = 2 / 3^i 

        // if you think about Each touch is an Bernoulli independent trial
        // with success probability = 2/3 
        // T ~ Geom(p)
        // => P[T == i] = (1 - p)^{i-1} * p = (1/3)^{i-1} * (2/3)
        double transform_one   = 3.0 / 2.0;

        double tranform_all = transform_one * r;

        // check all possible outcomes after transforming
        // 'r' lights into either 'g' or 'b'
        // E[ T after transforme ] =  1/ totalCases  \sum_{case} E[ T in the case]
        
        // each 'r' light independently turns into 'g' with prob 1/2
        // and into 'b' with prob 1/2 upon leaving the 'r' state.

        // number of outcomes in 2
        ll pow2r = (1ll << r); // 2^r;


        // we need to know binom(r,a)
        // n = 34 is sufficient since r<=10=/3  beacuse r is the minumin(r,g,b)
        vvll binom;
        calc_binom( binom, 34);

        // accumulator fot expecte number of touches needed after trasnforming all 'r' lights
        ll after_transform_weighted_sum = 0;
        for( int i=0; i<=r; i++){
            // outcome:
            // i 'r' lights into g lights
            // a-i 'r' lights into b lights
            // final state : (0, g + i, b + r -i)

            // we know the answe for only g and b lights, (before case)
            ll expect_this_case_ans =  3 * min( g + i, b + r - i );
            ll probability_in_this_case =  binom[r][i]; // pow2r;

            after_transform_weighted_sum +=  expect_this_case_ans*probability_in_this_case;
        }

        double expected_after_trasnform= 1.0f * after_transform_weighted_sum / pow2r;

        double ans = tranform_all + expected_after_trasnform;
        cout <<  fixed  << setprecision(7) << ans <<"\n";
}
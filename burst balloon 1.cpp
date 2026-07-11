/*
There are n balloons and n bullets and each balloon is assigned with a particular number (point).
Whenever a particular balloon is shot the no of points increases by
1.the multiplication of point assigned to balloon on left and that of right side.
2.point assigned to left if no right exists
3.point assigned to right if no left exists.
4.the point assigned to itself if no other balloon exists.
 
You have to output the maximum no of points possible.
 
Input-1
1 2 3 4
 
Output-1
20

Input-2
1 0 2 3 0 4

Output-2
34
*/
 //dp based onn which balloon is shot the last handle the edges by padding 1s

#include <iostream>
using namespace std;

int n;
int a[100];
int dp[100][100];

int f(int l, int r) {
    if (l > r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    
    int ans = 0;
    
    // Pick balloon k to be the LAST one to burst in this sub-range
    for (int k = l; k <= r; k++) {
        ans = max(ans, a[l-1] * a[r+1] + f(l, k-1) + f(k+1, r));
    }
    
    return dp[l][r] = ans;
}

void reset() {
    // Pad the array with 1s to elegantly handle boundary multiplications
    for (int i = 0; i < 100; i++) a[i] = 1;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            dp[i][j] = -1;
        }
    }
}

void solve() {
    cin >> n;
    reset();
    
    // Read elements starting from index 1 (leaving a[0] as 1)
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    int ans = 0;
    
    // Pick balloon k to be the ABSOLUTE LAST one to burst in the entire game
    for (int k = 1; k <= n; k++) {
        ans = max(ans, a[k] + f(1, k-1) + f(k+1, n));
    }
    
    cout << ans << endl;
}

int main() {
    int tt;
    cin >> tt;
    while (tt--) solve();
    
    return 0;
}

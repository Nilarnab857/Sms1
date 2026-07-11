/*
https://www.youtube.com/watch?v=IFNibRVgFBo - Tushar Roy

Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. 
You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins.
Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.
Input: [3,1,5,8]
Output: 167 
*/

//easier than bb 1
//because we dont need the outer loop for each k for the final ans

#include <iostream>
using namespace std;

int n;
int a[305];
int dp[305][305];

int f(int l, int r) {
    if (l > r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    
    int ans = 0;
    
    // Pick balloon k to be the LAST one to burst in this sub-range
    for (int k = l; k <= r; k++) {
        ans = max(ans, a[l-1] * a[k] * a[r+1] + f(l, k-1) + f(k+1, r));
    }
    
    return dp[l][r] = ans;
}

void reset() {
    // Pad the array with 1s to handle boundary multiplications
    for (int i = 0; i < 305; i++) a[i] = 1;
    for (int i = 0; i < 305; i++) {
        for (int j = 0; j < 305; j++) {
            dp[i][j] = -1;
        }
    }
}

void solve() {
    cin >> n;
    reset();
    
    // Read elements starting from index 1 (leaving a[0] as 1)
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    // The padded '1' at a[n+1] is already set by reset()
    
    // Just ask the DP to solve the entire range from 1 to n
    int ans = f(1, n);
    
    cout << ans << endl;
}

int main() {
    int tt;
    cin >> tt;
    while (tt--) solve();
    
    return 0;
}

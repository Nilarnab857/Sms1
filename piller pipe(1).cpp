/*
https://www.geeksforgeeks.org/samsung-r-d-noida-question-september-2018/
https://code.hackerearth.com/8ca41dM?key=54591adea7ca921ac55169b10f163508

You have to place an electronic banner of a company as high as it can be, so that whole the city can view the banner 
standing on top of TWO PILLERS.
The height of two pillers are to be chosen from given array.. say [1, 2, 3, 4, 6]. We have to maximise the height
of the two pillars standing side by side, so that the pillars are of EQUAL HEIGHT and banner can be placed on top of it.
In the above array, (1, 2, 3, 4, 6) we can choose pillars like this, say two pillars as p1 and p2.
In case, there is no combination possible, print 0.

INPUT :
1
5
1 2 3 4 6
Output :
8
*/

#include <iostream>
using namespace std;

void solve(int a[], int vis[], int p1, int p2, int n, int &ans){
    if(p1 == p2){
        if(p1 > ans){
            ans = p1;
        }
    }


    for(int i=0 ; i<n ; ++i){
        if(vis[i] == 0){
            vis[i] = 1;
            solve(a, vis, p1 + a[i], p2, n, ans);
            solve(a, vis, p1, p2 + a[i], n, ans);
            vis[i] = 0;
        }
    }
}

int main(){
    int n;
    cin>>n;
    int a[n];

    for(int i=0 ; i<n ; ++i){
        cin>>a[i];
    }

    int vis[n] = {0};
    int ans = -1;
    solve(a,vis,0,0,n,ans);

    cout<<ans;
}


//dp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt;
    if (!(cin >> tt)) return 0;
    
    while(tt--) {
        int n, s = 0;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            s += a[i];
        }
        
        // dp[i][j] stores the max height of the taller pillar using a subset 
        // of the first i elements, such that the difference between pillars is j.
        vector<vector<int>> dp(n, vector<int>(s + 1, -1));
        
        // Base cases for the 0-th element
        dp[0][a[0]] = a[0]; // Put it on Pillar 1
        dp[0][0] = 0;       // Discard it
        
        for(int i = 1; i < n; i++) {
            for(int j = 0; j <= s; j++) {
                
                // We MUST branch out from the PREVIOUS state (i-1)
                if(dp[i-1][j] != -1) {
                    
                    // Option 1: Discard the current element (carry forward previous state)
                    dp[i][j] = max(dp[i][j], dp[i-1][j]);
                    
                    // Option 2: Put it on the TALLER pillar
                    if(j + a[i] <= s) {
                        dp[i][j + a[i]] = max(dp[i][j + a[i]], dp[i-1][j] + a[i]);
                    }
                    
                    // Option 3: Put it on the SHORTER pillar
                    if(a[i] <= j) {
                        // It doesn't overtake the taller pillar
                        dp[i][j - a[i]] = max(dp[i][j - a[i]], dp[i-1][j]);
                    } else {
                        // It overtakes the taller pillar!
                        // Old shorter pillar height = dp[i-1][j] - j
                        // New taller pillar height = (dp[i-1][j] - j) + a[i] = dp[i-1][j] + a[i] - j
                        dp[i][a[i] - j] = max(dp[i][a[i] - j], dp[i-1][j] + a[i] - j);
                    }
                }
            }
        }
        
        // The answer is the maximum equal height (difference = 0) 
        // after considering all n elements.
        cout << dp[n-1][0] << "\n";
    }
    return 0;
}

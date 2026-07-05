/*
https://www.geeksforgeeks.org/samsung-competency-test-25-aug-19/
*/
/*
	----IIT(ISM) Dhanbad----
	Author: Siddhant Choudhary
	
	--samsumg coding test--
	
	Q.There is a large plot with various sinkholes present. 
	Since one sinkhole can combine with another sinkhole, it is required to get
	at most one sinkhole while occupying the plot. You have to find the maximum 
	square-area formed with at most one sinkhole present.
	If there are two plots with the same area then print the one with 
	lesser sinkhole present otherwise if the sinkholes are also same then print
	anyone. For each case, you have to print the bottom leftmost coordinate and 
	top rightmost point. Please keep in mind that the plot starts with (1, 1).

	Time limit= 1sec and Memory limit– 256Mb

	Input: First line will give the number of test cases. For each test case, we
	will be given the size of the plot matrix N x M (where 1<=N, M<=1000). Next
	line will give the number of sinkholes present in the matrix K (1<=K<=N+M). 
	Next, K-lines will give the coordinates of the sinkholes.

	Output: For each test case, you have to print the number of the test case
	and the coordinates of the resultant square.
	i.e. #i xb yb xt yt (ith test case, xb=bottomost left x-coordinate, 
	yb=bottomost  left y-coordinate, xt= topmost right x-coordinate,
	yt= topmost right y-coordinate)
	
  *	time complexity of my approach = O(n*m*log(min(m,n))) *
*/

#include <bits/stdc++.h>
using namespace std;

void solve(int tc) {
    int m, n;
    cin >> m >> n;
    
    // Read the grid (0 for empty, 1 for sinkhole)
    vector<vector<int>> a(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    
    // Build 2D Prefix Sum array
    vector<vector<int>> pre(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            pre[i][j] = (a[i][j] == 1) + pre[i][j-1] + pre[i-1][j] - pre[i-1][j-1];
        }
    }
    
    int maxL = -1;              // Tracks the maximum side length offset (length - 1)
    int min_sinkholes = 2;      // Used for the tie-breaker
    int maxr1 = 1, maxc1 = 1, maxr2 = 1, maxc2 = 1;
    
    // Iterate through every cell treating it as the top-left corner
    for (int r = 1; r <= m; r++) {
        for (int c = 1; c <= n; c++) {
            
            int lo = 0;
            int hi = min(m - r, n - c);
            int valid_L = 0; 
            
            // Binary search the maximum valid side length from this starting cell
            while (hi >= lo) {
                int mid = lo + (hi - lo) / 2; // Renamed 'm' to 'mid' to prevent shadowing 'm' (rows)
                int nr = r + mid;
                int nc = c + mid;
                
                int cnt = pre[nr][nc] - pre[nr][c-1] - pre[r-1][nc] + pre[r-1][c-1];
                
                if (cnt <= 1) {
                    valid_L = mid; // This size works, save it
                    lo = mid + 1;  // Try to find a larger square
                } else {
                    hi = mid - 1;  // Too many sinkholes, reduce the size
                } 
            }
            
            // Calculate the exact number of sinkholes for the largest valid square found here
            int nr = r + valid_L;
            int nc = c + valid_L;
            int cnt = pre[nr][nc] - pre[nr][c-1] - pre[r-1][nc] + pre[r-1][c-1];
            
            // Update the answer if this square is strictly larger
            if (valid_L > maxL) {
                maxL = valid_L;
                min_sinkholes = cnt;
                maxr1 = r; 
                maxc1 = c; 
                maxr2 = nr; 
                maxc2 = nc;
            } 
            // TIE-BREAKER: If it's the same size, pick the one with fewer sinkholes
            else if (valid_L == maxL) {
                if (cnt < min_sinkholes) {
                    min_sinkholes = cnt;
                    maxr1 = r; 
                    maxc1 = c; 
                    maxr2 = nr; 
                    maxc2 = nc;
                }
            }
        }
    }
    
    // Output formatted to match Samsung OA requirements
    cout << "#" << tc << " " << maxr1 << " " << maxc1 << " " << maxr2 << " " << maxc2 << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; i++) {
            solve(i); // Pass test case number for formatting
        }
    }
    return 0;
}

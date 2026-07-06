/*A robot is placed in an $N \times N$ grid. It starts at the top-left corner (0, 0) and needs to reach the bottom-right corner (N - 1, N - 1).
Each cell in the grid contains either a digit from '0' to '9' representing the number of reward points available in that cell, or an 'x' representing an obstacle that the robot cannot pass through.
From any cell (i, j), the robot can move in exactly three directions (provided they are within the grid boundaries and are not obstacles):Right: to cell (i, j + 1)Down: to cell (i + 1, j)Diagonal Down-Right: to cell (i + 1, j + 1)
Important Notes:Regardless of the input given, the starting cell (0, 0) and the destination cell (N - 1, N - 1) will always yield 0 reward points.Your task is to find the maximum possible reward points the robot can collect on its way from the start to the destination.
Additionally, you need to find the total number of distinct paths that allow the robot to collect this exact maximum reward.If it is absolutely impossible for the robot to reach the destination due to obstacles, both the maximum reward and the number of paths should be reported as 0.Input FormatThe first line contains an integer $T$, denoting the number of test cases.For each test case:The first line contains an integer $N$, denoting the size of the grid.The next $N$ lines each contain $N$ characters (digits '0'-'9' or 'x'), representing the grid.Output FormatFor each testcase, output two space-separated integers on a new line:The maximum reward points collected.The total number of paths that yield this maximum reward.If no valid path exists to the destination, output 0 0.*/
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        char arr[n][n];
        
        // Separate DP tables
        int dp[n][n];  // Stores the maximum reward to reach (i, j)
        int dp1[n][n]; // Stores the number of paths yielding that max reward
        
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cin>>arr[i][j];
                // Default all cells to unreachable (INT_MIN) and 0 paths
                dp[i][j] = INT_MIN;
                dp1[i][j] = 0;
            }
        }
        arr[0][0]='0';
        arr[n-1][n-1]='0';
        
        // Base case: Starting position
        dp[0][0] = 0;
        dp1[0][0] = 1;
        
        // Move through the matrix forwards
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                // Skip the starting cell as it's already computed
                if(i==0 && j==0) continue;
                
                if(arr[i][j]=='x')
                {
                    dp[i][j] = INT_MIN;
                    dp1[i][j] = 0;
                }
                else
                {
                    // Fetch values from Top, Left, and Top-Left. 
                    // If out of bounds, treat as INT_MIN (unreachable)
                    int top = (i > 0) ? dp[i-1][j] : INT_MIN;
                    int left = (j > 0) ? dp[i][j-1] : INT_MIN;
                    int topLeft = (i > 0 && j > 0) ? dp[i-1][j-1] : INT_MIN;
                    
                    int maxi = max(top, max(left, topLeft));
                    
                    if(maxi == INT_MIN)
                    {
                        // If all previous cells are unreachable, this cell is unreachable
                        dp[i][j] = INT_MIN;
                        dp1[i][j] = 0;
                    }
                    else
                    {
                        // Accumulate paths from the cells that yielded the max value
                        int path = 0;
                        if(top == maxi)
                            path += dp1[i-1][j];
                        if(left == maxi)
                            path += dp1[i][j-1];
                        if(topLeft == maxi)
                            path += dp1[i-1][j-1];
                            
                        dp[i][j] = maxi + (arr[i][j]-48);
                        dp1[i][j] = path;
                    }
                }
            }
        }
        
        // Output the result for the bottom-right cell
        if(dp[n-1][n-1] == INT_MIN)
            cout<<"0 0"<<endl;
        else
            cout<<dp[n-1][n-1]<<" "<<dp1[n-1][n-1]<<endl;   
    }
    return 0;
}

/*
SRI Delhi, IIT B, 2026 FTE

We have a road that is a line of integer positions (0,1,...,n). There may be up to one tree on the left and up to one tree on the right at each integer position (i in {1,...,n-1}). Each tree has an integer height (h in [1,1000]). The total number of trees is (T).

A robot starts at position (0). Its job is to cut every tree and deliver them all at position (n). Rules:

* Cutting a tree costs (1) (so cutting all trees costs (T) in total; this part is fixed).
* Moving the robot a distance (d) along the line costs (d).
* The robot can carry any number of trees, but the stack of carried trees must always be in non-increasing order from bottom to top. Equivalently: every time the robot picks up a new tree, its height must be less equal to the height of the tree currently on top of the stack (if any). This permits equal heights.
* The robot must finish at position (n) after having cut and delivered all trees.

Goal: find the minimum total cost = (movement cost) + (cutting cost (=T)).

Input Format:
n -> length of road (5 <= n <= 1000)
left[i] -> n length array of left side tree heights
right[i] -> n length array of right side tree heights

E.g.
Input:
1
5
0 3 2 1 0
0 3 2 1 0

Output:
#1 11

*/

#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int n;
int dp[1001][1001];

int solve(vector<vector<int>> &trees, int treeVal, int pos) {
    if (treeVal == 0) {
        return n - pos;
    }

    if (dp[treeVal][pos] != -1) {
        return dp[treeVal][pos];
    }

    if (trees[treeVal].empty()) {
        return dp[treeVal][pos] = solve(trees, treeVal - 1, pos);
    }

    vector<int> &line = trees[treeVal];
    int t = line.size();
    int cost = INT_MAX;

    int L = line.front();
    int R = line.back();

    if (pos < L) {
        int dist = R - pos;
        int nPos = R;

        int curr = t + dist + solve(trees, treeVal - 1, nPos);
        cost = min(cost, curr);
    } else if (pos > R) {
        int dist = pos - L;
        int nPos = L;

        int curr = t + dist + solve(trees, treeVal - 1, nPos);
        cost = min(cost, curr);
    } else {
        int dist1 = (pos - L) + (R - L);
        int nPos1 = R;
        int curr1 = t + dist1 + solve(trees, treeVal - 1, nPos1);

        int dist2 = (R - pos) + (R - L);
        int nPos2 = L;
        int curr2 = t + dist2 + solve(trees, treeVal - 1, nPos2);

        cost = min({cost, curr1, curr2});
    }

    return dp[treeVal][pos] = cost;
}

int main(int argc, char const *argv[]) {
    int testCases;
    cin >> testCases;

    for (int t = 1; t <= testCases; t++) {
        cin >> n;

        vector<vector<int>> trees(1001);
        memset(dp, -1, sizeof(dp));

        int a;
        for (int i = 0; i < n; i++) {
            cin >> a;
            if (a > 0)
                trees[a].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            cin >> a;
            if (a > 0)
                trees[a].push_back(i);
        }

        for (int i = 0; i < 1001; i++) {
            if (trees[i].empty()) {
                continue;
            }
            sort(trees[i].begin(), trees[i].end());
        }

        int minCost = solve(trees, 1000, 0);
        cout << "#" << t << " " << minCost << endl;
    }

    return 0;
}


//nil solution

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Changed return type from void to int
int f(int h, int pos, vector<pair<int, int>>& trees, vector<vector<int>>& dp, int n) {
    // Base case: No more heights to check. Just walk to the finish line (n).
    if (h == 0) return n - pos;

    // Memoization check
    if (dp[h][pos] != -1) return dp[h][pos];

    // If there are NO trees at this height (1e9 is our placeholder), skip to height h-1
    if (trees[h].first == 1e9) {
        return dp[h][pos] = f(h - 1, pos, trees, dp, n);
    }

    int L = trees[h].first;
    int R = trees[h].second;

    // Scenario A: Robot is to the left of all trees of this height
    if (pos < L) {
        int cost = R - pos; // Distance to walk to R
        return dp[h][pos] = cost + f(h - 1, R, trees, dp, n);
    } 
    // Scenario B: Robot is to the right of all trees of this height
    else if (pos > R) {
        int cost = pos - L; // Distance to walk to L
        return dp[h][pos] = cost + f(h - 1, L, trees, dp, n);
    } 
    // Scenario C: Robot is in between the trees
    else {
        // Choice 1: Walk to L, then all the way to R
        int cost1 = (pos - L) + (R - L);
        // Choice 2: Walk to R, then all the way to L
        int cost2 = (R - pos) + (R - L);
        
        // We want the MINIMUM cost, not maximum
        return dp[h][pos] = min(cost1 + f(h - 1, R, trees, dp, n),
                                cost2 + f(h - 1, L, trees, dp, n));
    }
}

void solve(int testCaseNum) {
    int n;
    cin >> n;

    // Initialize trees pair: {Leftmost, Rightmost}. 
    // Leftmost starts at 1e9 (infinity) so min() works. Rightmost starts at -1.
    vector<pair<int, int>> trees(1005, {1e9, -1});
    int totaltrees = 0;

    // Read Left Side Trees
    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        if (h > 0) {
            totaltrees++;
            trees[h].first = min(trees[h].first, i);
            trees[h].second = max(trees[h].second, i);
        }
    } // Added missing closing brace

    // Read Right Side Trees
    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        if (h > 0) {
            totaltrees++;
            trees[h].first = min(trees[h].first, i);
            trees[h].second = max(trees[h].second, i);
        }
    } // Added missing closing brace

    // Initialize DP table. Positions can go from 0 up to n, so size is n+1.
    vector<vector<int>> dp(1005, vector<int>(n + 1, -1));

    // Calculate minimum movement cost starting from height 1000 at position 0
    int minMovementCost = f(1000, 0, trees, dp, n);
    
    // Total cost is Movement Cost + Cutting Cost (which is equal to totaltrees)
    int totalCost = minMovementCost + totaltrees;
    
    cout << "#" << testCaseNum << " " << totalCost << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; i++) {
            solve(i);
        }
    }
    return 0;
}

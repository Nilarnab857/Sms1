/*
https://www.geeksforgeeks.org/samsung-interview-experience-on-campus-for-r-d-noida/

A binary matrix of nxm was given, you have to toggle any column k number of times so that you can get the maximum 
number of rows having all 1’s.

for eg, n=3, m=3,

            1 0 0

            1 0 1

            1 0 0

if k=2, then we will toggle column 2 and 3 once and we will get rows 1 and 3 with 1 1 1 and 1 1 1 i.e. all 1’s so 
answer is 2 as there are 2 rows with all 1’s.

if k=3, then we will toggle column 2 thrice and we will get row 2 with 1 1 1 i.e. all 1’s so answer is 1 as there 
is 1 row with all 1’s.
*/



//IDEA
//main concept is of each possible row types only one of the row types can be made 1 and all others can be made all1
// for each row type compute the frequency and 0s and check if we can convert as parity of k and toggles must be same and  zerocnt<= k
//maximise over all rows
#include <iostream>
using namespace std;

int n, m, k;
int grid[55][55];

void solve(int testCaseNum) {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    int max_all_ones_rows = 0;

    // Check every row as a potential "target pattern"
    for (int i = 0; i < n; i++) {
        int zero_count = 0;
        
        // 1. Count the zeros in the current row
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) {
                zero_count++;
            }
        }

        // 2. Check if this row CAN be converted to all 1s
        if (zero_count <= k && (k - zero_count) % 2 == 0) {
            
            int identical_rows_count = 0;
            
            // 3. Count how many rows in the entire matrix are identical to row i
            for (int r = 0; r < n; r++) {
                bool is_identical = true;
                for (int c = 0; c < m; c++) {
                    if (grid[i][c] != grid[r][c]) {
                        is_identical = false;
                        break;
                    }
                }
                
                if (is_identical) {
                    identical_rows_count++;
                }
            }

            // 4. Update the global maximum
            if (identical_rows_count > max_all_ones_rows) {
                max_all_ones_rows = identical_rows_count;
            }
        }
    }

    cout << "#" << testCaseNum << " " << max_all_ones_rows << "\n";
}

int main() {
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

Given below are the raw materials quantities and their respective selling price(if sold as raw).

D --> No of CPUs
E --> No of memory chips
F --> No of boards
d --> Selling price of CPU
e --> Selling price of Memory chips

We are given N Computer configurations like below : 
Di, Ei, Fi, SPi, which are the CPU, Chips, Boards and one unit selling price for ith computer respectively.
Our task is to maximize the final cost.
Constraints:
1. Can use at Max 3 different Configurations
2. We can use 1 configuration multiple times
3. Remaining Inventories can be sold on its selling price

Input:
T --> Number of test cases.
D E F d e --> Inventories
N --> Total Configuration Count
Di Ei Fi SPi
...
Dn En Fn SPn

1<=T<=10
1<= D, E, F <= 100
1<= d, e <=100000
1<=N<=8

Output:
First Line print the Case #testCaseNumber
Second Line Print Maximum Cost per test case in each line.

Sample Input:
1 --> Total Test Case
10 10 10 2 1 --> D E F d e
1 --> PC Configuration Count
1 2 2 3 --> D1 E1 F1 SP1

Sample Output:
Case #1
30
//not this is a Linear prog prob which is NP hard for dp ,
	//soo looping and determining the last loop in O(1) is actually best
	
#include <bits/stdc++.h>
using namespace std;

int DD, EE, FF, d, e;
int n, maxm;

void solve1(int i, int j, int k, const vector<int>& D, const vector<int>& E, const vector<int>& F, const vector<int>& S) {
    
    // Config properties for easier reading
    int d1 = D[i], e1 = E[i], f1 = F[i], s1 = S[i];
    int d2 = D[j], e2 = E[j], f2 = F[j], s2 = S[j];
    int d3 = D[k], e3 = E[k], f3 = F[k], s3 = S[k];
    
    // Calculate Net Profit for Configuration 3
    int net_profit_3 = s3 - (d3 * d + e3 * e);
    
    for (int x1 = 0; x1 * d1 <= DD && x1 * e1 <= EE && x1 * f1 <= FF; x1++) {
        
        int remD1 = DD - x1 * d1;
        int remE1 = EE - x1 * e1;
        int remF1 = FF - x1 * f1;
        
        for (int x2 = 0; x2 * d2 <= remD1 && x2 * e2 <= remE1 && x2 * f2 <= remF1; x2++) {
            
            int remD = remD1 - x2 * d2;
            int remE = remE1 - x2 * e2;
            int remF = remF1 - x2 * f2;
            
            int cur_profit = (x1 * s1) + (x2 * s2);
            
            // O(1) Greedy decision for Configuration 3
            if (net_profit_3 > 0) {
                
                // Find maximum units of Config 3 we can physically build
                int x3 = INT_MAX;
                if (d3 > 0) x3 = min(x3, remD / d3);
                if (e3 > 0) x3 = min(x3, remE / e3);
                if (f3 > 0) x3 = min(x3, remF / f3);
                
                if (x3 != INT_MAX) {
                    remD -= x3 * d3;
                    remE -= x3 * e3;
                    cur_profit += (x3 * s3);
                }
            }
            
            // Sell whatever is left over
            cur_profit += (remD * d) + (remE * e);
            
            if (cur_profit > maxm) {
                maxm = cur_profit;
            }
        }
    }
}

void solve(int caseNum) {
    cin >> DD >> EE >> FF >> d >> e;
    cin >> n;
    
    vector<int> D(n), E(n), F(n), S(n);
    for (int i = 0; i < n; i++) {
        cin >> D[i] >> E[i] >> F[i] >> S[i];
    }
    
    maxm = (DD * d) + (EE * e);
    
    // N^3 loop to pick the 3 configurations
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                solve1(i, j, k, D, E, F, S);
            }
        }
    }
    
    cout << "Case #" << caseNum << endl;
    cout << maxm << endl;
}

int main() {
    int tt;
    cin >> tt;
    for(int i = 1; i <= tt; i++) {
        solve(i);
    }
    return 0;
}
---------------------------------------------------------------------



You want to cut a piece of paper by a certain fixed rule to make some pieces of white or 
blue colored square paper with various sizes.  
 
If the size of the entire paper is N×N (N = 2^K; 1 <= K <= 7; K = natural number), the cutting rules
are as below.
 
‘If the entire piece of paper is not colored the same, cut the middle part horizontally and vertically 
to divide it into the same sized four pieces of paper, 
(N/2)×(N/2), as with I, II, III, IV in < FIG. 2 >. 

For each I, II, III and IV, cut and divide again in the same way if one entire piece of paper 
is not colored the same, and make them into the same sized four pieces of paper. Continue until each and 
every piece of paper has only one color of white or blue.’
 
When you finish, < FIG. 3 > shows the first division of < FIG. 1 > and < FIG. 4 > 
shows the final version of 9 pieces of white paper and 7 pieces of blue paper of various sizes.
 
If the length of an edge of the first given piece of paper, N, and 
the color information (white or blue) inside each square are given, create a calculation program
 that assesses how many white/blue pieces of paper are.
 
Time limit: 1 second (java: 2 seconds) 
 
[Input]
 
Input may include many test cases. The number of test cases, T, is given on the first line of input and then the amount of T of test cases is given in a line. (T <= 30)
The length of an edge of the first given piece of paper, N, is given for the first line of each test case.
From the next line through to the amount of N lines, the color information is given separately as blanks. 0 indicates white and 1 indicates blue.
 
[Output]
 
For each test case, you should print "Case #T" in the first line where T means the case number. 
 
For each test case, you should output the number of white pieces of paper and blue pieces of paper separately as blanks on the first line of each test case.
 
[I/O Example]
Input 
2
8
1 1 0 0 0 0 1 1
1 1 0 0 0 0 1 1
0 0 0 0 1 1 0 0
0 0 0 0 1 1 0 0
1 0 0 0 1 1 1 1
0 1 0 0 1 1 1 1 
0 0 1 1 1 1 1 1
0 0 1 1 1 1 1 1
 
 
16
1 0 0 1 0 0 0 0 0 0 1 1 0 1 1 1
1 1 0 1 0 1 1 0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 1 1 1 1 0 0 1 0 0 1
1 1 0 0 1 0 0 1 0 0 1 0 1 1 1 0
0 1 1 1 0 0 1 1 0 0 1 0 0 1 1 1
1 0 1 1 0 0 0 1 0 1 0 1 0 0 1 1
1 1 1 1 1 1 0 0 1 1 1 1 1 0 0 0
1 1 0 1 0 1 0 0 1 0 1 1 1 0 0 1
1 1 1 1 1 1 0 0 1 0 1 1 0 1 1 0
1 0 0 1 1 1 0 0 0 0 1 1 1 1 0 0
1 0 0 1 1 1 1 0 0 0 1 1 0 1 0 1
1 1 1 0 1 1 0 0 1 1 1 1 1 1 0 1
1 1 1 1 1 1 0 0 0 0 1 1 1 1 0 0
1 1 1 1 1 1 0 1 1 1 1 1 1 1 0 0
1 1 0 0 0 0 0 0 1 1 0 1 1 0 0 0
1 1 0 0 1 1 0 0 0 1 1 1 1 0 0 0
 
 
 
Output
 
Case #1
9 7
 
Case #2
88 99
//Nilarnab
#include<bits/stdc++.h>
using namespace std;

int a[130][130];
int bc,wc;




int divide(int r1, int r2, int c1, int c2){
    set<int>colors;
    
    for(int i=r1; i<= r2; i++){
        for(int j = c1; j<= c2; j++){
         colors.insert(a[i][j]) ;
        }
    }
    if(colors.size()>=2) return -1;
    else if(a[r1][c1]==0)return 0;
    else return 1;
    
    
}

void f(int r1, int r2, int c1, int c2){
    
   int val = divide(r1,r2,c1,c2);
    
    
    if(val==-1){
        int m1 = (r1+r2)>>1;
        int m2 = (c1+c2)>>1;
        
        f(r1,m1,c1,m2);
        f(m1+1,r2,c1,m2);
        f(r1,m1,m2+1, c2);
        f(m1+1,r2,m2+1,c2);
       



    }else if(val==0){
        wc++;

    }else bc++;
    
}

void solve(){
    int n;
    cin>>n;
    wc=0, bc=0;
    
    for(int i=0 ; i<n ; i++){
        for(int j =0 ; j< n ; j++)cin>>a[i][j];

    }
    f(0,n-1,0,n-1);
    cout<<wc<<" "<<bc<<endl;
    
    


}

int main(){

    int t;
    cin>>t;
    while(t--){
        solve();

    }
    return 0;

}


Solution : 
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define debug(x) cout << '>' << #x << ':' << x << endl;
const int maxn = 129;
int white = 0, blue = 0;

bool checkSame(bool arr[maxn][maxn], int sti, int stj, int size)
{
	bool color = arr[sti][stj];
	for(int i = sti; i < sti + size; i++){
		for(int j = stj; j < stj + size; j++){
			if(arr[i][j] != color){
				return false;
			}
		}
	}
	return true;
}

void solve(bool arr[maxn][maxn], int size, int sti, int stj)
{
	bool same = checkSame(arr, sti, stj, size);
	
	if(!same){
		solve(arr, size / 2, sti, stj);
		solve(arr, size / 2, sti + size/2, stj);
		solve(arr, size / 2, sti, stj + size/2);
		solve(arr, size / 2, sti + size/2, stj + size/2);
	}
	else{
		(arr[sti][stj]) ? ++blue : ++white ;
	}
}

int main()
{
	int test ;
	cin >> test ;
	for(int l = 1; l <= test; l++){
		white = 0;
		blue = 0;
		int size ;
		cin >> size;
		bool arr[maxn][maxn];
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				cin >> arr[i][j] ;
			}
		}
		solve(arr, size, 0, 0);
		cout << "Case #" << l << endl;
		cout << white << " " << blue << endl;
	}
	return 0;
}
// optimized approach using prefix sum of matrix

#include <iostream>
using namespace std;
const int maxn = 129;
int white = 0, blue = 0;
void solve(int arr[maxn][maxn], int size, int si,int sj)
{
    if( size == 0)
    return;
    int sum = arr[size + si - 1][size + sj - 1];
    if(sj - 1 >= 0)
    sum -= arr[size + si - 1][sj - 1];
    if(si - 1 >= 0)
    sum -= arr[si - 1][sj + size - 1];
    if( si - 1 >= 0 && sj - 1 >= 0)
    sum += arr[si - 1][sj - 1];
    if(si == 4 && sj == 1)
    cout<<sum<<endl;
    if(sum == 0)
    {
       // cout<<si<<"white"<<sj<<" "<<size<<" "<<white<<endl;
        white++;
        return;
    }
    if(sum == size * size)
    {
     //cout<<si<<"blue"<<sj<<" "<<size<<" "<<blue<<endl;
     blue++;
     return;
    }
    solve(arr, size / 2, si, sj);
    solve(arr, size / 2,  si + size/2, sj);
    solve(arr, size / 2, si, sj + size/2);
    solve(arr, size / 2, si + size / 2, sj + size / 2);
}
int main() {
    int test ;
	cin >> test ;
	for(int l = 1; l <= test; l++){
		white = 0;
		blue = 0;
		int size ;
		cin >> size;
		int arr[maxn][maxn];
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
                int a;
                cin>>a;
                if( i == 0 && j == 0)
                 arr[i][j] = a;
                else if( i == 0)
                arr[i][j] = a + arr[i][j - 1];
                else if( j == 0)
                arr[i][j] = a + arr[i - 1][j];
                else
                arr[i][j] = a + arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1];
			}
		}
		solve(arr, size, 0, 0);
		cout << "Case #" << l << endl;
		cout << white << " " << blue << endl;
	}
	return 0;
}

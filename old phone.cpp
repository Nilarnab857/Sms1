// lengthy see implementation again


/*
https://www.careercup.com/question?id=5680648437104640

You are given an old touch smartphone numbers having dial pad and calculator app.
Aim: The goal is to type a number on dialpad.

But as phone is old, some of the numbers and some operations can't be touched.
For eg. 2,3,5,9 keys are not responding , i.e you cannot use them
But you can always make a number using other numbers and operations in Calculator. There could be multiple ways of making a number

Calculator have 1-9 and +,-,*,/,= as operations. Once you have made the number in Calculator you can copy the number and use it.

You have to find minimum number to touches required to obtain a number.

#Input:#
There will be multiple Test cases .Each test case will consist of 4 lines
1) First line will consist of N,M,O
	N: no of keys working in Dialpad (out of 0,1,2,3,4,5,6,7,8,9)
	M:types of operations supported (+,-,*,/)
	O: Max no of touches allowed
2) second line of input contains the digits that are working e.g 0,2,3,4,6.
3) Third line contains the valued describing operations, 1(+),2(-),3(*),4(/)
4) fourth line contains the number that we want to make .

#Output:#
Output contains 1 line printing the number of touches required to make the number


#Sample Test Case:#
5 
5 3 5
1 2 4 6 0
1 2 3
5
6 4 5 
1 2 4 6 9 8
1 2 3 4
91
6 2 4
0 1 3 5 7 9
1 2 4
28
5 2 10
1 2 6 7 8
2 3
981
6 3 5
1 4 6 7 8 9
1 2 3
18

#Output:#
4
2 
5
9
2



If you have to type 18-> 2 operations. (Each touch is considered an operation),br> If you have to type 5 -> '1+4=' that requires 4 operations. There could be other ways to make '5'.
*/
#include <iostream>
#include <cstring> // Required for memset if you use it

using namespace std;

int digs[10];
int ops[4];

#define MAXVAL 100000
#define INF 1000000000

int mintouches[1000005];
int generated[1000005];
int queue[2000005]; // Fixed name to avoid 'q' vs 'queue' conflicts

int N, M, O, target;
int gencnt = 0, front = 0, rear = 0;

void reset() {
    // Safely initializing to infinity without memset byte-corruption
    for(int i = 0; i <= MAXVAL; i++) {
        mintouches[i] = INF;
    }
    front = 0;
    rear = 0;
    gencnt = 0;
}

int applyop(int a, int b, int op) {
    if (op == 1) return a + b;
    if (op == 2) return a - b;
    if (op == 3) return a * b;
    if (op == 4) {
        if (b == 0) return -1; // Division by zero guard
        return a / b;
    }
    return -1; 
}

void dfs(int cur, int len) {
    if (cur > MAXVAL) return;
    
    if (cur > 0 || len == 1) {
        if (mintouches[cur] > len) {
            mintouches[cur] = len;
            generated[gencnt++] = cur;
            queue[rear++] = cur; // Fixed: was queur and val
        }
    }
    
    // Fixed: Loop to N (digits), not M (operators)
    for (int i = 0; i < N; i++) {
        if (cur == 0 && len > 0) continue; // Fixed: was leng
        
        long long next = (long long)cur * 10 + digs[i];
        
        if (next <= MAXVAL) {
            dfs((int)next, len + 1);
        }
    }
}

void solve() {
    cin >> N >> M >> O;
    for (int i = 0; i < N; i++) cin >> digs[i];
    for (int i = 0; i < M; i++) cin >> ops[i]; // Fixed: was cins
    cin >> target;
    
    // Fixed: Bootstrap DFS using N (digits), not M
    for (int i = 0; i < N; i++) {
        dfs(digs[i], 1);
    }
    
    while (front < rear) {
        int num = queue[front++]; // Fixed: was q
        int cost = mintouches[num];
        
        if (cost > O) continue;
        
        for (int i = 0; i < gencnt; i++) {
            int oper = generated[i];
            int opercost = mintouches[oper];
            
            if (opercost > O) continue;
            
            for (int k = 0; k < M; k++) {
                int next = applyop(num, oper, ops[k]);
                
                if (next >= 0 && next <= MAXVAL) {
                    // +2 accounts for the operator press and the '=' press
                    int nextcost = cost + opercost + 2; 
                    
                    // Fixed variable names: maxtouches -> O, next_val -> next
                    if (nextcost <= O && nextcost < mintouches[next]) {
                        mintouches[next] = nextcost;
                        queue[rear++] = next;
                    }
                }
            }
        }
    }
    
    if (mintouches[target] <= O) {
        cout << mintouches[target] << "\n";
    } else {
        cout << -1 << "\n";
    }
}

int main() {
    // Fast I/O is good practice here
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tt;
    if (cin >> tt) {
        while (tt--) {
            reset();
            solve();
        }
    }
    return 0;
}

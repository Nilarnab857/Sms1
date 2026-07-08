//binrary tree given as string (root(lefttree)(righttree)) recursively
//find sum at depth k

/*
3 
(0(5(6()())(-4()(9()())))(7(1()())(3()())))
*/

//Nilarnabs OP approach
#include <bits/stdc++.h>
using namespace std;
bool isdigit(char x){
    return x>= '0' && x<= '9';
    
}

int main() {
	int k;
	cin>>k;
	string s;
	cin>>s;
	
	
	int curnum=0, sign =1, lev=-1;
	int ans=0;
	
	
	for(int i=0 ; i< s.size(); i++){
	    if(isdigit(s[i])){
	        curnum = curnum*10+ (s[i]-'0');
	        
	    }else if(s[i]=='('){
	        if(lev==k){
	            ans+=(sign *curnum);
	            
	        }
	        
	        lev++;
	       curnum=0;
	       sign =1;
	       
	    }else if( s[i]==')'){
	        if(lev==k){
	            ans+=(sign *curnum);
	            
	        }
	        lev--;
	        curnum=0;
	        sign =1;
	        
	    }else if(s[i]=='-'){
	        sign =-1;
	        curnum=0;
	        
	        
	    }
	}
	
	cout<<ans<<endl;
	
	

}


///standard approach generalisation
#include <iostream>
#include <string>

using namespace std;

// 1. Manually implement the structural representation
struct Node {
    int val;
    Node* left;
    Node* right;
    
    Node(int v) {
        val = v;
        left = nullptr;
        right = nullptr;
    }
};

// Phase 1: Recursive String Parsing
Node* buildTree(const string& s, int& i) {
    if (i >= s.length() || s[i] != '(') return nullptr;
    
    i++; // Skip the opening '('
    
    // Check for an empty node "()"
    if (s[i] == ')') {
        i++; // Skip the closing ')'
        return nullptr;
    }

    // Parse the node's integer value manually
    int sign = 1;
    int num = 0;
    
    if (s[i] == '-') {
        sign = -1;
        i++;
    }
    
    while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
        num = num * 10 + (s[i] - '0');
        i++;
    }

    // Create the current node
    Node* root = new Node(sign * num);

    // Recursively build left and right subtrees
    root->left = buildTree(s, i);
    root->right = buildTree(s, i);

    i++; // Skip the closing ')' for the current node
    
    return root;
}

// Phase 2: Standard DFS Traversal
void calculateTargetSum(Node* root, int current_depth, int target_depth, int& sum) {
    if (root == nullptr) {
        return;
    }
    
    // If we reach the target depth, add to the sum
    if (current_depth == target_depth) {
        sum += root->val;
    }
    
    // Continue traversing down the tree
    calculateTargetSum(root->left, current_depth + 1, target_depth, sum);
    calculateTargetSum(root->right, current_depth + 1, target_depth, sum);
}

int main() {
    int k;
    cin >> k;
    
    string s;
    cin >> s;

    // Start parsing from index 0
    int index = 0;
    Node* root = buildTree(s, index);

    int target_sum = 0;
    calculateTargetSum(root, 0, k, target_sum);

    cout << target_sum << endl;

    return 0;
}



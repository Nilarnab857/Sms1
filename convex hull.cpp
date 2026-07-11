/*
Given random points in a 2-D plane, construct a convex polygon with minimum area of covering and 
which encompasses all the given points.
*/
#include <iostream>
using namespace std;

struct Point {
    long long x, y;
};

int n;
Point pts[100005];
Point temp[100005]; // For merge sort
Point hull[100005]; // Acts as our stack

// The golden formula: Returns >0 if left turn, <0 if right turn
long long ccw(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 1. Manual Merge Sort (Sort by X, then by Y)
void merge(int l, int m, int r) {
    int i = l, j = m + 1, k = l;
    while(i <= m && j <= r) {
        // Primary sort by X, secondary sort by Y
        if(pts[i].x < pts[j].x || (pts[i].x == pts[j].x && pts[i].y < pts[j].y)) {
            temp[k++] = pts[i++];
        } else {
            temp[k++] = pts[j++];
        }
    }
    while(i <= m) temp[k++] = pts[i++];
    while(j <= r) temp[k++] = pts[j++];
    for(int p = l; p <= r; p++) pts[p] = temp[p];
}

void merge_sort(int l, int r) {
    if(l < r) {
        int m = l + (r - l) / 2;
        merge_sort(l, m);
        merge_sort(m + 1, r);
        merge(l, m, r);
    }
}

void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
    }

    // Edge case: A hull needs at least 3 points
    if (n < 3) {
        // Handle based on problem constraints (e.g., print all points)
        return;
    }

    merge_sort(0, n - 1);

    int k = 0; // k is the size of our hull
    
    for(int i =0 ; i< n ; i++){
        
        while(k>=2 && ccw(hull[k-2], hull[k-1], pts[i])<=0){
            k--;
        }
        hull[k++] = pts[i];
        
    }
    int t= k+1;
    for(int i = n-2; i>=0 ; i-- ){
        while(k>= t && ccw(hull[k-2], hull[k-1], pts[i])<=0){
            k--;
            
        }
        hull[k++]pts[i]
    }

}

int main() {
    int tt = 1;
    // cin >> tt;
    while(tt--) solve();
    return 0;
}

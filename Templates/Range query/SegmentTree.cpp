#include <bits/stdc++.h>
#define int int64_t
using namespace std;
struct Node{
//contents of the node
    int sum;
//Neutral value used in padding 
    Node(){
        sum = 0;
    }
//initialized value of the node 
    Node(int x){
        sum = x;
    }
//changing pattern
    void change(int x){
        sum += x;
    }
};
struct Segtree{
//Initialization of segment tree with 0-indexed and half interval
    int size;
    vector<Node> segData;
    Segtree(int n){
        size = 1;
        while(size < n) size *= 2;
        segData.assign(2 * size, Node());
    }
    void init(vector<int> &arr, int cur, int l, int r){
        if(r-l == 1){
            if(l < arr.size()) segData[cur] = Node(arr[l]);
            return;
        }
        int mid = (l+r)/2;
        init(arr, 2*cur+1, l, mid);
        init(arr, 2*cur+2, mid, r);
        segData[cur] = merge(segData[2*cur+1], segData[2*cur+2]);
    }
    void init(vector<int> &arr){
        init(arr, 0, 0, size);
    }
// calculation of the parent
    Node merge(Node &lf, Node &ri){
        Node ans = Node();
        ans.sum = lf.sum + ri.sum;
        return ans;
    }
//Set and get each in O(lg n)
    void set(int idx, int val, int cur, int l, int r){
        if(r - l == 1){
            segData[cur].change(val);
            return;
        }
        int mid = (r + l) / 2;
        if(idx < mid)
            set(idx, val, 2 * cur + 1, l, mid);
        else
            set(idx, val, 2 * cur + 2, mid, r);
        segData[cur] = merge(segData[2 * cur + 1], segData[2 * cur + 2]);
    }
    void set(int idx, int val){
        set(idx, val, 0, 0, size);
    }
    Node get(int lq, int rq, int cur, int l, int r){
        if(l >= lq && r <= rq) return segData[cur];
        if(l >= rq || r <= lq) return Node();
        int mid = (r + l) / 2;
        Node lf = get(lq, rq, 2 * cur + 1, l, mid);
        Node ri = get(lq, rq, 2 * cur + 2, mid, r);
        return merge(lf, ri);
    }
    Node get(int lq, int rq){
        return get(lq, rq, 0, 0, size);
    }
};

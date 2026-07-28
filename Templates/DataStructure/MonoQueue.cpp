struct monoQueue {
    struct Node {
        int idx, val;
        Node(int x, int i) {
            idx = i;
            val = x;
        }
    };
    deque<Node> d;
    void push(int l, int r, int x) {
        while (!d.empty() && d.front().idx < l) d.pop_front();
        while (!d.empty() && x <= d.back().val) d.pop_back(); // <<< min  
        d.push_back(Node(x, r));
    }
    int get() {
        return d.front().val;
    }
};

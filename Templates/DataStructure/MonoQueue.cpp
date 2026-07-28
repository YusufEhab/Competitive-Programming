struct monoQueue {
    struct Node {
        int idx, val;
        Node(int x, int i) {
            idx = i;
            val = x;
        }
    };
    deque<Node> d;
    void check(int l) {
        while (!d.empty() && d.front().idx < l) d.pop_front();
    }
    void push(int val, int idx) {
        while (!d.empty() && val <= d.back().val) d.pop_back();
        d.push_back(Node(val, idx));
    }
    int front() {
        return d.front().val;
    }
};

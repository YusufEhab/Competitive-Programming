struct TwoStackQ {
    struct Node {
        int oro, val;
        Node() {
            oro = val = 0;
        }
        Node(int x) {
            oro = x;
            val = x;
        }
    };
    stack<Node> a, b;
    int size() {
        return a.size() + b.size();
    }
    void merge(Node &lf, Node &rt) {
        lf.oro |= rt.oro;
    }
    void push(int val) {
        Node ne = Node(val);
        if (!a.empty()) merge(ne, a.top());
        a.push(ne);
    }
    void move() {
        while (!a.empty()) {
            auto ne = Node(a.top().val);
            if (!b.empty()) merge(ne, b.top());
            b.push(ne); a.pop();
        }
    }
    void pop() {
        if (b.empty()) move();
        if (!b.empty()) b.pop();
    }
    int get() {
        Node res;
        if (!a.empty()) merge(res, a.top());
        if (!b.empty()) merge(res, b.top());
        return res.oro;
    }
} q;

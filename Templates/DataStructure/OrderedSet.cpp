#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OrderedSet;
void erase(OrderedSet &st, int val){
    int rank = st.order_of_key(val);
    auto it = st.find_by_order(rank);
    st.erase(it);
}
// multi set/map has reversed lower/upper bound
// order_of_key(x), no of elements < x 
// find_by_order(k), Kth number in the set

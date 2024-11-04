/**
 * Author: Mohamed ElHagry
 * Description: Executes point update/ range queries both in O($(\log(N))^2$) on a grid of size O($N \mul N$) for invertible functions, can query prefix for all functions
*/

const int N = 1e3 + 5;

struct BIT2D {
    vector<vector<ll>> tree;
    BIT2D(int _n = N) {
        tree.resize(_n + 2, vector<ll>(_n + 2));
    }
    ll get_prefix(int i, int j) {
        ++i;
        ++j;
        ll sum = 0;
        for (int x = i; x >= 1; x -= x & -x) {
            for (int y = j; y >= 1; y -= y & -y) {
                sum += tree[x][y];
            }
        }
        return sum;
    }
    void update_point(int i, int j, ll v) {
        ++i;
        ++j;
        for (int x = i; x < tree.size(); x += x & -x) {
            for (int y = j; y < tree.size(); y += y & -y) {
                tree[x][y] += v;
            }
        }
    }
    ll query(int x1, int y1, int x2, int y2) {
        return get_prefix(x2, y2) - get_prefix(x1 - 1, y2) - get_prefix(x2, y1 - 1) + get_prefix(x1 - 1, y1 - 1);
    }
};

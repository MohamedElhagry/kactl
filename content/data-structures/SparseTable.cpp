/**
 * Author: Hagry
 * Description: Nice sparse table template
 */
struct SparseTable {
    int n, lg;
    vector<vector<int>> sparseTable;
    vector<int> bigPow;
    SparseTable(vector<int> &a) {
        n = a.size();
        lg = __lg(n) + 2;
        sparseTable.resize(n, vector<int>(lg));
        bigPow.resize(n + 1);
        for (int k = 0; k < lg; k++) {
            for (int i = 0; i + (1 << k) - 1 < n; i++) {
                if (k == 0)
                    sparseTable[i][k] = a[i];
                else
                    sparseTable[i][k] = max(sparseTable[i][k - 1], sparseTable[i + (1 << (k - 1))][k - 1]);
            }
        }
        bigPow[1] = 0;
        for (int k = 2; k <= n; k++)
            bigPow[k] = bigPow[k / 2] + 1;
    }
    int query(int l, int r) {
        int len = r - l + 1;
        int k = bigPow[len];
        return max(sparseTable[l][k], sparseTable[r - (1 << k) + 1][k]);
    }
};
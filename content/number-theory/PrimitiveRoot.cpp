/**
 * Author: Gamal
 * Description: Remember that $\phi(y)$ is the euler phi function (number of elements less that me that are coprime with me)$\\$
 * $Ord(x)$ is the least positive number such that $x^{ord(x)} = 1 \pmod n\\$
 *  Number of $x$ with $Ord(x) = y$ is $\phi(y)\\$
 *  All possible $Ord(x)$ divide $\phi(n)\\$
 *  $Ord(a^k) = Ord(a) \mathbin{/}  \gcd(k,Ord(a))$
 */
int powmod(int a, int b, int p) {
    int res = 1;
    while (b)
        if (b & 1)
            res = int(res * 1ll * a % p), --b;
        else
            a = int(a * 1ll * a % p), b >>= 1;
    return res;
}
int generator(int p) {
    vector<int> fact;
    int phi = p - 1, n = phi;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back(n);
    for (int res = 2; res <= p; ++res) {
        bool ok = true;
        for (size_t i = 0; i < fact.size() && ok; ++i)
            ok &= powmod(res, phi / fact[i], p) != 1;
        if (ok) return res;
    }
    return -1;
}
#include<bits/stdc++.h>
using namespace std;

namespace BIGINT {
    const int BASE = 1000;
    const int BASE_WIDTH = 3;
    struct Bigint {
        int sign; // 0, 1, -1
        vector<int> d;

        Bigint() : sign(0) {}
        Bigint(long long x) { *this = x; }
        Bigint(const string &s) { *this = s; }

        void trim() {
            while (!d.empty() && d.back() == 0) d.pop_back();
            if (d.empty()) sign = 0;
        }

        Bigint& operator=(long long x) {
            d.clear();
            if (x == 0) { sign = 0; return *this; }
            sign = x < 0 ? -1 : 1;
            unsigned long long val = x < 0 ? -x : x;
            while (val) { d.push_back(val % BASE); val /= BASE; }
            return *this;
        }

        Bigint& operator=(const string &s) {
            d.clear(); sign = 1;
            if (s.empty()) { sign = 0; return *this; }
            int pos = 0;
            if (s[0] == '-') { sign = -1; pos = 1; }
            else if (s[0] == '+') pos = 1;
            while (pos < (int)s.size() && s[pos] == '0') pos++;
            if (pos == (int)s.size()) { sign = 0; return *this; }
            for (int i = (int)s.size() - 1; i >= pos; i -= BASE_WIDTH) {
                int x = 0;
                int l = max(pos, i - BASE_WIDTH + 1);
                for (int j = l; j <= i; ++j) x = x * 10 + (s[j] - '0');
                d.push_back(x);
            }
            trim(); return *this;
        }

        bool operator<(const Bigint &b) const {
            if (sign != b.sign) return sign < b.sign;
            if (sign == 0) return false;
            if (d.size() != b.d.size()) return sign > 0 ? d.size() < b.d.size() : d.size() > b.d.size();
            for (int i = (int)d.size() - 1; i >= 0; --i)
                if (d[i] != b.d[i]) return sign > 0 ? d[i] < b.d[i] : d[i] > b.d[i];
            return false;
        }
        bool operator>(const Bigint &b) const { return b < *this; }
        bool operator<=(const Bigint &b) const { return !(*this > b); }
        bool operator>=(const Bigint &b) const { return !(*this < b); }
        bool operator==(const Bigint &b) const { return sign == b.sign && d == b.d; }
        bool operator!=(const Bigint &b) const { return !(*this == b); }

        Bigint operator-() const { Bigint r = *this; if (r.sign != 0) r.sign = -r.sign; return r; }
        
        Bigint operator+(const Bigint &b) const {
            if (sign == 0) return b;
            if (b.sign == 0) return *this;
            if (sign == b.sign) {
                Bigint r; r.sign = sign;
                int n = max(d.size(), b.d.size()), carry = 0;
                for (int i = 0; i < n || carry; ++i) {
                    int v = carry + (i < d.size() ? d[i] : 0) + (i < b.d.size() ? b.d[i] : 0);
                    r.d.push_back(v % BASE);
                    carry = v / BASE;
                }
                return r;
            }
            return *this - (-b);
        }

        Bigint operator-(const Bigint &b) const {
            if (b.sign == 0) return *this;
            if (sign == 0) return -b;
            if (sign != b.sign) return *this + (-b);
            Bigint A = this->abs(), B = b.abs();
            if (A < B) return -(b - *this);
            Bigint r; r.sign = sign;
            int carry = 0;
            for (int i = 0; i < d.size(); ++i) {
                int v = d[i] - carry - (i < b.d.size() ? b.d[i] : 0);
                if (v < 0) { v += BASE; carry = 1; } else carry = 0;
                r.d.push_back(v);
            }
            r.trim(); return r;
        }

        Bigint mul_small(int m) const {
            if (sign == 0 || m == 0) return Bigint(0);
            Bigint r; r.sign = sign;
            long long carry = 0;
            for (int x : d) {
                long long v = 1LL * x * m + carry;
                r.d.push_back(v % BASE);
                carry = v / BASE;
            }
            while (carry) { r.d.push_back(carry % BASE); carry /= BASE; }
            r.trim(); return r;
        }

        // FFT Core
        using cd = complex<double>;
        static void fft(vector<cd>& a, bool invert) {
            int n = a.size();
            for (int i = 1, j = 0; i < n; i++) {
                int bit = n >> 1;
                for (; j & bit; bit >>= 1) j ^= bit;
                j ^= bit;
                if (i < j) swap(a[i], a[j]);
            }
            for (int len = 2; len <= n; len <<= 1) {
                double ang = 2 * M_PI / len * (invert ? -1 : 1);
                cd wlen(cos(ang), sin(ang));
                for (int i = 0; i < n; i += len) {
                    cd w(1);
                    for (int j = 0; j < len / 2; j++) {
                        cd u = a[i + j], v = a[i + j + len / 2] * w;
                        a[i + j] = u + v;
                        a[i + j + len / 2] = u - v;
                        w *= wlen;
                    }
                }
            }
            if (invert) for (cd & x : a) x /= n;
        }

        Bigint operator*(const Bigint &b) const {
            if (sign == 0 || b.sign == 0) return Bigint(0);
            int n = d.size(), m = b.d.size();
            if (min(n, m) < 80) { // Naive for small
                Bigint r; r.sign = sign * b.sign;
                r.d.assign(n + m, 0);
                for (int i = 0; i < n; ++i) {
                    long long carry = 0;
                    for (int j = 0; j < m || carry; ++j) {
                        long long v = r.d[i + j] + carry + 1LL * d[i] * (j < m ? b.d[j] : 0);
                        r.d[i + j] = v % BASE;
                        carry = v / BASE;
                    }
                }
                r.trim(); return r;
            }
            // FFT for large
            int N = 1; while (N < n + m) N <<= 1;
            vector<cd> fa(N), fb(N);
            for (int i = 0; i < n; i++) fa[i] = d[i];
            for (int i = 0; i < m; i++) fb[i] = b.d[i];
            fft(fa, false); fft(fb, false);
            for (int i = 0; i < N; i++) fa[i] *= fb[i];
            fft(fa, true);
            Bigint r; r.sign = sign * b.sign;
            long long carry = 0;
            for (int i = 0; i < N || carry; i++) {
                long long v = carry + (i < N ? (long long)(fa[i].real() + 0.5) : 0);
                r.d.push_back(v % BASE);
                carry = v / BASE;
            }
            r.trim(); return r;
        }

        Bigint operator/(const Bigint &b) const {
            if (b.sign == 0) return Bigint(0);
            Bigint A = this->abs(), B = b.abs();
            if (A < B) return Bigint(0);
            Bigint res; res.sign = sign * b.sign;
            res.d.resize(A.d.size());
            Bigint cur(0);
            for (int i = (int)A.d.size() - 1; i >= 0; --i) {
                cur = cur.mul_small(BASE) + A.d[i];
                int L = 0, R = BASE - 1, best = 0;
                while (L <= R) {
                    int mid = (L + R) >> 1;
                    if (!(B.mul_small(mid) > cur)) { best = mid; L = mid + 1; }
                    else R = mid - 1;
                }
                res.d[i] = best;
                cur = cur - B.mul_small(best);
            }
            res.trim(); return res;
        }

        Bigint operator%(const Bigint &b) const { return *this - (*this / b) * b; }
        Bigint abs() const { Bigint r = *this; if (r.sign < 0) r.sign = 1; return r; }
        
        string toString() const {
            if (sign == 0) return "0";
            stringstream ss;
            if (sign < 0) ss << '-';
            ss << d.back();
            for (int i = (int)d.size() - 2; i >= 0; --i)
                ss << setfill('0') << setw(BASE_WIDTH) << d[i];
            return ss.str();
        }
        friend ostream& operator<<(ostream& os, const Bigint& b) { os << b.toString(); return os; }
        friend istream& operator>>(istream& is, Bigint& b) { string s; is >> s; b = s; return is; }
    };
}
using namespace BIGINT;
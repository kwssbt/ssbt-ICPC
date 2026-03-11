#include<bits/stdc++.h>
using namespace std;
namespace BIGINT {
    const int BASE = 1000;
    const int BASE_WIDTH = 3;
    struct Bigint {
        int sign;
        vector<int> d;
        Bigint(): sign(0) {}
        Bigint(long long x) { *this = x; }
        Bigint(const string &s) { *this = s; }
        friend istream& operator>>(istream &in, Bigint &x) {string s;in >> s;x = Bigint(s);return in;}
        string toString() const {
            if (sign == 0) return "0";
            stringstream ss;
            if (sign < 0) ss << '-';
            ss << (d.empty() ? 0 : d.back());
            for (int i = (int)d.size() - 2; i >= 0; --i) {
                ss << setw(BASE_WIDTH) << setfill('0') << d[i];
            }
            return ss.str();
        }
        friend ostream& operator<<(ostream& os,const Bigint& num){os<<num.toString();return os;}
        Bigint& operator=(long long x) {
            d.clear();
            if (x == 0) { sign = 0; return *this; }
            sign = x < 0 ? -1 : 1;
            if (x < 0) x = -x;
            while (x) { d.push_back(int(x % BASE)); x /= BASE; }
            return *this;
        }
        Bigint& operator=(const string &s) {
            d.clear();
            if (s.empty()) { sign = 0; return *this; }
            int pos = 0;
            sign = 1;
            if (s[0] == '-') { sign = -1; pos = 1; }
            else if (s[0] == '+') { pos = 1; }
            while (pos < (int)s.size() && s[pos] == '0') pos++;
            if (pos >= (int)s.size()) { sign = 0; return *this; }
            for (int i = (int)s.size() - 1; i >= pos; i -= BASE_WIDTH) {
                int x = 0;
                int l = max(pos, i - BASE_WIDTH + 1);
                for (int j = l; j <= i; ++j) x = x * 10 + (s[j] - '0');
                d.push_back(x);
            }
            trim();
            return *this;
        }
        void trim() {
            while (!d.empty() && d.back() == 0) d.pop_back();
            if (d.empty()) sign = 0;
        }
        Bigint abs() const { Bigint r = *this; if (r.sign < 0) r.sign = 1; return r; }
        int cmpAbs(const Bigint &b) const {
            if (d.size() != b.d.size()) return d.size() < b.d.size() ? -1 : 1;
            for (int i = (int)d.size() - 1; i >= 0; --i)
                if (d[i] != b.d[i]) return d[i] < b.d[i] ? -1 : 1;
            return 0;
        }
        bool operator<(const Bigint &b) const {
            if (sign != b.sign) return sign < b.sign;
            if (sign == 0) return false;
            int t = cmpAbs(b);
            return sign > 0 ? (t < 0) : (t > 0);
        }
        bool operator==(const Bigint &b) const { return sign == b.sign && d == b.d; }
        bool operator!=(const Bigint &b) const { return !(*this == b); }
        bool operator>(const Bigint &b) const { return b < *this; }
        bool operator<=(const Bigint &b) const { return !(*this > b); }
        bool operator>=(const Bigint &b) const { return !(*this < b); }
        Bigint operator-() const { Bigint r = *this; if (r.sign != 0) r.sign = -r.sign; return r; }
        Bigint operator+(const Bigint &b) const {
            if (sign == 0) return b;
            if (b.sign == 0) return *this;
            if (sign == b.sign) {
                Bigint r;
                r.sign = sign;
                const vector<int> &a = d, &bb = b.d;
                int n = max(a.size(), bb.size());
                r.d.assign(n, 0);
                int carry = 0;
                for (int i = 0; i < n; ++i) {
                    int v = carry;
                    if (i < (int)a.size()) v += a[i];
                    if (i < (int)bb.size()) v += bb[i];
                    carry = v >= BASE;
                    if (carry) v -= BASE;
                    r.d[i] = v;
                }
                if (carry) r.d.push_back(carry);
                r.trim();
                return r;
            } else {
                return *this - (-b);
            }
        }
        Bigint operator-(const Bigint &b) const {
            if (b.sign == 0) return *this;
            if (sign == 0) return -b;
            if (sign != b.sign) return *this + (-b);
            if (this->abs() == b.abs()) return Bigint(0);
            bool positiveResult = (this->abs().cmpAbs(b.abs()) > 0);
            const Bigint &A = positiveResult ? *this : b;
            const Bigint &B = positiveResult ? b : *this;
            Bigint r;
            r.sign = positiveResult ? sign : -sign;
            r.d.assign(A.d.size(), 0);
            int carry = 0;
            for (size_t i = 0; i < A.d.size(); ++i) {
                int av = A.d[i];
                int bv = (i < B.d.size() ? B.d[i] : 0);
                int cur = av - carry - bv;
                if (cur < 0) { cur += BASE; carry = 1; } else carry = 0;
                r.d[i] = cur;
            }
            r.trim();
            return r;
        }
        static Bigint mul_naive(const Bigint &a, const Bigint &b) {
            if (a.sign == 0 || b.sign == 0) return Bigint(0);
            Bigint r;
            r.sign = a.sign * b.sign;
            r.d.assign(a.d.size() + b.d.size(), 0);
            for (size_t i = 0; i < a.d.size(); ++i) {
                long long carry = 0;
                for (size_t j = 0; j < b.d.size() || carry; ++j) {
                    long long cur = r.d[i + j] + carry + 1LL * a.d[i] * (j < b.d.size() ? b.d[j] : 0);
                    r.d[i + j] = int(cur % BASE);
                    carry = cur / BASE;
                }
            }
            r.trim();
            return r;
        }
        using cd = complex<double>;
        static void fft(vector<cd> & a, bool invert) {
            int n = (int)a.size();
            static vector<int> rev;
            static vector<cd> roots{ {0,0}, {1,0} };
            if ((int)rev.size() != n) {
                int k = __builtin_ctz(n);
                rev.assign(n,0);
                for (int i = 0; i < n; ++i)
                    rev[i] = (rev[i>>1] >> 1) | ((i&1) << (k-1));
            }
            for (int i = 0; i < n; ++i)
                if (i < rev[i]) swap(a[i], a[rev[i]]);
 
            if ((int)roots.size() < n) {
                int k = __builtin_ctz(roots.size());
                roots.resize(n);
                while ((1 << k) < n) {
                    double angle = M_PI / (1 << k);
                    for (int i = 1 << (k-1); i < (1<<k); ++i) {
                        roots[2*i] = roots[i];
                        double ang = angle * (2*i+1 - (1<<k));
                        roots[2*i+1] = cd(cos(ang), sin(ang));
                    }
                    ++k;
                }
            }
            for (int len = 1; len < n; len <<= 1) {
                for (int i = 0; i < n; i += 2*len) {
                    for (int j = 0; j < len; ++j) {
                        cd u = a[i+j];
                        cd v = a[i+j+len] * roots[len + j];
                        a[i+j] = u + v;
                        a[i+j+len] = u - v;
                    }
                }
            }
            if (invert) {
                reverse(a.begin() + 1, a.end());
                for (int i = 0; i < n; ++i) a[i] /= n;
            }
        }
        static Bigint mul_fft(const Bigint &a, const Bigint &b) {
            if (a.sign == 0 || b.sign == 0) return Bigint(0);
            vector<cd> fa(a.d.begin(), a.d.end()), fb(b.d.begin(), b.d.end());
            int n = 1;
            while (n < (int)(a.d.size() + b.d.size())) n <<= 1;
            fa.resize(n); fb.resize(n);
 
            fft(fa, false); fft(fb, false);
            for (int i = 0; i < n; ++i) fa[i] *= fb[i];
            fft(fa, true);
 
            Bigint res;
            res.sign = a.sign * b.sign;
            res.d.assign(n, 0);
            long long carry = 0;
            for (int i = 0; i < n; ++i) {
                long long t = carry + (long long) (fa[i].real() + 0.5);
                res.d[i] = int(t % BASE);
                carry = t / BASE;
            }
            while (carry) {
                res.d.push_back(int(carry % BASE));
                carry /= BASE;
            }
            res.trim();
            return res;
        }
        Bigint operator*(const Bigint &b) const {
            size_t n = d.size(), m = b.d.size();
            if (n == 0 || m == 0) return Bigint(0);
            if (n < 60 || m < 60) return mul_naive(*this, b);
            return mul_fft(*this, b);
        }
        Bigint operator/(long long b) const {
            if (b == 0) return Bigint(0);
            if (sign == 0) return Bigint(0);
            Bigint res;
            res.sign = sign * (b < 0 ? -1 : 1);
            long long bb = llabs(b);
            res.d.assign(d.size(), 0);
            long long rem = 0;
            for (int i = (int)d.size() - 1; i >= 0; --i) {
                long long cur = d[i] + rem * BASE;
                res.d[i] = int(cur / bb);
                rem = cur % bb;
            }
            res.trim();
            return res;
        }
        long long operator%(long long b) const {
            if (b == 0) return 0;
            long long bb = llabs(b);
            long long rem = 0;
            for (int i = (int)d.size() - 1; i >= 0; --i)
                rem = (rem * BASE + d[i]) % bb;
            if (sign < 0) rem = -rem;
            return rem;
        }
        Bigint operator/(const Bigint &b) const {
            if (b.sign == 0) return Bigint(0);
            if (sign == 0) return Bigint(0);
            Bigint A = this->abs();
            Bigint B = b.abs();
            if (A < B) return Bigint(0);
            int n = A.d.size();
            Bigint res;
            res.sign = sign * b.sign;
            res.d.assign(n, 0);
            Bigint cur; 
            cur.sign = 0; 
            cur.d.clear();
            auto mul_small = [&](const Bigint &x, int m) {
            if (x.sign == 0 || m == 0) return Bigint(0);
            Bigint r;
            r.sign = x.sign;
            long long carry = 0;
            r.d.assign(x.d.size(), 0);
            for (int i = 0; i < (int)x.d.size(); i++) {
            long long t = 1LL * x.d[i] * m + carry;
            r.d[i] = int(t % BASE);
            carry = t / BASE;
        }
        while (carry) {
            r.d.push_back(int(carry % BASE));
            carry /= BASE;
        }
            r.trim();
            return r;
        };
        for (int i = n - 1; i >= 0; --i) {
            if (cur.sign != 0) cur.d.insert(cur.d.begin(), 0);
            if (cur.d.empty()) cur.d.push_back(A.d[i]);
            else cur.d[0] = A.d[i];
            cur.trim();
            if (cur.sign == 0) cur.sign = 1;
            int L = 0, R = BASE - 1, best = 0;
            while (L <= R) {
                int mid = (L + R) >> 1;
                Bigint t = mul_small(B, mid);
                if (!(t > cur)) { // t <= cur
                    best = mid;
                    L = mid + 1;
                } else R = mid - 1;
            }
            res.d[i] = best;
            if (best > 0) cur = cur - mul_small(B, best);
        }
        res.trim();
        return res;
    }
        Bigint operator%(const Bigint &b) const {
            Bigint q = (*this) / b;
            Bigint r = *this - q * b;
            return r;
        }
        Bigint& operator+=(const Bigint &rhs){ *this = *this + rhs; return *this; }
        Bigint& operator-=(const Bigint &rhs){ *this = *this - rhs; return *this; }
        Bigint& operator*=(const Bigint &rhs){ *this = *this * rhs; return *this; }
        Bigint& operator/=(const Bigint &rhs){ *this = *this / rhs; return *this; }
        Bigint& operator%=(const Bigint &rhs){ *this = *this % rhs; return *this; }
    };
}using namespace BIGINT;
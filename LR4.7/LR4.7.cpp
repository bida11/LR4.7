// Біда О. М., ІК-12. ЛР 4.7, варіант 1. Ряд Тейлора.
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    double xp, xk, dx, eps;
    cout << "xp, xk, dx, eps: ";
    if (!(cin >> xp >> xk >> dx >> eps) || !isfinite(xp)
        || !isfinite(xk) || !isfinite(dx) || !isfinite(eps)
        || dx <= 0 || eps <= 0 || xp > xk
        || (xk - xp) / dx > 1000000) {
        cerr << "Invalid input\n"; return 1;
    }
    const int m = int(floor((xk - xp) / dx + 1e-10));
    cout << "TABLE ln((x+1)/(x-1))\n" << setw(12) << "x"
        << setw(18) << "function" << setw(18) << "series"
        << setw(10) << "terms" << '\n';
    cout << fixed << setprecision(10);
    for (int j = 0; j <= m; ++j) {
        const double x = xp + j * dx;
        cout << setw(12) << x;
        if (abs(x) <= 1) {
            cout << "   undefined (require |x| > 1)\n";
            continue;
        }
        // a = a_n, q - верхня межа |a_(n+1)/a_n|.
        const double q = (1 / x) * (1 / x);
        double a = 2 / x, S = a;
        int n = 0;
        double next = a * q * (2 * n + 1) / (2 * n + 3);
        // Залишок ряду за модулем <= |next|/(1-q).
        while (abs(next) / (1 - q) >= eps && n < 1000000) {
            a = next; S += a; ++n;
            next = a * q * (2 * n + 1) / (2 * n + 3);
        }
        if (abs(next) / (1 - q) >= eps) {
            cout << "   convergence limit reached\n";
            continue;
        }
        const double f = abs(x) <= 2 ? log((x + 1) / (x - 1))
            : log1p(2 / (x - 1));
        cout << setw(18) << f << setw(18) << S
            << setw(10) << n + 1 << '\n';
    }
}

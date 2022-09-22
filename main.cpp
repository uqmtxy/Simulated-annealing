#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <set>
#include <queue>
#include <ctime>
#include <random>
#include <numeric>

using namespace std;

typedef long long ll;
typedef long double ld;

const double eps = 1e-7;

int n;

// генерирует действительное число от 0 до 1
double rnd() { return double(rand()) / RAND_MAX; }

// Количество ферзей, поставленных успешно
int f(vector<int>& p) {
	int s = 0;
	vector <int> d1(2 * n - 1, 0), d2(2 * n - 1, 0);
	for (int i = 0; i < n; i++) {
		if (d1[i + p[i]] == 0 && d2[n + i - p[i] - 1] == 0) {
			s++;
			d1[i + p[i]] = 1;
			d2[n + i - p[i] - 1] = 1;
		}
	}
	return s;
}

int main()
{

	cin >> n;

	mt19937 gen(time(0));

	//Генерируем начальное состояние
	vector <int> p(n);
	iota(p.begin(), p.end(), 0);
	shuffle(p.begin(), p.end(), gen);
	// Метод отжига
	int ans = f(p);
	double t = 1.0;
	for (int step = 0; step < 100000; step++) {

		t *= 0.99;
		if (ans == n) break;

		// p1 - новая перестановка
		vector <int> p1 = p;
		swap(p1[rand()%n], p1[rand()%n]);

		int val = f(p1);

		//cout << t << " " << val << endl;

		if (val > ans || (rnd() < exp(double(val - ans) / t))) {
			ans = val;
			p = p1;
		}
	}
	for (auto it : p) {
		cout << it+1 << " ";
	}
}
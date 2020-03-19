#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point
{
	int n;
	string follow;

	Point(int n, string follow) {
		this->n = n;
		this->follow = follow;
	}
};

int S, E;
string ans;
int visit[10001];

void init() {
	for (int i = 0; i <= 10001; i++) {
		visit[i] = 0;
	}
}

void bfs() {
	queue<Point> q;
	vector<char> temp;
	q.push(Point(S, ""));
	visit[S] = 1;

	while (!q.empty()) {
		int cn = q.front().n;
		string cf = q.front().follow;

		q.pop();

		if (cn == E) {
			ans = cf;
			return;
		}

		for (int i = 0; i < 4; i++) {
			// D
			if (i == 0) {
				int nn = (cn * 2) % 10000;

				if (visit[nn] == 1) continue;

				visit[nn] = 1;
				q.push(Point(nn, cf + "D"));
			}
			// S
			if (i == 1) {
				int nn = cn-1;
				if (nn == -1) {
					nn = 9999;
				}

				if (visit[nn] == 1) continue;

				visit[nn] = 1;
				q.push(Point(nn, cf + "S"));
			}
			// L
			if (i == 2) {
				int nn = (cn % 1000) * 10 + cn / 1000;
				if (visit[nn] == 1) continue;

				visit[nn] = 1;
				q.push(Point(nn, cf + "L"));
			}
			// R
			if (i == 3) {
				int nn = (cn % 10) * 1000 + (cn / 10);
				if (visit[nn] == 1) continue;

				visit[nn] = 1;
				q.push(Point(nn, cf + "R"));
			}

		}
	}
}

int main() {
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		// 입력
		cin >> S >> E;

		// 끝을 향해서 가자!
		bfs();

		// 출력
		for (int i = 0; i < ans.size(); i++) {
			printf("%c", ans[i]);
		}

		// 초기화
		init();
		ans = "";
		cout << "\n";
	}

	return 0;
}
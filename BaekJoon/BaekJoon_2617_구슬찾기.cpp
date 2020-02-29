#include<iostream>
#include <queue>

using namespace std;

struct Point
{
	int n, flag;
	Point(int n, int flag) {
		this->n = n;
		this->flag = flag;
	}
};

int N, K;
int ans;
int map[100][100];
int visit[100];
int count_1, count_2;

void init() {
	for (int i = 0; i < 100; i++) {
		visit[i] = 0;
	}
}

void bfs(int n, int flag) {
	queue<Point> q;
	q.push(Point(n, flag));
	visit[n] = 1;

	while (!q.empty()) {
		int cn = q.front().n;
		int f = q.front().flag;

		if (f == 1) count_1++;
		if (f == 2) count_2++;

		q.pop();

		for (int i = 1; i <= N; i++) {
			if (map[cn][i] == 0)
				continue;

			if (f != 0 && map[cn][i] != f)
				continue;

			if (visit[i] == 1) continue;

			visit[i] = 1;
			q.push(Point(i, map[cn][i]));
		}
	}

}

int main() {
	cin >> N >> K;

	for (int i = 0; i < K; i++) {
		int y, x;
		cin >> y >> x;
		// map 그리기
		map[y][x] = 1;
		map[x][y] = 2;
	}

	for (int i = 1; i <= N; i++) {
		bfs(i, 0);

		// 제외해보기
		if (count_1 > (N / 2) || count_2 > (N / 2)) {
			ans++;
		}

		// 초기화
		init();
		count_1 = 0;
		count_2 = 0;
	}

	cout << ans << endl;

	return 0;
}
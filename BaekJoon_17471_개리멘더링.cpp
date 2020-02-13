#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct point
{
	int x, y;
	int dis;
};

int map[50][50];
int copy_map[50][50];
int visited[50][50];
int val[10];
int visit[10];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int N, M;
int Count;
int ans = 0;
int res = 0;
int last = 987654321;
vector<point> v[10];

void init() {

	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			visited[i][k] = 0;
		}
	}

	for (int i = 0; i < 10; i++) {
		visit[i] = 0;
	}
}
int check() {

	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			if (map[i][k] == 0) return 1;
		}
	}
	return 0;
}

void dfs(int cnt, int m) {

	// M개의 조합을 찾음
	if (cnt == M) {

		// 모든  초기화
		res = 0;
		init();

		// copy_map
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				copy_map[i][k] = map[i][k];
			}
		}

		// val에 조합이 있음
		// M에 따른 확산 속도 측정
		queue<point> q;
		for (int i = 0; i < M; i++) {
			point p1;
			p1.x = v[val[i]].front().x;
			p1.y = v[val[i]].front().y;
			p1.dis = v[val[i]].front().dis;
			q.push(p1);
		}

		// bfs 시작  바이러스가 퍼짐
		while (!q.empty()) {

			int x = q.front().x;
			int y = q.front().y;
			int d = q.front().dis;
			visited[y][x] = 1;
			q.pop();

			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N || visited[ny][nx] == 1 || map[ny][nx] == 1)
					continue;

				visited[ny][nx] = 1;
				point p2;
				p2.x = nx;
				p2.y = ny;
				if (map[ny][nx] == 2) {
					p2.dis = d + 1;
				}
				else {
					map[ny][nx] = 1;
					p2.dis = d + 1;
					ans = d + 1;
					if (res < ans)
						res = ans;
				}
				q.push(p2);

			}
		}

		// 퍼지지 못한곳이 있다면 ans =-1;
		if (check() == 1) {
			if (last == 987654321) last = -1;
		}
		else {
			if (last == -1) last = res;
			else if (last > res)
				last = res;
		}

		// map 되돌리기
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				map[i][k] = copy_map[i][k];
			}
		}
	}
	for (int i = m; i < Count; i++) {
		if (visit[i] == 1) continue;
		visit[i] = 1;
		val[cnt] = i;
		dfs(cnt + 1, i + 1);
		visit[i] = 0;
	}

}

int main() {
	cin >> N >> M;

	// 맵 초기화 및 바이러스 위치 넣기
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			cin >> map[i][k];
			if (map[i][k] == 2) {
				point p;
				p.x = k;
				p.y = i;
				p.dis = 0;
				v[Count].push_back(p);
				Count++;
			}
		}
	}

	// 바이러스의 조합 찾기
	dfs(0, 0);

	cout << last << endl;

	return 0;
}
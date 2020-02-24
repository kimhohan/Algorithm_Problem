#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct point
{
	int x, y;
	int dis;
};

vector<int> map[50][50];
int visit[50][50];
int c_visit[50][50];
int N, K;
int ans;
int res;
int ress;
int area;

int dir[4];
int dx[4] = { 0,1, 0,-1};
int dy[4] = {1,0, -1,0 };

void re() {
	for (int i = 0; i < 4; i++)
		dir[i] = 0;

}

void d_check(int n) {
	int num = n;
	if (num == 0) {
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			num = num - 8;
			if (num > 0)
				dir[0]++;
			else if (num == 0) {
				dir[0]++;
				return;
			}
			else
				num = num + 8;
		}
		if (i == 1) {
			num = num - 4;
			if (num > 0)
				dir[1]++;
			else if (num == 0) {
				dir[1]++;
				return;
			}
			else
				num = num + 4;
		}
		if (i == 2) {
			num = num - 2;
			if (num > 0)
				dir[2]++;
			else if (num == 0) {
				dir[2]++;
				return;
			}
			else
				num = num + 2;
		}
		if (i == 3) {
			num = num - 1;
			if (num >= 0)
				dir[3]++;
			return;
		}
	}
}

void copy_visit(int f) {
	if (f == 1) {

		for (int i = 0; i < N; i++) {
			for (int k = 0; k < K; k++) {
				c_visit[i][k] = visit[i][k];
			}
		}
	}

	if (f == 2) {

		for (int i = 0; i < N; i++) {
			for (int k = 0; k < K; k++) {
				visit[i][k] = c_visit[i][k];
			}
		}
	}


	if (f == 3) {

		for (int i = 0; i < N; i++) {
			for (int k = 0; k < K; k++) {
				visit[i][k] =  0;
			}
		}
	}
}

void bfs(int y, int x, int f) {
	visit[y][x] = 1;

	int l_d = 0;

	queue<point> q;
	point p;
	p.x = x;
	p.y = y;
	p.dis = 1;
	res = 1;
	q.push(p);

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		int d = q.front().dis;

		q.pop();

		for (int i = 0; i < 4; i++) {
			if (map[cy][cx][i] == 1) continue;
			
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || ny < 0 || nx >= K || ny >= N || visit[ny][nx] == 1 ) {
				continue;
			}

			visit[ny][nx] = 1;
			point p1;
			p1.x = nx;
			p1.y = ny;
			p1.dis = d + 1;
			res++;
			q.push(p1);
		}
	}

	if (f == 1) {
		if (ans < res) {
			ans = res;
			ress = res;
		}
	}
	if (f == 2) {
		if (ress < res)
			ress = res;
	}
}

int main() {
	cin >> K >> N;

	for (int i = 0; i < N; i++) {
		for (int k = 0; k < K; k++) {
			int num;
			cin >> num;
			d_check(num);

			for (int t = 0; t < 4; t++) {
				if (dir[t] == 1)
					map[i][k].push_back(1);
				else
					map[i][k].push_back(0);
			}
			re();
		}
	}

	// bfs
	for (int i = 0; i < N ; i++) {
		for (int k = 0; k < K ; k++) {
			if (visit[i][k] == 0) {
				bfs(i, k, 1);
				area++;
			}
		}
	}

	copy_visit(3);

	// ¹®¶Õ±â
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < K; k++) {
				
			for (int t = 0; t < 4; t++) {
				if (map[i][k][t] == 1) {
					int nx = k + dx[t];
					int ny = i + dy[t];

					if (nx < 0 || ny < 0 || nx >= K || ny >= N) {
						continue;
					}

					map[i][k][t] = 0;
					map[ny][nx][(t + 2) % 4] = 0;
					bfs(i, k, 2);
					map[i][k][t] = 1;
					map[ny][nx][(t + 2) % 4] = 1;
					copy_visit(3);
				}
			}
		}
	}

	cout << area << endl;
	cout << ans << endl;
	cout << ress << endl;

	return 0;
}
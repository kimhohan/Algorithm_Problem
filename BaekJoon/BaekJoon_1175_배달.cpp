#include <iostream>
#include <queue>

using namespace std;

struct Point
{
	int y, x, dir;
	int dis;
	int c, k;
	Point(int y, int x, int dir, int dis, int c, int k ) {
		this->y = y;
		this->x = x;
		this->dir = dir;
		this->dis = dis;
		this->c = c;
		this->k = k;
	}

};

int Y, X;
int visit[50][50][5][2][2];
int map[50][50];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,-1,0,1 };
int ans = 987654321;
int count1;

void bfs(int y, int x, int d, int dis, int c, int k) {
	queue<Point> q;
	q.push(Point(y, x, d, dis, c,k));

	visit[y][x][d][c][k] = 1;

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		int dir = q.front().dir;
		int dis = q.front().dis;
		int cc = q.front().c;
		int kk= q.front().k;

		q.pop();

		if (cc == 1 && kk == 1) {
			if (ans > dis)
				ans = dis;
			continue;
		}

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			// 같은 
			if (i == dir)
				continue;

			if (nx < 0 || ny < 0 || nx >= X || ny >= Y || visit[ny][nx][i][cc][kk] == 1 || map[ny][nx] == -1)
				continue;


			if (map[ny][nx] == 2) {
				q.push(Point(ny, nx, i, dis + 1, 1, kk));
			}
			if (map[ny][nx] == 3) {
				q.push(Point(ny, nx, i, dis + 1, cc, 1));
			}
			else {
				visit[ny][nx][i][cc][kk] = 1;
				q.push(Point(ny, nx, i, dis + 1, cc, kk));
			}
			
		}
	}
}

int main() {
	int cx, cy;

	cin >> Y >> X;

	// 입력
	int cnt = 0;
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			char ch;
			cin >> ch;

			if (ch == '.') {
				map[i][k] = 0;
			}
			if (ch == 'S') {
				map[i][k] = 1;
				cy = i;
				cx = k;
			}
			if (ch == 'C') {
				if(cnt == 0)
					map[i][k] = 2;
				else
					map[i][k] = 3;
				cnt++;
			}
			if (ch == '#') {
				map[i][k] = -1;
			}
		}
	}

	// 탐색시작
	bfs(cy, cx, 4 , 0, 0 , 0);

	if (ans == 987654321) ans = -1;

	cout << ans << endl;

	return 0;
}
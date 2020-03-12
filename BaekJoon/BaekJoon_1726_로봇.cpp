#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Point
{
	int y, x, dis, dir;
	Point(int y, int x, int dis, int dir) {
		this->dir = dir;
		this->dis = dis;
		this->x = x;
		this->y = y;
	}
};

int Y, X;
int map[101][101];
int visit[101][101][5];
int s_x, s_y, s_dir;
int e_x, e_y, e_dir;
int ans = 987654321;
int res;

int dx[5] = { 0,1,-1,0,0 };
int dy[5] = { 0,0,0,1,-1 };

void bfs() {
	queue<Point> q;
	q.push(Point(s_y, s_x, 0, s_dir));
	visit[s_y][s_x][s_dir] = 1;

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		int cd = q.front().dis;
		int cdir = q.front().dir;

		q.pop();

		// 종료
		if (cy == e_y && cx == e_x && cdir == e_dir) {
			ans = cd;
			return;
		}


		// 자기에 맞는 방향대로 움직이기
		for (int k = 1; k <= 3; k++) {
			int nx = cx + dx[cdir] * k;
			int ny = cy + dy[cdir] * k;


			if (visit[ny][nx][cdir] == 1)
				continue;

			if (map[ny][nx] == 1 || nx <= 0 || ny <= 0 || nx > X || ny > Y)
				break;

			visit[ny][nx][cdir] = 1;

			q.push(Point(ny, nx, cd + 1, cdir));
		}

		// 방향 전환을 Q에 넣어주기
		for (int i = 1; i <= 4; i++) {

			// 방향에 따른 가중치
			if (cdir != i && visit[cy][cx][i] == 0) {
				visit[cy][cx][i] = 1;
				if ((cdir == 1 && i == 2) || (cdir == 2 && i == 1) || (cdir == 3 && i == 4) || (cdir == 4 && i == 3))
					q.push(Point(cy, cx, cd + 2, i));
				else
					q.push(Point(cy, cx, cd + 1, i));
			}
		}
	}
}

int main() {
	cin >> Y >> X;

	for (int i = 1; i <= Y; i++) {
		for (int k = 1; k <= X; k++) {
			cin >> map[i][k];
		}
	}

	cin >> s_y >> s_x >> s_dir;
	cin >> e_y >> e_x >> e_dir;

	// 탐색
	bfs();

	cout << ans << endl;

	return 0;
}
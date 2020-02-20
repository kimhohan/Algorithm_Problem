#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>

using namespace std;

struct point
{
	int x, y;
	int dis;
	int c_count;
};

int Y, X;
int map[1000][1000];
int visit[1000][1000][2];
int c_visit[1000][1000][2];

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
int ans = 987654231;
int nc;

void bfs(int y, int x) {
	point p;
	p.x = x;
	p.y = y;
	p.dis = 1;
	p.c_count = 0;
	visit[y][x][0] = 1;
	visit[y][x][1] = 1;
	queue<point> q;
	q.push(p);

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		int d = q.front().dis;
		int c = q.front().c_count;
		q.pop();

		if (cx == X - 1 && cy == Y - 1) {
			if(ans > d)
				ans = d;
		}

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || ny < 0 || nx >= X || ny >= Y || visit[ny][nx][c] == 1 )
				continue;
			
			if (map[ny][nx] == 1) {
				if (c == 0) {
					nc = c + 1;
					visit[ny][nx][nc] = 1;
					point p11;
					p11.x = nx;
					p11.y = ny;
					p11.dis = d + 1;
					p11.c_count = nc;
					q.push(p11);
				}
				else {
					continue;
				}
			}
			else {
				visit[ny][nx][c] = 1;
				point p1;
				p1.x = nx;
				p1.y = ny;
				p1.dis = d + 1;
				p1.c_count = c;
				q.push(p1);
			}
		}
	}
}

// 1 : º® , 0 : ¶¥
int main() {
	cin >> Y >> X;

	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			scanf("%1d", &map[i][k]);
		}
	}

	bfs(0, 0);

	if (ans == 987654231) ans  = -1;
	cout << ans << endl;
}
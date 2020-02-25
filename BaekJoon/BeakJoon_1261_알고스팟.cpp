#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>

using namespace std;

struct Point
{
	int x, y;
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

int Y, X;
int map[100][100];
int d[100][100];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void bfs(int y, int x, int w) {
	queue<Point> q;
	q.push(Point(x, y));
	d[y][x] = 0;

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || ny < 0 || nx >= X || ny >= Y)
				continue;

			if (map[ny][nx] == 0 && d[cy][cx] < d[ny][nx]) {
				d[ny][nx] = d[cy][cx];
				q.push(Point(nx, ny));
			}
			else if (map[ny][nx] == 1 && d[cy][cx] + 1 < d[ny][nx]) {
				d[ny][nx] = d[cy][cx] + 1;
				q.push(Point(nx, ny));
			}

		}

	}

}

int main() {
	cin >> X >> Y;
	// ют╥б
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			scanf("%1d", &map[i][k]);
			d[i][k] = 987654321;
		}
	}

	bfs(0,0, 0);

	cout << d[Y-1][X-1] << endl;

	return 0;
}
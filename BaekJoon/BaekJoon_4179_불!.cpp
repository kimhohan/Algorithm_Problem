#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Point
{
	int y, x;
	int dis;
	int flag;
	Point(int y, int x, int dis, int flag) {
		this->y = y;
		this->x = x;
		this->dis = dis;
		this->flag = flag;
	}
};

vector<Point> fire;
int Y, X;
int s_x, s_y;
int ans;
int map[1000][1000];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void bfs(int y, int x, int dis, int flag) {
	queue<Point> q;

	for (int i = 0; i < fire.size(); i++) {
		q.push(Point(fire[i].y, fire[i].x, fire[i].dis, fire[i].flag));
	}

	q.push(Point(y, x, dis, flag));

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		int d = q.front().dis;
		int f = q.front().flag;

		q.pop();

		// 탈출 성공
		if (f == 2) {
			if (cx == 0 || cy == 0 || cx == X - 1 || cy == Y - 1) {
				ans = d + 1;
				return;
			}
		}

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			// 지훈이
			if (f == 2) {

				if (map[ny][nx] == 1 || map[ny][nx] == 2 || map[ny][nx] == 3)
					continue;

				map[ny][nx] = f;
				q.push(Point(ny, nx, d + 1, f));
			}
			// 불
			if (f == 3) {
				if (nx < 0 || ny < 0 || nx >= X || ny >= Y || map[ny][nx] == 1 || map[ny][nx] == 3)
					continue;

				map[ny][nx] = f;
				q.push(Point(ny, nx, d + 1, f));
			}
		}
	}
}

int main() {
	cin >> Y >> X;

	// 입력
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			char ch;
			cin >> ch;
			if (ch == '#') {
				map[i][k] = 1;
			}
			if (ch == '.') {
				map[i][k] = 0;
			}
			if (ch == 'J') {
				map[i][k] = 2;
				s_x = k;
				s_y = i;
			}
			if (ch == 'F') {
				map[i][k] = 3;
				fire.push_back(Point(i, k, 0, 3));
			}
		}
	}

	// 탈출 시작
	bfs(s_y, s_x, 0, 2);

	// 출력
	if (ans == 0) cout << "IMPOSSIBLE" << endl;
	else cout << ans << endl;

	return 0;
}
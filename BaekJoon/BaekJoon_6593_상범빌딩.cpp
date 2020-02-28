#include <iostream>
#include <queue>

struct Point
{
	int x, y, z;
	int dis;

	Point(int z, int y, int x, int dis) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->dis = dis;
	}
};

using namespace std;

int Z, Y, X;
int ans;
int s_x, s_y, s_z;
int map[30][30][30];
int dx[6] = {0,0,0,0,1,-1};
int dy[6] = {0,0,1,-1,0,0};
int dz[6] = {1,-1,0,0,0,0};

void bfs(int z, int y, int x, int dis) {
	queue<Point>q;
	q.push(Point(z, y, x, dis));
	map[z][y][x] = 1;

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		int cz = q.front().z;
		int d = q.front().dis;

		q.pop();

		for (int i = 0; i < 6; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			int nz = cz + dz[i];

			if (nz < 0 || ny < 0 || nx < 0 || nz >= Z || ny >= Y || nx >= X || map[nz][ny][nx] == 1)
				continue;

			if (map[nz][ny][nx] == 3) {
				ans = d + 1;
				return;
			}

			map[nz][ny][nx] = 1;
			q.push(Point(nz, ny, nx,d+ 1));
		}
	}
	
}

int main() {

	// 입력
	while (1) {
		cin >> Z >> Y >> X;

		if (Z == 0 && Y == 0 && X == 0)
			break;

		for (int i = 0; i < Z; i++) {
			for (int k = 0; k < Y; k++) {
				for (int r = 0; r < X; r++) {
					char ch;
					cin >> ch;
					if (ch == '.') {
						map[i][k][r] = 0;
					}
					if (ch == 'S') {
						map[i][k][r] = 2;
						s_x = r;
						s_y = k;
						s_z = i;
					}
					if (ch == 'E') {
						map[i][k][r] = 3;
					}
					if (ch == '#') {
						map[i][k][r] = 1;
					}
				}
			}
		}

		// 탈출 해보기
		bfs(s_z, s_y, s_x, 0);

		if (ans == 0) {
			cout << "Trapped!" << endl;
		}
		else {
			cout << "Escaped in " << ans << " minute(s)." << endl;
		}

		ans = 0;
	}
	return 0;
}

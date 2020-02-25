#include <iostream>
#include <queue>

using namespace std;

struct Point
{
	int x, y;
	Point(int y, int x) {
		this->y = y;
		this->x = x;
	}
};

int map[12][6];
int visit[12][6];
int ans = 0;
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void bfs(int y, int x, int color) {
	queue<Point> q;
	q.push(Point(y, x));

	map[y][x] = 0;
	int count = 0;

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		count++;

		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || ny < 0 || nx >= 6 || ny >= 12 || map[ny][nx] == 0 || map[ny][nx] == -1 || map[ny][nx] != color)
				continue;

			map[ny][nx] = 0;
			q.push(Point(ny, nx));
		}
	}
	//  4개이하면 원상 복구
	if(count < 4) {
		for (int i = 0; i < 12; i++) {
			for (int k = 0; k < 6; k++) {
				if (map[i][k] == 0 && visit[i][k] == 0)
					map[i][k] = color;
			}
		}
	}
	// 4개이상이라면 check
	else {
		for (int i = 0; i < 12; i++) {
			for (int k = 0; k < 6; k++) {
				if (map[i][k] == 0)
					visit[i][k] = 1;
			}
		}
	}
}

int main() {
	// 맵 입력
	for (int i = 0; i < 12; i++) {
		for (int k = 0; k < 6; k++) {
			char ch;
			cin >> ch;
			if (ch == '.') {
				map[i][k] = -1;
			}
			if (ch == 'R') {
				map[i][k] = 1;
			}
			if (ch == 'G') {
				map[i][k] = 2;
			}
			if (ch == 'B') {
				map[i][k] = 3;
			}
			if (ch == 'P') {
				map[i][k] = 4;
			}
			if (ch == 'Y') {
				map[i][k] = 5;
			}
		}
	}

	// 제거하면서 칸 내리기
	while (1) {

		// visit 초기화
		for (int i = 0; i < 12; i++) {
			for (int k = 0; k < 6; k++) {
				visit[i][k] = 0;
			}
		}

		// 본격 지울수있는 블럭 찾기
		for (int i = 11; i >= 0; i--) {
			for (int k = 0; k < 6; k++) {
				if (map[i][k] != -1 && map[i][k] != 0) {
					bfs(i, k, map[i][k]);
				}
			}
		}

		//0짜리 내리기
		int flag = 0;
		for (int i = 0; i < 6; i++) {
			for (int k = 0; k < 12; k++) {
				if (map[k][i] == 0) {
					flag = 1;
					// 다내리기
					for (int r = k; r >= 1; r--) {
						map[r][i] = map[r - 1][i];
					}
					map[0][i] = -1;
				}
			}
		}
		// 아무변화가 없다면 끝!
		if (flag == 0) {
			break;
		}
		// 아니면 계속
		else {
			ans++;
		}
		
	}

	cout << ans << endl;

	return 0;
}
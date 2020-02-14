#include <iostream>

using namespace std;

struct Point
{
	int x, y;
};

int map[10000][500];
int visit[10000][500];

int dx[5] = {1,1,1};
int dy[5] = {-1,0,1};
int Y, X;
int ans = 0;

bool dfs(int y, int x) {
	visit[y][x] = 1;
	// 마지막 열까지 가보자
	if (x == X - 1) {
		// 표시하기
		ans++;
		return true;
	}

	for (int i = 0; i < 3; i++) {
		cout << i << endl;
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || ny < 0 || nx >= X || ny >= Y || map[ny][nx] == 1 || visit[ny][nx] == 1)
			continue;

		if (dfs(ny, nx)) return true;
	}
	return false;
}


int main() {
	cin >> Y >> X;

	// 입력
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			char ch;
			cin >> ch;
			if (ch == '.') map[i][k] = 0;
			else if (ch == 'x') map[i][k] = 1;
		}
	}
	// 1열 1만들기
	for (int i = 0; i < Y; i++) {
		map[i][0] = 1;
	}

	// 1열의 첫번째 부터 bfs
	for (int i = 0; i < Y; i++) {
		dfs(i , 0);
	}

	cout << ans << endl;
}
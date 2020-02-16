#include <iostream>
#include <queue>

using namespace std;

struct Point
{
	int t_x, t_y;
	int h_x, h_y;
};

int map[16][16];
int N;
int ans;
int dx[3] = {1,0,1};
int dy[3] = {1,1,0};

void bfs(int y1, int x1, int y, int x) {
	
	queue<Point> q;
	Point p;
	p.t_y = y1;
	p.t_x = x1;
	p.h_y = y;
	p.h_x = x;
	q.push(p);

	while (!q.empty())
	{
		Point p1 = q.front();
		int tail_x = p1.t_x;
		int tail_y = p1.t_y;
		int head_x = p1.h_x;
		int head_y = p1.h_y;
		q.pop();

		if (head_x == N - 1 && head_y == N - 1) {
			ans++;
			continue;
		}

		int flag = 0;
		// 가로인 경우
		if (tail_y == head_y) {
			flag = 1;
		}
		// 세로인 경우
		else if (tail_x == head_x) {
			flag = 2;
		}
		// 대각선이 경우 판단
		else {
			flag = 3;
		}

		for (int i = 0; i < 3; i++) {
			if (i == flag) continue;

			int ny_head_y = head_y + dy[i];
			int nx_head_x = head_x + dx[i];

			if (ny_head_y < 0 || nx_head_x < 0 || ny_head_y >= N || nx_head_x >= N || map[ny_head_y][nx_head_x] == 1)
				continue;

			// 대각선의 경우 예외		
			if (i == 0) {
				if (map[ny_head_y][nx_head_x] == 1 || map[head_y + 1][head_x] == 1 || map[head_y][head_x + 1] == 1)
					continue;
			}

			Point p2;
			p2.t_x = head_x;
			p2.t_y = head_y;
			p2.h_x = nx_head_x;
			p2.h_y = ny_head_y;
			q.push(p2);
		}
	}
}

int main() {
	cin >> N;
	// 입력
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			cin >> map[i][k];
		}
	}

	bfs(0,0,0,1);

	cout << ans << endl;

	return 0;
}
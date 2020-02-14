#include <iostream>
#include <queue>

using namespace std;

int map[21][21] = { 0, };
int div_[21][21] = { 0, };
int visit[21][21] = { 0, };

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int po_x[5] = { 0, };
int po_y[5] = { 0, };

int N;
int res[6] = { 0, };
int ans = 987654321;

struct point
{
	int x, y;
};

void init_div() {
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			div_[i][k] = 0;
			visit[i][k] = 0;
		}
	}

	for (int i = 0; i < 6; i++) {
		res[i] = 0;
	}
}

void bfs_s(int y, int x, int c) {
	queue<point> q;
	point p;
	p.x = x;
	p.y = y;

	div_[y][x] = c;
	q.push(p);

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N || div_[ny][nx] == 5 || div_[ny][nx] > 0)
				continue;

			div_[ny][nx] = c;
			point p1;
			p1.x = nx;
			p1.y = ny;

			q.push(p1);
		}
	}
}

void bfs(int y, int x, int c) {
	queue<point> q;
	point p;
	p.x = x;
	p.y = y;

	visit[y][x] = 1;
	q.push(p);

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		q.pop();
		res[c] += map[cy][cx];

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N || visit[ny][nx] == 1 || div_[ny][nx] != c)
				continue;

			visit[ny][nx] = 1;
			point p1;
			p1.x = nx;
			p1.y = ny;

			q.push(p1);
		}
	}
}

void divide(int x, int y, int d1, int d2) {

	// 일단 5번 구역 부터
	for (int i = 0; i <= d1; i++) {
		div_[y - i][x + i] = 5;
		if (i == 0) {
			po_x[3] = x + i;
			po_y[3] = y - i;
		}
		if (i == d1) {
			po_x[1] = x + i;
			po_y[1] = y - i;
		}
		div_[y + d2 - i][x + d2 + i] = 5;
		if (i == 0) {
			po_x[4] = x + d2 + i;
			po_y[4] = y + d2 - i;
		}
		if (i == d1) {
			po_x[2] = x + d2 + i;
			po_y[2] = y + d2 - i;
		}
	}
	for (int i = 0; i <= d2; i++) {

		div_[y + i][x + i] = 5;
		div_[y - d1 + i][x + d1 + i] = 5;
	}

	// 5 채우기
	int flag = 0;
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			if (div_[i][k] == 5) {
				if(div_[i + 1][k] == 0 && div_[i + 1][k + 1] == 5 && div_[i + 1][k - 1] == 5)
					bfs_s(i + 1, k,5);
			}
		}
	}

	// 나머지 채우기
	//1
	for (int i = 0; i < po_y[3]; i++) {
		for (int k = 0; k <= po_x[1]; k++) {
			if (div_[i][k] == 0)
				div_[i][k] = 1;
		}
	}
	//2
	for (int i = 0; i <= po_y[2]; i++) {
		for (int k = po_x[1] + 1; k < N; k++) {
			if (div_[i][k] == 0)
				div_[i][k] = 2;
		}
	}
	//3
	for (int i = po_y[1] + 1; i < N; i++) {
		for (int k = 0; k < po_x[4]; k++) {
			if (div_[i][k] == 0)
				div_[i][k] = 3;
		}
	}
	//4
	for (int i = po_y[2] + 1; i < N; i++) {
		for (int k = po_x[4]; k < N; k++) {
			if (div_[i][k] == 0)
				div_[i][k] = 4;
		}
	}

	// 계산
	int f = 0;
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			if (visit[i][k] != 1) {
				int num = div_[i][k];
				bfs(i, k, num);
			}
		}
	}

	// 최대와 최소의 차이 구하기
	int min = 987654321;
	int max = 0;
	for (int i = 1; i <= 5; i++) {
		if (min > res[i]) min = res[i];
		if (max < res[i]) max = res[i];
	}

	if (ans > (max - min))
		ans = (max - min);
}

int main() {
	cin >> N;

	// 입력 받기
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			cin >> map[i][k];
		}
	}

	// x, y , d1, d2 조합 찾기
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			int x = k;
			int y = i;

			// d1, d2 값정하기
			for (int r = 1; r < N; r++) {
				for (int t = 1; t < N; t++) {
					int d1 = r;
					int d2 = t;
					// 예외 처리
					if ((x + d1 + d2) >= N) continue;
					if ((y - d1) < 1) continue;
					if ((y + d2) >= N) continue;
					
					// 구역 초기화
					init_div();

					// x, y ,d1,d2 결정 완료
					// 구역 나누기
					divide(x, y, d1, d2);
				}
			}
		}
	}

	cout << ans << endl;

	return 0;
}
#include <iostream>
#include <queue>
#include <algorithm>

struct Point
{
	int dir[4];
	int flag;

	Point() {};
	Point(int a, int b, int c, int d, int f) {
		this->dir[0] = a;
		this->dir[1] = b;
		this->dir[2] = c;
		this->dir[3] = d;
		this->flag = f;
	}
};

struct q_point
{
	int y, x;
	int dis;

	q_point(int y, int x, int dis) {
		this->x = x;
		this->y = y;
		this->dis = dis;
	}
};

using namespace std;

int ans_x, ans_y, ans_block;
int s_x, s_y, e_x, e_y;
char ans;
int Y, X;
Point map[25][25];
int check_map[25][25];
int visit[25][25];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

void init() {
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			visit[i][k] = 0;
		}
	}
}

int check() {
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			if (visit[i][k] != check_map[i][k]) return 0;
		}
	}
	return 1;
}


int find_hole(int y, int x) {
	queue<q_point> q;
	q.push(q_point(y, x, 0));
	visit[y][x] = 1;

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;

		q.pop();

		for (int i = 0; i < 4; i++) {
			if (map[cy][cx].dir[i] == 0) continue;

			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || ny < 0 || nx >= X || ny >= Y) continue;
			// 헛점이 나오면 아웃
			if (map[ny][nx].dir[0] == 0 && map[ny][nx].dir[1] == 0 && map[ny][nx].dir[2] == 0 && map[ny][nx].dir[3] == 0) {
				if (map[cy][cx].flag != 0) continue;
				ans_x = nx;
				ans_y = ny;
				return 1;
			}

			if (map[ny][nx].dir[(i + 2) % 4] == 1) {
				if (visit[ny][nx] == 1) continue;
				visit[ny][nx] = 1;
				q.push(q_point(ny, nx , 0));
			}
		}
	}
	return 0;
}

int bfs(int y, int x) {
	queue<q_point> q;
	q.push(q_point(y, x , 0));
	visit[y][x] = 1;
	int cnt = 1;

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		int cd = q.front().dis;

		q.pop();

		for (int i = 0; i < 4; i++) {
			if (map[cy][cx].dir[i] == 0) continue;

			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || ny < 0 || nx >= X || ny >= Y) continue;
			// 헛점이 나오면 아웃
			if (map[ny][nx].dir[0] == 0 && map[ny][nx].dir[1] == 0 && map[ny][nx].dir[2] == 0 && map[ny][nx].dir[3] == 0) {
				if (map[cy][cx].flag != 0) continue;
				else return 0;
			}

			if (map[ny][nx].dir[(i + 2) % 4] == 1) {
				if (map[cy][cx].flag == 1 && map[ny][nx].flag == 2) continue;
				if (visit[ny][nx] == 1) continue;
				if (cd == 0 && cnt > 1) return 0;
				visit[ny][nx] = 1;
				q.push(q_point(ny, nx, cd + 1));
				cnt++;
			}
			// 이상한 곳으로 연결되면 아웃
			else if(map[cy][cx].flag == 0){
				return 0;
			}
		}
	}

	if (check() == 1) return 1;
	else return 0;

}

void select(int y, int x, int n) {
	if (n == 1) {
		map[y][x] = Point(1, 1, 0, 0, 0);
	}
	// ㄴ
	if (n == 2) {
		map[y][x] = Point(1, 0, 0, 1, 0);
	}
	// 』
	if (n == 3) {
		map[y][x] = Point(0, 0, 1, 1, 0);
	}
	// ㄱ
	if (n == 4) {
		map[y][x] = Point(0, 1, 1, 0, 0);
	}
	// |
	if (n == 5) {
		map[y][x] = Point(0, 1, 0, 1, 0);
	}
	// -
	if (n == 6) {
		map[y][x] = Point(1, 0, 1, 0, 0);
	}
	// +
	if (n == 7) {
		map[y][x] = Point(1, 1, 1, 1, 0);
	}

}

int main() {
	cin >> Y >> X;
	// 입력
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			char ch;
			cin >> ch;
			if (ch == '.') {
				map[i][k] = Point(0, 0, 0, 0, 0);
			}
			if (ch == '|') {
				check_map[i][k] = 1;
				map[i][k] = Point(0, 1, 0, 1, 0);
			}
			if (ch == '-') {
				check_map[i][k] = 1;
				map[i][k] = Point(1, 0, 1, 0, 0);
			}
			if (ch == '+') {
				check_map[i][k] = 1;
				map[i][k] = Point(1, 1, 1, 1, 0);
			}
			// 「
			if (ch == '1') {
				check_map[i][k] = 1;
				map[i][k] = Point(1, 1, 0, 0, 0);
			}
			// ㄴ
			if (ch == '2') {
				check_map[i][k] = 1;
				map[i][k] = Point(1, 0, 0, 1, 0);
			}
			// 』
			if (ch == '3') {
				check_map[i][k] = 1;
				map[i][k] = Point(0, 0, 1, 1, 0);
			}
			// ㄱ
			if (ch == '4') {
				check_map[i][k] = 1;
				map[i][k] = Point(0, 1, 1, 0, 0);
			}
			// 끝 = 2
			if (ch == 'Z') {
				check_map[i][k] = 1;
				map[i][k] = Point(1, 1, 1, 1, 2);
				e_x = k;
				e_y = i;
			}
			// 시작 = 1
			if (ch == 'M') {
				check_map[i][k] = 1;
				map[i][k] = Point(1, 1, 1, 1, 1);
				s_x = k;
				s_y = i;
			}
		}
	}

	//// 헛점 1군데 찾기 ,(좌표 저장 해두기)
	// 한칸차이의 경우 
	if (find_hole(s_y, s_x) == 0) {
		int t_x = e_x;
		int t_y = e_y;
		e_x = s_x;
		e_y = s_y;
		s_x = t_x;
		s_y = t_y;
		if (find_hole(s_y, s_x) == 0) {
			if ((abs(s_x - e_x) + abs(s_y - e_y)) == 2) {
				if (s_x == e_x) {
					ans_x = s_x;
					ans_y = (s_y + e_y) / 2;
				}
				else if (s_y == e_y) {
					ans_y = s_y;
					ans_x = (s_x + e_x) / 2;
				}
				else {
					ans_y = s_y;
					ans_x = e_x;
				}
			}
		}
	}

	// visit 초기화
	init();

	// 찾은 헛점에 모든 경우(7가지) 다넣어보기
	check_map[ans_y][ans_x] = 1;
	for (int i = 1; i <= 7; i++) {
		select(ans_y, ans_x, i);
		if (bfs(s_y, s_x) == 0) {
			init();
			continue;
		}
		else {
			ans_block = i;
			break;
		}
	}

	// 출력
	if (ans_block == 1) {
		ans = '1';
	}
	if (ans_block == 2) {
		ans = '2';
	}
	if (ans_block == 3) {
		ans = '3';
	}
	if (ans_block == 4) {
		ans = '4';
	}
	if (ans_block == 5) {
		ans = '|';
	}
	if (ans_block == 6) {
		ans = '-';
	}
	if (ans_block == 7) {
		ans = '+';
	}
	cout << ans_y + 1 << " " << ans_x  + 1<< " " << ans << endl;

	return 0;
}
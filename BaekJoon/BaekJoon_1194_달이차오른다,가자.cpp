#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Point
{
	int y, x, dis;
	vector<char> key_item;
	int a, b, c, d, e, f;

	Point(int y, int x, int dis, int a, int b, int c, int d, int e, int f, vector<char> key) {
		this->y = y;
		this->x = x;
		this->dis = dis;

		this->key_item = key;

		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->e = e;
		this->f = f;
	}
};

int N, M;
vector<Point> v_end;
vector<Point> v_up;
vector<Point> v_down;

vector<Point> key_item;

char map[50][50];
int visit[50][50][2][2][2][2][2][2];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
int cx, cy;
int ans = 987654321;

bool cmp(Point a, Point b) {
	if (a.dis < b.dis) return true;
	return false;
}


void bfs(int y, int x, int dis, int a, int b, int c, int d, int e, int f) {
	queue<Point>q;
	vector<char> ch1;

	q.push(Point(y, x, dis, a, b, c, d, e, f, ch1));
	visit[y][x][a][b][c][d][e][f] = 1;

	while (!q.empty()) {
		int xxx = q.front().x;
		int yyy = q.front().y;
		int diss = q.front().dis;
		int a1 = q.front().a;
		int b1 = q.front().b;
		int c1 = q.front().c;
		int d1 = q.front().d;
		int e1 = q.front().e;
		int f1 = q.front().f;

		vector<char> ch = q.front().key_item;

		// 끝
		if (map[yyy][xxx] == '1') {
			ans = diss;
			return;
		}
		else {
			q.pop();
		}

		// 방향 탐색
		for (int i = 0; i < 4; i++) {
			int xx = xxx + dx[i];
			int yy = yyy + dy[i];

			if (xx < 0 || yy < 0 || xx >= M || yy >= N || map[yy][xx] == '#' || visit[yy][xx][a1][b1][c1][d1][e1][f1] == 1)
				continue;

			// 찾은 아이템은 저장 
			if (map[yy][xx] == 'a' || map[yy][xx] == 'b' || map[yy][xx] == 'c' || map[yy][xx] == 'd' || map[yy][xx] == 'e' || map[yy][xx] == 'f') {
				if (map[yy][xx] == 'a') {
					vector<char> ch2;
					for (int i = 0; i < ch.size(); i++)
						ch2.push_back(ch[i]);
					ch2.push_back(map[yy][xx]);
					visit[yy][xx][1][b1][c1][d1][e1][f1] = 1;
					q.push(Point(yy, xx, diss + 1, 1, b1, c1, d1, e1, f1, ch2));
				}
				if (map[yy][xx] == 'b') {
					vector<char> ch2;
					for (int i = 0; i < ch.size(); i++)
						ch2.push_back(ch[i]);
					ch2.push_back(map[yy][xx]);
					visit[yy][xx][a1][1][c1][d1][e1][f1] = 1;
					q.push(Point(yy, xx, diss + 1, a1, 1, c1, d1, e1, f1, ch2));
				}
				if (map[yy][xx] == 'c') {
					vector<char> ch2;
					for (int i = 0; i < ch.size(); i++)
						ch2.push_back(ch[i]);
					ch2.push_back(map[yy][xx]);
					visit[yy][xx][a1][b1][1][d1][e1][f1] = 1;
					q.push(Point(yy, xx, diss + 1, a1, b1, 1, d1, e1, f1, ch2));
				}
				if (map[yy][xx] == 'd') {
					vector<char> ch2;
					for (int i = 0; i < ch.size(); i++)
						ch2.push_back(ch[i]);
					ch2.push_back(map[yy][xx]);
					visit[yy][xx][a1][b1][c1][1][e1][f1] = 1;
					q.push(Point(yy, xx, diss + 1, a1, b1, c1, 1, e1, f1, ch2));
				}
				if (map[yy][xx] == 'e') {
					vector<char> ch2;
					for (int i = 0; i < ch.size(); i++)
						ch2.push_back(ch[i]);
					ch2.push_back(map[yy][xx]);
					visit[yy][xx][a1][b1][c1][d1][1][f1] = 1;
					q.push(Point(yy, xx, diss + 1, a1, b1, c1, d1, 1, f1, ch2));
				}
				if (map[yy][xx] == 'f') {
					vector<char> ch2;
					for (int i = 0; i < ch.size(); i++)
						ch2.push_back(ch[i]);
					ch2.push_back(map[yy][xx]);
					visit[yy][xx][a1][b1][c1][d1][e1][1] = 1;
					q.push(Point(yy, xx, diss + 1, a1, b1, c1, d1, e1, 1, ch2));
				}
			}

			else if (map[yy][xx] == 'A' || map[yy][xx] == 'B' || map[yy][xx] == 'C' || map[yy][xx] == 'D' || map[yy][xx] == 'E' || map[yy][xx] == 'F') {
				// 열쇠가 있으면 통과
				if (ch.size() != 0) {
					for (int i = 0; i < ch.size(); i++) {
						if ((ch[i] - '0') - (map[yy][xx] - '0') == 32) {
							visit[yy][xx][a1][b1][c1][d1][e1][f1] = 1;
							q.push(Point(yy, xx, diss + 1, a1, b1, c1, d1, e1, f1, ch));
							continue;
						}
					}
				}
			}
			else {
				visit[yy][xx][a1][b1][c1][d1][e1][f1] = 1;
				q.push(Point(yy, xx, diss + 1, a1, b1, c1, d1, e1, f1, ch));
			}
		}
	}
}

int main() {
	cin >> N >> M;

	// 입력
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < M; k++) {
			cin >> map[i][k];
			if (map[i][k] == '0') {
				cy = i;
				cx = k;
			}
		}
	}

	// 찾을때 까지 돌거라
	bfs(cy, cx, 0, 0, 0, 0, 0, 0, 0.0);

	if (ans == 987654321) ans = -1;
	cout << ans << endl;
}
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct point
{
	int y, x;
	point(int y, int x) {
		this->y = y;
		this->x = x;
	}
};

struct edge
{
	int s, e, w;
	edge(int s, int e, int w) {
		this->s = s;
		this->e = e;
		this->w = w;
	}
};

int V;
int p[7];
int check[7];
int Y, X;
int map[10][10];
int visit[10][10];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
vector<edge> ed;

// union_find
void makeSet(int x) {
	p[x] = x;
}

int find_Set(int x) {
	if (x == p[x])
		return x;

	int nx = find_Set(p[x]);
	p[x] = nx;
	return nx;
}

void unionSet(int x, int y) {
	x = find_Set(x);
	y = find_Set(y);

	if (x == y)
		return;

	p[y] = x;
}

// union_find end

bool emp(const edge &a, const edge &b) {
	return a.w < b.w;
}

void find_edge(int y, int x, int v) {

	for (int i = 0; i < 4; i++) {
		int nx = x ;
		int ny=  y ;
		int cnt = 0;
		while (1) {
			nx += dx[i];
			ny += dy[i];

			if (nx < 0 || ny < 0 || nx >= X || ny >= Y || map[ny][nx] == v)
				break;

			if (map[ny][nx] == 0) {
				cnt++;
				continue;
			}

			if (cnt == 1)
				break;

			ed.push_back(edge(v, map[ny][nx], cnt));
			break;
		}
	}
}

void bfs(int y, int x, int cnt) {
	queue<point> q;
	visit[y][x] = 1;
	q.push(point(y, x));
	map[y][x] = cnt;

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || ny < 0 || nx >= X || ny >= Y || visit[ny][nx] == 1 || map[ny][nx] == 0)
				continue;

			map[ny][nx] = cnt;
			visit[ny][nx] = 1;
			q.push(point(ny, nx));
		}
	}

}

int main() {
	cin >> Y >> X;

	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			cin >> map[i][k];
		}
	}

	// 번호 부여
	int cnt = 1;
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			if (map[i][k] != 0 && visit[i][k] == 0) {
				bfs(i, k, cnt);
				cnt++;
			}
		}
	}
	V = cnt-1;

	// 가중치 저장
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			if (map[i][k] != 0 ) {
				find_edge(i, k, map[i][k]);
			}
		}
	}

	// 정렬
	sort(ed.begin(), ed.end(), emp);

	// 크루스칼
	for (int i = 1; i <= V; i++)
		makeSet(i);

	int c = 0;
	int ans = 0;
	for (int i = 0; i < ed.size(); i++) {
		int a = find_Set(ed[i].s);
		int b = find_Set(ed[i].e);

		if (a == b)
			continue;
		
		unionSet(a, b);
		c++;
		ans += ed[i].w;
		
		if (c == V - 1)
			break;
	}

	// 출력
	int flag = 0;
	int num = find_Set(p[1]);
	for (int i = 1; i <= V; i++) {
		int f = find_Set(p[i]);
		if (num != f) {
			flag = 1;
		}
	}
	if (flag == 1) ans = -1;
	cout << ans << endl;
	return 0;
}
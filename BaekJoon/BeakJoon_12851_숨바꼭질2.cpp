#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Point
{
	int data;
	int dis;
};

int map[100001];
int visit[100001];
int N, K;
// N�� K�� ���� ������ �F�����־�Ѵ�.
int ans;
int res = 987654321;
int count1;
int flag;
int dx[3] = { 1,-1, 0 };

void bfs(int start) {
	queue<Point> q;
	Point p;
	p.data = start;
	p.dis = 0;
	q.push(p);

	while (!q.empty()) {
		int data = q.front().data;
		int dis = q.front().dis;
		q.pop();
		// pop �Ҷ��� üũ
		visit[data] = 1;

		if (data == K) {
			ans = dis;
			if (res >= ans)
				res = ans;
			else
				continue;

			count1++;
			continue;
		}

		for (int i = 0; i < 3; i++) {
			int nx = data + dx[i];
			if (i == 2) {
				nx = 2 * data;
			}

			if (nx < 0 || nx >= 100001 || visit[nx] == 1)
				continue;

			Point p1;
			p1.data = nx;
			p1.dis = dis + 1;
			q.push(p1);
		}
	}
}

int main() {
	cin >> N >> K;

	bfs(N);

	cout << res << " " << count1 << endl;

	return 0;
}
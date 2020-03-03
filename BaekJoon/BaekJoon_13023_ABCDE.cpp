#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Point
{
	int y, dis;
	Point(int y, int dis) {
		this->dis = dis;
		this->y = y;
	}
};

int N, K;
int cnt = 1;
int map[2000][2000];
int visit[1000];
vector<int> v[2000];

void init() {
	for (int i = 0; i < N; i++)
		visit[i] = 0;
}

int dfs(int n, int cnt) {
	if (cnt == 4) {
		return 1;
	}

	for (int i = 0; i < v[n].size(); i++) {
		if (visit[v[n][i]] == 1)continue;
		//if (map[n][i] == 0) continue;
		visit[v[n][i]] = 1;
		if (dfs(v[n][i], cnt + 1) == 1) {
			return 1;
		}
		visit[v[n][i]] = 0;
	}

	return 0;
}


int main() {
	cin >> N >> K;

	for (int i = 0; i < K; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		/*map[a][b] = 1;
		map[b][a] = 1;*/
		v[a].push_back(b);
		v[b].push_back(a);
	}

	int flag = 0;
	for (int i = 0; i < N; i++) {
		visit[i] = 1;
		if (dfs(i, 0) == 1) {
			flag = 1;
			break;
		}
		visit[i] = 0;
		init();
	}

	if (flag == 1) cout << 1 << endl;
	else cout << 0 << endl;

	return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point
{
	int x, y;
	Point(int y, int x) {
		this->y = y;
		this->x = x;
	}
};

int N;
int visit[102];
vector<int> map[102];
vector<Point> v;

void dfs(int n) {

	visit[n] = 1;

	for (int i = 0; i < map[n].size(); i++) {
		if (visit[map[n][i]] == 1) continue;
		dfs(map[n][i]);
	}
}

int main() {


	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;

		for (int i = 0; i < N + 2; i++) {
			int y, x;
			cin >> y >> x;
			v.push_back(Point(y, x));
		}

		//맥주 20병으로 갈 수 있는 거리 내에 있으면 그래프에 추가
		for (int j = 0; j < N + 2; j++) {

			for (int k = j + 1; k < N + 2; k++) {

				if (abs(v[j].x - v[k].x) + abs(v[k].y - v[j].y) <= 50 * 20)
				{
					//양방향 그래프
					map[j].push_back(k);
					map[k].push_back(j);

				}
			}
		}

		// 시작
		dfs(0);

		if (visit[N + 1] == 1) {
			cout << "happy" << "\n";
		}
		else {
			cout << "sad" << "\n";
		}

		// 초기화
		for (int i = 0; i < 102; i++) {
			map[i].clear();
			visit[i] = 0;
		}
		v.clear();
	}

	return 0;
}
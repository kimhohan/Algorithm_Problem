#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 상어 정보
struct shark_point
{
	int x, y;
	int speed, dir, size;
	int num;
};

int r, c, m;
int res = 0;

vector<int> map[101][101];

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, 1, -1 };

vector<shark_point> v;

bool cmp(int A, int B)
{
	if (v[A].size > v[B].size) return true;
	return false;
}

void solution(int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		// 물고기가 러디에도 없으면 끝
		if (v.empty()) return;

		// 낚시꾼 이동후 물고기 잡음
		// 가장 땅에 가까운 상어
		for (int k = 0; k < r; k++)
		{
			int min = 987654321;
			int kill;
			/*res += v[map[k][i][0]].size;
			v[map[k][i][0]].size = 0;
			*/
			for (int t = 0; t < v.size(); t++)
			{
				if (i == v[t].x)
				{
					if (min > v[t].y)
					{
						kill = t;
						min = v[t].y;
					}
				}
			}

			if (min == 987654321) break;
			else
			{
				res += v[kill].size;
				v[kill].size = 0;
				v[kill].x = 1000;
				v[kill].y = 1000;
				//v.erase(v.begin() + kill);
				map[min][i].clear();
				break;
			}
		}

		//// 물고기 이동

		// map 초기화

		for (int e = 0; e < v.size(); e++)
		{
			if (v[e].size == 0) continue;
			int x = v[e].x;
			int y = v[e].y;
			map[y][x].clear();
		}

		//이동
		for (int e = 0; e < v.size(); e++)
		{
			if (v[e].size == 0) continue;
			int x = v[e].x;
			int y = v[e].y;
			int dir = v[e].dir;
			int speed = v[e].speed;

			if (dir == 0 || dir == 1)
			{
				int rotate = (r - 1) * 2; // 중요 !
				if (speed >= rotate) speed %= rotate;

				// 스피드 만큼 돌리기
				for (int k = 0; k < speed; k++)
				{
					int nx = x + dx[dir];
					int ny = y + dy[dir];

					if (ny < 0)
					{
						dir = 1;
						ny += 2;
					}

					if (ny >= r)
					{
						dir = 0;
						ny -= 2;
					}
					x = nx;
					y = ny;
				}
			}
			else
			{
				int rotate = (c - 1) * 2; // 중요 !
				if (speed >= rotate) speed %= rotate;

				// 스피드 만큼 돌리기
				for (int k = 0; k < speed; k++)
				{
					int nx = x + dx[dir];
					int ny = y + dy[dir];

					if (nx < 0)
					{
						dir = 2;
						nx += 2;
					}

					if (nx >= c)
					{
						dir = 3;
						nx -= 2;
					}
					x = nx;
					y = ny;
				}
			}

			// 상어 벡터 최신화
			v[e].x = x;
			v[e].y = y;
			v[e].dir = dir;

			map[y][x].push_back(e);
		}

		// 서열 정리
		for (int e = 0; e < r; e++)
		{
			for (int k = 0; k < c; k++)
			{
				if (map[e][k].size() > 1)
				{
					sort(map[e][k].begin(), map[e][k].end(), cmp);
					int live = map[e][k][0];

					for (int t = 1; t < map[e][k].size(); t++)
					{
						// 삭제
						v[map[e][k][t]].size = 0;

						v[map[e][k][t]].x = 1000;
						v[map[e][k][t]].y = 1000;
						//v.erase(v.begin() + map[e][k][t]);
					}
					map[e][k].clear();
					map[e][k].push_back(live);
				}
			}
		}

	}
}

int main()
{

	cin >> r >> c >> m;

	for (int i = 0; i < m; i++)
	{
		shark_point num;
		cin >> num.y >> num.x >> num.speed >> num.dir >> num.size;
		num.num = i;
		num.dir -= 1;
		num.y -= 1;
		num.x -= 1;
		v.push_back(num);
		map[num.y][num.x].push_back(i);
	}

	solution(c);

	cout << res << endl;

	return 0;
}
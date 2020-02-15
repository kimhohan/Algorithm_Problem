#include <iostream>

using namespace std;
int map[10][10];
int color_count[5] = { 5,5,5,5,5 };
int ans = 987654321;
int res;

void dfs(int y, int x) {
	// 해당 줄은 다 확인했으므로 다음 줄 확인
	if (x == 10)
	{
		dfs(y + 1, 0);
		return;
	}

	// 마지막 줄까지 다 확인했으므로 현재 색종이 개수 확인
	if (y == 10)
	{
		if (ans > res)
			ans = res;
		return;
	}

	// 덮을 필요 없으므로 다음 칸 확인
	if (map[y][x] == 0)
	{
		dfs(y, x + 1);
		return;
	}

	// 모든 경우의 수 다 확인
	for (int len = 4; len >= 0; len--)
	{
		// 현재 len 크기 색종이가 없거나 덮었을 때 범위를 벗어날 경우
		if (color_count[len] == 0 || y + len >= 10 || x + len >= 10)
		{
			continue;
		}

		bool flag = true;
		// len 길이만한 정사각형이 존재하는지 확인
		for (int j = 0; j <= len; j++)
		{
			for (int k = 0; k <= len; k++)
			{
				if (map[y + j][x + k] == 0)
				{
					flag = false;
					break;
				}
			}

			if (flag == false)
			{
				break;
			}
		}

		// 존재하지 않으면 확인할 필요 없음
		if (flag == false)
		{
			continue;
		}

		// 덮었다고 치고
		for (int j = 0; j <= len; j++)
		{
			for (int k = 0; k <= len; k++)
			{
				map[y + j][x + k] = 0;
			}
		}

		color_count[len]--;
		res++;

		// 다음 칸 확인
		dfs(y, x + len);

		// 덮었던 색종이를 치운다
		for (int j = 0; j <= len; j++)
		{
			for (int k = 0; k <= len; k++)
			{
				map[y + j][x + k] = 1;
			}
		}

		color_count[len]++;
		res--;
	}
}

int main() {
	//입력
	for (int i = 0; i < 10; i++) {
		for (int k = 0; k < 10; k++) {
			cin >> map[i][k];
		}
	}

	// 전부 탐색
	dfs(0, 0);

	if (ans == 987654321) ans = -1;

	cout << ans << endl;

	return 0;
}
#include <iostream>

using namespace std;
int map[10][10];
int color_count[5] = { 5,5,5,5,5 };
int ans = 987654321;
int res;

void dfs(int y, int x) {
	// �ش� ���� �� Ȯ�������Ƿ� ���� �� Ȯ��
	if (x == 10)
	{
		dfs(y + 1, 0);
		return;
	}

	// ������ �ٱ��� �� Ȯ�������Ƿ� ���� ������ ���� Ȯ��
	if (y == 10)
	{
		if (ans > res)
			ans = res;
		return;
	}

	// ���� �ʿ� �����Ƿ� ���� ĭ Ȯ��
	if (map[y][x] == 0)
	{
		dfs(y, x + 1);
		return;
	}

	// ��� ����� �� �� Ȯ��
	for (int len = 4; len >= 0; len--)
	{
		// ���� len ũ�� �����̰� ���ų� ������ �� ������ ��� ���
		if (color_count[len] == 0 || y + len >= 10 || x + len >= 10)
		{
			continue;
		}

		bool flag = true;
		// len ���̸��� ���簢���� �����ϴ��� Ȯ��
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

		// �������� ������ Ȯ���� �ʿ� ����
		if (flag == false)
		{
			continue;
		}

		// �����ٰ� ġ��
		for (int j = 0; j <= len; j++)
		{
			for (int k = 0; k <= len; k++)
			{
				map[y + j][x + k] = 0;
			}
		}

		color_count[len]--;
		res++;

		// ���� ĭ Ȯ��
		dfs(y, x + len);

		// ������ �����̸� ġ���
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
	//�Է�
	for (int i = 0; i < 10; i++) {
		for (int k = 0; k < 10; k++) {
			cin >> map[i][k];
		}
	}

	// ���� Ž��
	dfs(0, 0);

	if (ans == 987654321) ans = -1;

	cout << ans << endl;

	return 0;
}
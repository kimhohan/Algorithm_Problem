#include <iostream>
#include <vector>
using namespace std;

vector<int> v;
int N;
char map[19];
char map_co[19];
char c_map[19];
int visit[19];
int c_visit[19];
int ans = -2147483647;
int count1;
int val[9];

void copy_map(int flag) {
	if (flag == 1) {
		for (int i = 0; i < N; i++) {
			map_co[i] = map[i];
		}
	}
	else if (flag == 2) {
		for (int i = 0; i < N; i++) {
			map[i] = map_co[i];
		}
	}
}

int check(int num) {
	for (int i = 0; i < num - 1; i++) {
		if (val[i] == 1 &&  val[i + 1] == 1) return 0;
	}
	return 1;
}

int cal(int a, char op, int b) {

	if (op == '*') {
		return a * b;
	}
	else if (op == '+') {
		return a + b;
	}
	else if (op == '-') {
		return a - b;
	}
	return 0;
}

void dfs(int cnt, int g) {
	if (cnt == g) {

		// �ʿ���� ������ ����
		if (check(g) == 0) return;

		// map ����
		copy_map(1);

		// c_map �ʱ�ȭ
		for (int i = 0; i < N; i++) {
			visit[i] = 0;
			c_visit[i] = 0;
			c_map[i] = '0';
		}

		// val �� 1 �� ���� ���� ����
		for (int i = 0; i < g; i++) {
			if (val[i] == 1) {
				// ���� ����
				int c = cal(map[(i * 2)] - '0', map[(i * 2) + 1], map[(i * 2) + 2] - '0');
				visit[(i * 2)] = 1;
				visit[(i * 2) + 1] = 1;
				visit[(i * 2) + 2] = 1;
				//map[(i * 2)]�� �����ֱ�
				v.push_back(c);
			}
		}

		// �迭 �ٲٱ�
		int cc = 0;
		int dd = 0;
		for (int i = 0; i < N; i++) {
			if (visit[i] == 1) {
				if (dd == 0) {
					c_visit[cc] = 1;
					c_map[cc] = '0';
					cc++;
				}
				dd++;
				if (dd == 3)
					dd = 0;
			}
			else {
				c_map[cc] = map[i];
				cc++;
			}
		}

		// c_map �״�� ���
		int sum = 0;
		int ccc = 0;
		int num1;
		if (c_visit[0] == 1) {
			num1 = v[ccc];
			ccc++;
		}
		else num1 = c_map[0] - '0';
		for (int i = 1; i < cc - 1;) {
			int num2;
			if (c_map[i + 1] == '0' && c_visit[i + 1] == 1) {
				num2  = v[ccc];
				ccc++;
			}else{
				num2 = c_map[i + 1] - '0';
			}
			int sum = cal(num1, c_map[i],num2);
			num1 = sum;
			i += 2;
		}

		if (ans < num1)
			ans = num1;


		// map �ǵ�����
		copy_map(2);
		v.clear();
		return;
	}

	for (int i = 0; i < 2; i++) {
		val[cnt] = i;
		dfs(cnt + 1, g);
	}
}

int main() {

	// �Է�
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> map[i];
	}

	if (N == 1) {
		ans = map[0] - '0';
	}
	else if (N == 3) {
		// ���� �ϳ����̱� ������ ��ȣ�ʿ� ����
		ans = cal(map[0] - '0', map[1], map[2] - '0');
	}
	else {
		// �������� ��� ��ȣ�� �˻��� �ʿ伺�� �ִ�.
		count1 = N / 2;
		dfs(0,count1);
	}

	cout << ans << endl;

	return 0;
}

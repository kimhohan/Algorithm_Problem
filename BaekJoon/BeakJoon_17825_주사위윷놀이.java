import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;


class Main {
	static int[] arr = new int[10];
	static int[] val = new int[10];
	
	static int ans = 0;
    
	// 윷놀이 판
	static int[][] map = {

			{ 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 10, 13, 16, 19, 25, 30, 35, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 20, 22, 24, 25, 30, 35, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 30, 28, 27, 26, 25, 30, 35, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, };

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		
		// 무조건 10개
		for (int i = 0; i < arr.length; i++) {
			arr[i] = sc.nextInt();
		}

		// 조합으로 dfs
		dfs(0);

		System.out.println(ans);
		sc.close();
	}

	static void dfs(int num) {
		// 종료
		if (num == 10) {
			// 실행 - 4마리 말 조합
			// 말이 10 정해진 루트가 생기면 계산

			int[][] check = new int[4][21];
			int sum = 0;
			int[] flag_mal = new int[6];

			for (int i = 0; i < arr.length; i++) {
				int mal = val[i];
				int dis = arr[i];

				// 이동 시작
				int flag = 0;
				int cx = 0, cy = 0;

				// 이동이 끝난 말이 라면 PASS
				if (flag_mal[mal] == 1)
					continue;

				// 현재말과 겹치는 말이 있는지 확인
				run: for (int k = 0; k < 4; k++) {
					for (int r = 0; r < 21; r++) {
						if (mal == check[k][r]) {
							check[k][r] = 0;
							flag = 1;
							cx = r;
							cy = k;
							break run;
						}
					}
				}

				// 현재 저장된 말이 있다면 그말을 움직여야 한다.
				if (flag == 1) {
					int forty = 0;
					int ff = 0;
					int nnx = cx;
					int nny = cy;

					// 일단 이동
					for (int t = 0; t < dis; t++) {
						if (map[nny][nnx] == 40)
							forty = 1;
						if (nny != 3 && nnx != 0) {
							if (map[nny][nnx] == 25 || map[nny][nnx] == 30 || map[nny][nnx] == 35)
								ff = 1;
						}
						cx++;
					}

					// 40인 자리에서는 모든 배열 자리를 0으로 만들어준다.
					if (forty == 1) {
						check[0][20] = 0;
						check[1][7] = 0;
						check[2][6] = 0;
						check[3][7] = 0;
						flag_mal[mal] = 1;
						continue;
					}
					
					// 40이 아니라면 예외는 그냥 PASS
					else {
						if (ff == 1) {
							if (map[nny][nnx] == 25) {
								check[1][4] = 0;
								check[2][3] = 0;
								check[3][4] = 0;
							} else if (map[nny][nnx] == 30) {
								check[1][5] = 0;
								check[2][4] = 0;
								check[3][5] = 0;
							} else if (map[nny][nnx] == 35) {
								check[1][6] = 0;
								check[2][5] = 0;
								check[3][6] = 0;
							}
						}
						// 말이 이동을 끝냄
						if ((cy == 0 && cx >= 21) || (cy == 1 && cx >= 8) || (cy == 2 && cx >= 7)
								|| (cy == 3 && cx >= 8)) {
							flag_mal[mal] = 1;
							continue;
						}
						// 옮겼는데 배열이 바뀌는 자리라면
						else if (cy == 0 && map[cy][cx] == 10) {
							cy = 1;
							cx = 0;
							if (check[cy][cx] > 0) {
								check[nny][nnx] = mal;
								return;
							}

							check[cy][cx] = mal;
							sum += map[cy][cx];

						} else if (cy == 0 && map[cy][cx] == 20) {
							cy = 2;
							cx = 0;
							if (check[cy][cx] > 0) {
								check[nny][nnx] = mal;
								return;
							}

							check[cy][cx] = mal;
							sum += map[cy][cx];

						} else if (cy == 0 && map[cy][cx] == 30) {
							cy = 3;
							cx = 0;
							if (check[cy][cx] > 0) {
								check[nny][nnx] = mal;
								return;
							}
							check[cy][cx] = mal;
							sum += map[cy][cx];
						} else if (check[cy][cx] > 0) {
							check[nny][nnx] = mal;
							return;
						} else if (map[cy][cx] == 40) {

							check[0][20] = mal;
							check[1][7] = mal;
							check[2][6] = mal;
							check[3][7] = mal;
							sum += map[cy][cx];
						} else if (map[cy][cx] == 25) {

							check[1][4] = mal;
							check[2][3] = mal;
							check[3][4] = mal;
							sum += map[cy][cx];
						} else if (nny != 0 && map[cy][cx] == 30) {

							check[1][5] = mal;
							check[2][4] = mal;
							check[3][5] = mal;
							sum += map[cy][cx];
						} else if (map[cy][cx] == 35) {

							check[1][6] = mal;
							check[2][5] = mal;
							check[3][6] = mal;
							sum += map[cy][cx];
						} else {
							check[cy][cx] = mal;
							sum += map[cy][cx];
						}

					}

				}

				// 아무말이 업거나 새로운말이 출발할때
				else if (flag == 0) {
					int k = 0, r = 0;
					// 우선 이동
					for (int t = 0; t < dis; t++) {
						r++;
					}

					// 이동하려는데 말이이있다면 못 움직임
					if (check[k][r] > 0) {
						return;
					}
					
					// 통과
					if (map[k][r] == 10) {
						k = 1;
						r = 0;
						if (check[k][r] > 0)
							return;
						check[k][r] = mal;
						sum += map[k][r];

					} else {
						check[k][r] = mal;
						sum += map[k][r];
					}
				}
				// 최대 찾기
				if (ans < sum) {
					ans = sum;
				}
			}
			return;
		}

		for (int i = 0; i < 4; i++) {
			val[num] = i + 1;
			dfs(num + 1);
		}
	}
}
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Solution_7699 {
	static int Y, X;
	static int result;
//	static char[][] map;
	static int[][] map;
	static int[] dx = {0,0,1,-1};
	static int[] dy = {1,-1,0,0};
//	static int[][] v; //0,1,2,3
//	static int[] v; 
	static int v; // 비트마스크
//	static Set<Character> set = new HashSet();
	
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		
		for(int tc = 1; tc <= t; tc++) {
			result = 0;
//			set.clear();
			// 입력
			Y = sc.nextInt();
			X = sc.nextInt();
			map = new int[Y][X];
//			map = new char[Y][X];
//			v = new int[Y][X];
//			v = new int[26 + 1];
			v = 0;
			
			for(int i = 0; i < Y; i++) {
				String s = sc.next();
				for(int k = 0; k < X; k++) {
//					map[i][k] = s.charAt(k);
					map[i][k] = s.charAt(k) - 'A';
				}
			}
			
			//처리 
			dfs(0,0,1);
			
			//출력
			System.out.println("#" + tc + " " + result);
		}
	}
	static void dfs(int y, int x, int cnt) {
		//종료
		result = Math.max(result, cnt);
		if(cnt == 26) {
			return;
		}
		//실행 재귀
		v |= 1 << map[y][x];
//		v[map[y][x]] = 1;
//		v[y][x] = 1;
//		set.add(map[y][x]);
		int nx, ny;
		for(int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			
//			if(nx < 0 || ny < 0 || nx >= X || ny >= Y || v[ny][nx] == 1)
//				continue;
//			if(nx < 0 || ny < 0 || nx >= X || ny >= Y || v[map[ny][nx]]== 1)
//				continue;
			if(nx < 0 || ny < 0 || nx >= X || ny >= Y || (v & 1<<map[ny][nx]) != 0)
				continue;
			// 알파벳 중복 체크
//			if(set.contains(map[ny][nx]) == true) {
//				continue;
//			}
			
			dfs(ny, nx, cnt + 1);
			v &= ~(1<<map[ny][nx]);
//			v[map[ny][nx]] = 0;
//			v[ny][nx] = 0;
//			set.remove(map[ny][nx]);
		}
	}
}

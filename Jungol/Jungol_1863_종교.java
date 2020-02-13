import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Solution5 {
	static int n;
	static int m;
	static int[] visit;
	static int ans;
	static ArrayList<Integer>[] list;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		m = sc.nextInt();
		
		visit = new int[n];
		list = new ArrayList[n];
		// 초기화
		for(int i = 0; i < n; i++)
			list[i] = new ArrayList<Integer>();
		
		// 입력
		for(int i = 0; i < m; i++) {
			int x = sc.nextInt();
			x--;
			int y = sc.nextInt();
			y--;
			list[x].add(y);
			list[y].add(x);
		}
		
		// 탐색시작
		for(int i = 0; i < n; i++) {
			if(visit[i] == 1) continue;
			bfs(i);
			ans++;
		}
		
		// 결과
		System.out.println(ans);
	}
	static void bfs(int num) {
		Queue<Integer> q = new LinkedList<>();
		visit[num] = 1;
		q.offer(num);
		
		while(!q.isEmpty()) {
			int n = q.poll();
			for(int i = 0; i < list[n].size(); i++) {
				if(visit[list[n].get(i)] == 1) continue;
				visit[list[n].get(i)] = 1;
				q.offer(list[n].get(i));
			}
		}
	}
}

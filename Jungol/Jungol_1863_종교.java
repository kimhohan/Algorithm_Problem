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
		// �ʱ�ȭ
		for(int i = 0; i < n; i++)
			list[i] = new ArrayList<Integer>();
		
		// �Է�
		for(int i = 0; i < m; i++) {
			int x = sc.nextInt();
			x--;
			int y = sc.nextInt();
			y--;
			list[x].add(y);
			list[y].add(x);
		}
		
		// Ž������
		for(int i = 0; i < n; i++) {
			if(visit[i] == 1) continue;
			bfs(i);
			ans++;
		}
		
		// ���
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

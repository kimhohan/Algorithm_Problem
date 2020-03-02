import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * 
 * 4
 * 1 2
 * 1 3
 * 1 4
 * �ڱ��ڽ��� ����Ǽ� : �ڽ��� ���� ����� ��(1) �� ���϶� ����� ��(2*2*2)�� ����
 */
// �ڱ��ڽ��� ����Ǽ� : �ڽ��� ���� ����� �� �� ���϶� ����� ���� ����
// �ڱ� �ڽ��� �ڽĵ��� ����� ��: �ڽĵ��� ����� ���� ��� ��

public class Solution_4534_Ʈ�� {
	static final int MOD = 1000000007;
	static int N;
	static List<Integer>[] adj;
	static long[][] memo; //����, ���� ��ȣ
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int t = sc.nextInt();
		
		for(int tc = 1; tc <= t; tc++) {
			N = sc.nextInt();
			adj = new ArrayList[N +1];
			for(int i =1; i <= N; i++)
				adj[i] = new ArrayList<>();
			
			memo = new long[2][N+1];
			
			for(int i = 1; i < N; i++) {
				int a = sc.nextInt();
				int b = sc.nextInt();
				adj[a].add(b);
				adj[b].add(a);
			}
			
			long ans = (dfs(1,0,-1) + dfs(1,1,-1)) % MOD;
			System.out.println("#" + tc + " " + ans);
		}
	}
	// �θ�� Ž������ �ʴ´�.
	static long dfs(int v, int color, int parent) {
		// memo[color][v]�� ���� �Ѵٸ� , �ٽ� ������� �Ѱ�, �˰� �ִ��� ����.
		if(memo[color][v] != 0)
			return memo[color][v];
		long ret= 1;
		
		// color�� ��(0)�� ���.
		// �ڽ� ������ ��(1)���� ĥ�� ����� ����� ������ ��
		if(color == 0) {
			// ���� ���� v���� ����� ��� ������ ���Ͽ�
			for(int i = 0; i < adj[v].size(); i++) {
				if(adj[v].get(i) != parent) {
					ret *= dfs(adj[v].get(i),1,v);
					ret%= MOD;
				}
			}
			
		}
		// color ��(1)�ΰ��
		else {
			for(int i = 0; i < adj[v].size(); i++) {
				if(adj[v].get(i) != parent) {
					// �ڽ� ������ ��(1)���� ĥ�� ����� ����� ������ ��
					ret *= (dfs(adj[v].get(i),1,v) + dfs(adj[v].get(i),0,v));
					ret%= MOD;
					// �ڽ� ������ ��(0)���� ĥ�� ����� ����� ������ ��
				}
			}
		}
		
		// memo[color][v] �� ���
		memo[color][v] = ret;
		return ret;
	}
}

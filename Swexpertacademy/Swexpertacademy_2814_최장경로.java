import java.util.Scanner;

public class ������2 {
    static int N;
    static int M;
    static int[][] adj;
    //� �湮üũ���·�, � ������ �����ߴ���.
    static int[][] memo;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for(int tc = 1; tc <= T; tc++) {
            N = sc.nextInt(); //������ ���� 1 �� N �� 10
            M = sc.nextInt(); //������ ���� <= 20
            adj = new int[N+1][N+1];
            memo = new int[1 << (N+1)][N+1];
            for(int i = 0; i < M; i++) {
                int a = sc.nextInt();
                int b = sc.nextInt();
                adj[a][b] = 1;
                adj[b][a] = 1;
            }
            ans = 0;
            for(int i = 1; i <= N; i++) {
                ans = Math.max(ans, dfs(i, 1 << i)); 
	}
            System.out.println("#" + tc + " " + ans);
        }
    }
    
    static int ans = 0;
    static int dfs(int v, int visited) {
        //�̹� ����� ����� �ִٸ� �ش� ���� ����
        if( memo[visited][v] != 0 )
            return memo[visited][v];
        
        //���̻� �湮�� ��尡 ������ ���� �湮�ϴ� ���1������ ���� ��� �̹Ƿ�, �ʱⰪ 1
        int ret = 1;
        //��� ��带 �˻��ϸ�, �湮���� ��尡 �ִٸ� ���ȣ�� �ϰ�, �ش� ȣ���� ��尡 ������ ������ ��+1 �� �ִ밪�� ���
        for(int i = 1; i <= N; i++) {
            if( adj[v][i] == 1 && (visited & (1 << i)) == 0) {
                ret = Math.max(ret, dfs(i, visited | (1 << i))+1);
            }
        }
        //���� ��������� ���� �����ΰ��� ���
        memo[visited][v] = ret;
        return ret;
    }
}
import java.util.Scanner;

public class 최장경로2 {
    static int N;
    static int M;
    static int[][] adj;
    //어떤 방문체크상태로, 어떤 정점에 도달했는지.
    static int[][] memo;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for(int tc = 1; tc <= T; tc++) {
            N = sc.nextInt(); //정점의 갯수 1 ≤ N ≤ 10
            M = sc.nextInt(); //간선의 갯수 <= 20
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
        //이미 계산한 기억이 있다면 해당 값을 리턴
        if( memo[visited][v] != 0 )
            return memo[visited][v];
        
        //더이상 방문할 노드가 없으면 현재 방문하는 노드1개만이 남은 경로 이므로, 초기값 1
        int ret = 1;
        //모든 노드를 검사하며, 방문안한 노드가 있다면 재귀호출 하고, 해당 호출한 노드가 가지는 최장경로 값+1 중 최대값을 기억
        for(int i = 1; i <= N; i++) {
            if( adj[v][i] == 1 && (visited & (1 << i)) == 0) {
                ret = Math.max(ret, dfs(i, visited | (1 << i))+1);
            }
        }
        //계산된 현재상태의 남은 최장경로값을 기억
        memo[visited][v] = ret;
        return ret;
    }
}
import java.util.Scanner;

public class Main_1699 {
	static int N;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		N = sc.nextInt();
		int []dp = new int[N+1];
		for(int i = 0; i <= N; i++)
			dp[i]  = i;
		
		for(int i = 4; i<= N; i++) {
			for(int k = 2; k*k <= i; k++) {
				dp[i] = Math.min(dp[i], dp[i - (k*k)] + 1);
			}
		}
		System.out.println(dp[N]);
		sc.close();
	}
}


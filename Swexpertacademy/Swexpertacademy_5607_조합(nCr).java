import java.math.BigInteger;
import java.util.Scanner;

public class Solution_5607 {
	static int N, R;
	static int mod = 1234567891;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int t = sc.nextInt();

		for (int tc = 1; tc <= t; tc++) {
			N = sc.nextInt();
			R = sc.nextInt();

			long[] fac = new long[N + 1];
			fac[0] = 1;
			
			for (int i = 1; i <= N; i++) fac[i] = (fac[i - 1] * i) % mod;

			BigInteger mods = BigInteger.valueOf(mod);
			BigInteger up_Num = BigInteger.valueOf(fac[N]);
			BigInteger down_Num1 = BigInteger.valueOf(fac[R]).modInverse(mods).remainder(mods);
			BigInteger down_Num2 = BigInteger.valueOf(fac[N -R]).modInverse(mods).remainder(mods);
			
			BigInteger ans = up_Num.multiply(down_Num1).multiply(down_Num2).remainder(mods);
			
			System.out.println("#" + tc + " " + ans);
		}

		sc.close();
	}

}

// 페르마 소정리
import java.math.BigInteger;
import java.util.Scanner;

public class Solution {
	static int N, R;
	static int mod = 1234567891;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int t = sc.nextInt();

		for (int tc = 1; tc <= t; tc++) {
			N = sc.nextInt();
			R = sc.nextInt();

			long[] fac = new long[N + 1];
			fac[0] = 1;
			
			for (int i = 1; i <= N; i++)
				fac[i] = (fac[i - 1] * i) % mod;

			long down_Num = (fac[R] * fac[N - R]) % mod;

			long res = fermat(down_Num, mod - 2);

			long ans = (fac[N] * res) % mod;

			System.out.println("#" + tc + " " + ans);
		}

		sc.close();
	}

	private static long fermat(long n, int x) {
		if (x == 0)
			return 1;
		long tmp = fermat(n, x / 2);
		long ret = (tmp * tmp) % mod;
		if (x % 2 == 0)
			return ret;
		else
			return (ret * n) % mod;
	}
}

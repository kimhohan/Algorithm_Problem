import java.util.Scanner;

public class Solution {
    static int result;
    static int n, m; //행, 열 갯수
    static int[][] map;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int TC = sc.nextInt();
        for(int t = 1; t <= TC ; t++) {
            n = sc.nextInt();
            m = sc.nextInt();
            map = new int[n][m];
            for(int i = 0 ; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    map[i][j] = sc.nextInt();
                }
            }
//            사이즈정해져있으면
//            처리
            result = dfs(0,0,n,m, Integer.MAX_VALUE);
//            출력
            System.out.println("#" + t +  " " + result);
        }

    }
    static int dfs(int y, int x, int h, int w, int min) {
//        종료
        if(w == 1 && h == 1) {
            return 0;
        }
//        실행
//        기존에 있던 덩어리의 건포도 개수
        int sum  = 0;
        for(int i = y; i < y + h; i++) {
            for(int j = x; j < x + w; j++) {
                sum += map[i][j];
            }
        }
//        가로로 나누어서 비용을 최소비용을 구한다.
        for(int i = 1; i < h;i++) {
//            위쪽 비용
            int sum1 = dfs(y,x,i,w, min);
//            아래쪽 비용
            int sum2 = dfs(y + i,x,h-i,w, min);
            int sum3 = sum + sum1 + sum2;
            min = Math.min(min, sum3);
        }
//        세로로 나누어서 비용을 최소비용을 구한다.
        for(int i = 1;i < w; i++) {
//            왼쪽 비용
            int sum1 =  dfs(y,x,h,i, min);
//            오른쪽 비용
            int sum2 =  dfs(y,x+i,h,w-i, min);
            int sum3 = sum + sum1 + sum2;
            min = Math.min(min, sum3);
        }
//        재귀호출
        return min;
    }

}
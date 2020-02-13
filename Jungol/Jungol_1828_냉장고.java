import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;
 
public class Main{
    static int N;
    static ArrayList<point> list = new ArrayList<>();
 
    static class point {
        int min, max;
 
        public point(int min, int max) {
            this.min = min;
            this.max = max;
        }
    }
 
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
 
        N = sc.nextInt();
 
        // 입력
        for (int i = 0; i < N; i++) {
            int mi = sc.nextInt();
            int ma = sc.nextInt();
            list.add(new point(mi, ma));
        }
 
        // sort 하기 내림차순 max 기준
        Collections.sort(list, new Comparator<point>() {
 
            @Override
            public int compare(point arg0, point arg1) {
                // TODO Auto-generated method stub
                if (arg0.max < arg1.max)
                    return 1;
                return -1;
            }
        });
        point temp = list.get(0);
        // 냉장고 탐색 시작
        int s = temp.min;
        int e = temp.max;
        int count = 1;
 
        // 전부 돌림
        for (int i = 1; i < list.size(); i++) {
            // 다음 max 끝이랑 s 비교
            if (s > list.get(i).max) {
                count++;
                s = list.get(i).min;
                e = list.get(i).max;
            } else {
                e = list.get(i).max;
                if (s < list.get(i).min) {
                    s = list.get(i).min;
                }
            }
        }
 
        System.out.println(count);
    }
}
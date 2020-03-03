import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Solution_1907_�𷡼� {
    static class Node{
        int r, c;
        Node(int r, int c){
            this.r = r;
            this.c = c;
        }
    }
    static int[] dr = {-1, -1, -1, 0, 1, 1, 1, 0};
    static int[] dc = {-1, 0, 1, 1, 1, 0, -1, -1};
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for(int tc = 1; tc <= T; tc++) {
            int H = sc.nextInt(); //1 �� H, W �� 1,000
            int W = sc.nextInt();
            int[][] map = new int[H][W];
            for(int r = 0; r < H; r++) {
                String str = sc.next();
                for(int c = 0; c < W; c++) {
                    if( str.charAt(c) != '.' )
                        map[r][c] = str.charAt(c) - '0';
                }
            }
            Queue queue = new LinkedList<>();
            for(int r = 0; r < H; r++) {
                for(int c = 0; c < W; c++) {
                    //�ٴٶ��
                    if( map[r][c] == 0 ) {
                        //8�濡 ���ؼ� �𷡰� �����Ѵٸ� �߰����� 1 ����    
                        for(int d = 0; d < 8; d++) {
                            int nr = r + dr[d];
                            int nc = c + dc[d];
                            if( nr < 0 || nc < 0 || nr >= H || nc >= W)
                                continue;
                            if( map[nr][nc] != 0 ) {
                                map[nr][nc]--;
                                if( map[nr][nc] == 0 ) {
                                    //������ �𷡿����� �￩�� �ٴٰ� �� ģ���� -1�� ǥ������.
                                    map[nr][nc] = -1;
                                    //���� ȸ������ �ֺ� ���� �߰����� ���̱� ���� ť�� ����.
                                    queue.add(new Node(nr,nc));
                                }
                            }
                        }
                    }
                }
            }
            int ans = 0;
            while(!queue.isEmpty()) {
                int size = queue.size();
                for(int i = 0; i < size; i++) {
                    //���� �������� �ٴٷ� �� ģ����
                    Node node = (Node) queue.poll();
                    for(int d = 0; d < 8; d++) {
                        int nr = node.r + dr[d];
                        int nc = node.c + dc[d];
                        if( nr < 0 || nc < 0 || nr >= H || nc >= W)
                            continue;
                        //�𷡰� �߰ߵǸ�
                        if( map[nr][nc] > 0 ) {
                            map[nr][nc]--;
                            if( map[nr][nc] == 0 ) {
                                //������ �𷡿����� �￩�� �ٴٰ� �� ģ���� -1�� ǥ������.
                                map[nr][nc] = -1;
                                //���� ȸ������ �ֺ� ���� �߰����� ���̱� ���� ť�� ����.
                                queue.add(new Node(nr,nc));
                            }
                        }
                    }
                }
                ans++;
            }
            System.out.println("#" + tc + " " + ans);
        }
    }
}
import java.util.Scanner;
 
public class Solution {
    public static void main(String[] args) {
        STree tree = new STree();
        Scanner sc = new Scanner(System.in);
         
        for(int i = 0; i < 10; i++) {
            // 입력 받기
            int N = sc.nextInt();
            String ch_nl = sc.nextLine();
             
            char[] r = new char[100];
            int[] r_c = new int[100];
            int cnt = 0;
            int n_count = 0;
            char comp = ' ';
            int c_count = 0;
             
            for(int k = 0; k < N; k++) {
                String ch = sc.nextLine();
                String[] c = ch.split(" ");
                 
                char[] al = c[1].toCharArray();
                r[k] = al[0];
                r_c[k] = k;
                 
                if(cnt == 2) {
                    cnt = 0;
                    n_count++;
                    comp = r[n_count];
                    c_count = r_c[n_count];
                }
                if(k == 0) {
                    comp = r[n_count];
                    c_count = r_c[n_count];
                    tree.setRoot(al[0], 0);
                }
                else if((k%2) == 0) {
                    tree.setRight(comp ,c_count, al[0], k);
                    cnt ++;
                }
                else {
                    tree.setLeft(comp ,c_count, al[0], k);
                    cnt++;
                }
            }
             
            System.out.print("#" + (i + 1) + " ");
            tree.inOrder(tree.root);
            System.out.println();
        }
    }
 
    static class STree {
        Node root;
 
        void inOrder(Node temp) {
            // 종료
            if(temp == null) return;
            inOrder(temp.left);
            System.out.print(temp.data);
            inOrder(temp.right);            
        }
         
        void setRoot(char data, int count) {
            root = new Node(data, count);
        }
 
        void setLeft(char parent, int f,char child, int count) {
            Node temp = search(parent, f);
            if(temp == null) {
                System.out.println("NO FIND");
                return ;
            }
            temp.left = new Node(child, count);
        }
         
        void setRight(char parent,int f, char child, int count) {
            Node temp = search(parent, f);
            if(temp == null) {
                System.out.println("NO FIND");
                return ;
            }
            temp.right = new Node(child, count);
        }
         
        Node search(char pdata, int f) {
            return search(root, pdata, f);
        }
         
        Node search(Node temp, char pdata, int f) {
             
            // 종료
            if (temp != null) {
                if (temp.data == pdata && temp.count == f) {
                    return temp;
                }
            }
            // 재귀
            Node nLeft = temp.left;
            Node nRight = temp.right;
            if(nLeft == null && nRight == null) {
                return null;
            }
            if(nLeft != null && nRight != null) {
                if(nLeft.data == pdata && temp.count == f) {
                    return nLeft;
                }
                if(nRight.data == pdata && temp.count == f) {
                    return nRight;
                }
                Node n1 = search(nLeft, pdata, f);
                Node n2 = search(nRight, pdata, f);
                if(n1 == null && n2 == null) {
                    return null;
                }
                if(n1 != null) {
                    return n1;
                }
                if(n2 != null) {
                    return n2;
                }
            }
             
            if(nLeft != null) {
                if(nLeft.data == pdata && temp.count == f) {
                    return nLeft;
                }
                return search(nLeft, pdata, f);
            }
            if(nRight != null) {
                if(nRight.data == pdata && temp.count == f) {
                    return nLeft;
                }
                return search(nRight, pdata, f);
            }
             
            return null;
        }
    }
 
    static class Node {
        char data;
        int count;
        Node left;
        Node right;
 
        public Node(char data, int count) {
            this.data = data;
            this.count = count;
        }
 
        public Node(char data, Node left, Node right) {
            this.data = data;
            this.left = left;
            this.right = right;
        }
 
        @Override
        public String toString() {
            return "Node [data=" + data + ", count=" + count + ", left=" + left + ", right=" + right + "]";
        }
 
 
 
    }
}
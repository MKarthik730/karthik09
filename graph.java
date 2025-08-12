
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class graph {
    static class Node{
        int src;
        int dest;
      public Node(int src,int dest) {
        this.src=src;
        this.dest=dest;
    }
         }
         static void bgraph(ArrayList<Node> cgraph[]){
            for(int i=0;i<cgraph.length;i++){
                cgraph[i]=new ArrayList<>();
            }
                cgraph[0].add(new Node(0,1));
                cgraph[0].add(new Node(0,2));
                cgraph[1].add(new Node(1, 2));
                cgraph[2].add(new Node(2,0));
                cgraph[2].add(new Node(3,0));
                cgraph[2].add(new Node(2,3));
         }
         static void dfs(ArrayList<Node> cgraph[], int curr, boolean vis[]){
                     if(vis[curr]){
                        return;
                     }
                     System.out.print(curr+" ");
                     vis[curr]=true;
                     for(int i=0;i<cgraph[curr].size();i++){
                        Node n=cgraph[curr].get(i);
                        dfs(cgraph, n.dest, vis);
                     }
         }
          
            static void bfs(ArrayList<Node> cgraph[], int v){
                boolean vis[]=new boolean[v];
                Queue<Integer> q= new LinkedList<>();
                q.add(0);
                while(!q.isEmpty()){
                    int curr=q.remove();
                    if(!vis[curr]){
                          System.out.print(curr+" ");
                          vis[curr]=true;
                    }
                    for(int i=0;i<cgraph[curr].size();i++){
                            Node e= cgraph[curr].get(i);
                            q.add(e.dest);
                    }
                }
            }
public static void main(String[] args) {
    int v=4;
    ArrayList<Node> agraph[]=new ArrayList[v];
    bgraph(agraph);
    dfs(agraph, 0,new boolean[v]);
System.out.println();
    bfs(agraph, v);
}
        }


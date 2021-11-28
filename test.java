import java.io.*;
import java.util.*;


public class TestClass {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter wr = new PrintWriter(System.out);
        int T = Integer.parseInt(br.readLine().trim());
        for(int t_i = 0; t_i < T; t_i++)
        {
            int N = Integer.parseInt(br.readLine().trim());
            int Q = Integer.parseInt(br.readLine().trim());
            int[][] roads = new int[N-1][2];
            for(int i_roads = 0; i_roads < N-1; i_roads++)
            {
            	String[] arr_roads = br.readLine().split(" ");
            	for(int j_roads = 0; j_roads < arr_roads.length; j_roads++)
            	{
            		roads[i_roads][j_roads] = Integer.parseInt(arr_roads[j_roads]);
            	}
            }
            int[][] queries = new int[Q][2];
            for(int i_queries = 0; i_queries < Q; i_queries++)
            {
            	String[] arr_queries = br.readLine().split(" ");
            	for(int j_queries = 0; j_queries < arr_queries.length; j_queries++)
            	{
            		queries[i_queries][j_queries] = Integer.parseInt(arr_queries[j_queries]);
            	}
            }

            long[] out_ = findMaxDistance(N, Q, roads, queries);
            System.out.print(out_[0]);
            for(int i_out_ = 1; i_out_ < out_.length; i_out_++)
            {
            	System.out.print(" " + out_[i_out_]);
            }
            
            System.out.println();
            
         }

         wr.close();
         br.close();
    }

    

    static int mxlvl = 0, end1 = -1;
    public static void findmax(int u, int p, int lvl, ArrayList<ArrayList<Integer>> gp)
    {
        // System.out.println(u);
        for(int v : gp.get(u))
        {
            if(v != p)
            {
                if(lvl + 1 > mxlvl)
                {
                    mxlvl = lvl + 1;
                    end1 = v;
                }
                findmax(v, u, lvl+1, gp);
            }
        }
    }

    public static void filldia(int u, int p, int lvl, ArrayList<ArrayList<Integer>> gp, ArrayList<Integer> ds)
    {
        // System.out.println(u);
        for(int v : gp.get(u))
        {
            if(v != p)
            {
                if(lvl + 1 == mxlvl)
                    ds.add(v);
                filldia(v, u, lvl+1, gp, ds);
            }
        }
    }

    public static void filldist(int u, int p, ArrayList<ArrayList<Integer>> gp, long dist[])
    {
        for(int v : gp.get(u))
        {
            if(v != p)
            {
                dist[v] = Math.max(dist[u] + 1, dist[v]);
                filldist(v, u, gp, dist);
            }
        }
    }


    static long[] findMaxDistance(int N, int Q, int[][] roads, int[][] queries){
       // Write your code here

        ArrayList<ArrayList<Integer>> gp = new ArrayList<ArrayList<Integer>>();
        for(int i = 0; i < N; i++)
            gp.add(new ArrayList<Integer>());
        
        for(int i = 0; i < N-1; i++)
        {
            --roads[i][0];
            --roads[i][1];
            gp.get(roads[i][0]).add(roads[i][1]);
            gp.get(roads[i][1]).add(roads[i][0]);
        }


        ArrayList<Integer> d1 = new ArrayList<Integer>();
        ArrayList<Integer> d2 = new ArrayList<Integer>();

        findmax(0, -1, 0, gp);

        mxlvl = 0;
        findmax(end1, -1, 0, gp);
        filldia(end1, -1, 0, gp, d2);
        mxlvl = 0;
        findmax(d2.get(0), -1, 0, gp);
        filldia(d2.get(0), -1, 0, gp, d1);

        long dist1[] = new long[N];
        long dist2[] = new long[N];
        dist1[d1.get(0)] = 0;
        filldist(d1.get(0), -1, gp, dist1);
        dist2[d2.get(0)] = 0;
        filldist(d2.get(0), -1, gp, dist2);
        
        long[] result = new long[Q];
        for(int i = 0; i < Q; i++)
        {
            int city = queries[i][0]-1;
            long time = queries[i][1];
            if(N == 1)
            {
                result[i] = 0;
                continue;
            }
            if(N == 2)
            {
                result[i] = time;
                continue;
            }

            long sum = 0;
            boolean fl = true;
            
            if(dist1[city] >= dist2[city])
            {
                sum += dist1[city];
                city = d1.get(0);
                fl = false;
            }
            else
            {
                sum += dist2[city];
                city = d2.get(0);
            }
            if(--time > 0)
            {
                if(fl) sum += (long)time*dist1[city];
                else sum += (long)time*dist2[city];
            }

            result[i] = sum;
        }
        

        return result;
    
    }
}
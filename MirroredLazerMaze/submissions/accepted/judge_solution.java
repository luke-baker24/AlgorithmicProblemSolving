import java.io.*;
import java.util.*;

/**
 * The trick is to realize that the laser can only move in 4 directions.
 * And after looking up similar solutions online, the way to solve this most optimally
 * Seems to be a 0-1 BFS, similar to the one used in Dijkstra's algorithm that we
 * were taught in class.
 *  Use the runner.py file, to run the judge solution. using the command:
 *  python runner.py from the MirroredLazerMaze directory.
 */
public class judge_solution {

    // movement arrays, for example north is moving up so reduce row -> -1
    // and col stays the same -> 0
    // in order of N,E,S,W
    private static final int[] DR = {-1, 0, 1, 0};
    private static final int[] DC = { 0, 1, 0,-1};

    //The mapping is that north is  0, east is  1, south is  2, and west is 3 
    // direction changes after we hit our two types of mirrors
    // in order of N,E,S,W
    // (forwarD) slash “/” converts N to E, E to S, S to W, W to N
    // Essentially (0->1, 1->2, 2->3, 3->0) for the / mirror
    // backslash “\” converts N to W, E to N, S to E, W to S
    // Similarly, (0->3, 1->0, 2->1, 3->2) for the \ mirror

    private static final int[] SLASH = {1, 0, 3, 2};  
    private static final int[] BACK  = {3, 2, 1, 0}; 

    // just define a large number for infinity, instead of using Integer.MAX_VALUE
    private static final int INF = 1_000_000_000;

    public static int solve(BufferedReader br) throws IOException {

        //accept inputs

        StringTokenizer st = new StringTokenizer(br.readLine());
        int R = Integer.parseInt(st.nextToken());
        int C = Integer.parseInt(st.nextToken());

        char[][] g = new char[R][C];

        // keep track of source row and col, as well as target row and col
        int sr = -1, sc = -1, tr = -1, tc = -1;

        for (int r = 0; r < R; r++) {
            String row = br.readLine();
            
            for (int c = 0; c < C; c++) {

                g[r][c] = row.charAt(c);

                if (g[r][c] == 'S')
                    { 
                        sr = r; 
                        sc = c; 
                    }
                if (g[r][c] == 'T')
                    {
                        tr = r;
                        tc = c;
                    }
            }
        }

        // our 0-1 BFS setup starts below

        // simple logic -> dist[r][c][d] shows us the  min cost to reach (r,c) facing dir d
        int[][][] dist = new int[R][C][4];

        for (int[][] matrix : dist) 
            for (int[] d_arr : matrix) // Changed variable name d to d_arr to avoid conflict 
                Arrays.fill(d_arr, INF);


        // we seed our sr, and sc, the source row and col, with all 4 directions set to 0

        //note that every deque contains an array of 3 elements
        // representing row, col, and direction
        Deque<int[]> q = new ArrayDeque<>();
        for (int d_init = 0; d_init < 4; d_init++) { // Changed variable name d to d_init
            dist[sr][sc][d_init] = 0;
            q.addFirst(new int[]{sr, sc, d_init}); // initialize dq with 0 cost
        }

        // search 
        while (!q.isEmpty()) {
            //pop from the front of our dq
            int[] cur = q.pollFirst();

            //make life easier
            int r = cur[0];
            int c = cur[1];
            int d = cur[2]; // Current direction
            int cost = dist[r][c][d];

            if (r == tr && c == tc) 
                return cost;   // reached target


        
            // go straight in the direction we were going in with cost 0
            //in(...) is a helper function defined below for bounds checking
            
            // new row and col
            int nr = r + DR[d];
            int nc = c + DC[d];

            // If the next cell is inside the grid and not a wall
            // and we discover a cheaper path
            // update its distance and push it to the front of the dq

            if (in(nr, nc, R, C) && g[nr][nc] != '#' && cost < dist[nr][nc][d]) {
                dist[nr][nc][d] = cost;
                q.addFirst(new int[]{nr, nc, d});
            }

            // place mirror here with cost 1
            //it has to be an empty cell, as we can't place
            // a mirror on a wall or on S or T

            if (g[r][c] == '.') {
                // Try placing a '/' mirror
                // new direction and coords below
                int nd1 = SLASH[d];    
                int nr1 = r + DR[nd1];
                int nc1 = c + DC[nd1];

                if (in(nr1, nc1, R, C) && g[nr1][nc1] != '#' && cost + 1 < dist[nr1][nc1][nd1]) {
                    // update distance
                    dist[nr1][nc1][nd1] = cost + 1;
                    // push to back of deque with cost 1
                    q.addLast(new int[]{nr1, nc1, nd1});
                }

                // Try placing a '\' mirror now
                int nd2 = BACK[d]; 
                int nr2 = r + DR[nd2];
                int nc2 = c + DC[nd2];

                if (in(nr2, nc2, R, C) && g[nr2][nc2] != '#' && cost + 1 < dist[nr2][nc2][nd2]) {
                    // update distance
                    dist[nr2][nc2][nd2] = cost + 1;
                    // same as above, we push to the back of deque with cost 1
                    q.addLast(new int[]{nr2, nc2, nd2});
                }
            }


        }
        return -1; // impossible so return -1
    }

    //basic bounds checking
    private static boolean in(int r, int c, int R, int C) {
        return 0 <= r && r < R && 0 <= c && c < C;
    }

    // For making IDEs like VsCode happy
    // Essentially the entry point for running directly
    public static void main(String[] args) throws Exception {
        System.out.println(solve(new BufferedReader(new InputStreamReader(System.in))));
    }
}

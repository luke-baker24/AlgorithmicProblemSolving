import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

public class WeakVertices {
    public static void main(String[] args) throws IOException {
        FastIO io = new FastIO();

        while (true) {
            int graphSize = io.nextInt();

            if (graphSize == -1) break;
            
            int[][] adjMatrix = new int[graphSize][graphSize];

            for (int i = 0; i < graphSize; i++) {
                for (int j = 0; j < graphSize; j++) {
                    adjMatrix[i][j] = io.nextInt();
                }
            }

            HashMap<Integer, Boolean> isNodeInTriangle = new HashMap<Integer, Boolean>();
            for (int i = 0; i < graphSize; i++) {
                for (int j = 0; j < i; j++) {
                    for (int k = 0; k < j; k++) {
                        if (isConnected(adjMatrix, i, j) && isConnected(adjMatrix, j, k) && isConnected(adjMatrix, i, k)) {
                            isNodeInTriangle.put(i, true);
                            isNodeInTriangle.put(j, true);
                            isNodeInTriangle.put(k, true);
                        }
                    }
                }
            }

            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < graphSize; i++) {
                if (!isNodeInTriangle.containsKey(i)) sb.append(i + " ");
            }

            io.println(sb.toString());
        }

        io.close();
    }    

    public static boolean isConnected(int[][] adjMatrix, int i, int j) {
        return adjMatrix[i][j] == 1;
    }
}

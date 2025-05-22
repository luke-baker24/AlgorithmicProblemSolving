import java.io.IOException;
import java.rmi.server.ExportException;
import java.util.ArrayList;
import java.util.Scanner;

public class Knapsack {

    public static void main(String[] args) throws IOException {
        FastIO scanner = new FastIO();

        while (true) {
            try {
                int capacity = scanner.nextInt();
                int numObjects = scanner.nextInt();

                ArrayList<Integer> weights = new ArrayList<Integer>();
                ArrayList<Integer> values = new ArrayList<Integer>();

                weights.add(0);
                values.add(0);
                
                for (int i = 0; i < numObjects; i++) {
                    values.add(scanner.nextInt());
                    weights.add(scanner.nextInt());
                }

                int[][] memo = new int[numObjects + 1][capacity + 1];

                for (int i = 0; i < numObjects + 1; i++) {
                    for (int j = 0; j < capacity + 1; j++) {
                        memo[i][j] = -1;
                    }
                }

                //knapsack(memo, weights, values, numObjects, capacity);

                memo[0][capacity] = 0;
                memo[1][0] = 0;

                for (int i = 1 ; i < numObjects + 1; i++) {
                    for (int k = 1; k < capacity + 1; k++) {
                        if (weights.get(i) <= k) memo[i][k] = Math.max(memo[i - 1][k], memo[i - 1][k - weights.get(i)] + values.get(i));
                        else memo[i][k] = memo[i - 1][k];
                    }
                }

                ArrayList<Integer> output = new ArrayList<Integer>();

                backtrack(memo, weights, values, numObjects, capacity, output);

                scanner.println(output.size());

                StringBuilder sb = new StringBuilder();

                for (int i : output) {
                    sb.append(i + " ");
                }

                scanner.println(sb.toString());
            }
            catch(Exception e) {
                break;
            }
        }

        scanner.close();
    }

    public static int knapsack(int[][] memo, ArrayList<Integer> weights, ArrayList<Integer> values, int i, int k) {
        if (i == 0 || k <= 0) {
            memo[i][k] = 0;
            return memo[i][k];
        }
        
        if (memo[i][k] != -1) {
            return memo[i][k];
        }

        if (weights.get(i) <= k) {
            memo[i][k] = Math.max(
                knapsack(memo, weights, values, i - 1, k - weights.get(i)) + values.get(i), 
                knapsack(memo, weights, values, i - 1, k));
        }
        else {
            memo[i][k] = knapsack(memo, weights, values, i - 1, k);
        }

        return memo[i][k];
    }

    public static void backtrack(int[][] memo, ArrayList<Integer> weights, ArrayList<Integer> values, int i, int k, ArrayList<Integer> output) {
        while (i > 0) {
            if (k - weights.get(i) >= 0 && memo[i][k] - memo[i - 1][k - weights.get(i)] == values.get(i)) {
                output.add(i - 1);

                k = k - weights.get(i);
            }

            i--;
        }
    }
}

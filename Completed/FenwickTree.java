import java.io.IOException;

public class FenwickTree {
    public static void main(String[] args) throws IOException {
        FastIO scanner = new FastIO();

        int arrLength = scanner.nextInt();
        int numOps = scanner.nextInt();

        long[] fenwickTree = new long[arrLength];

        for (int i = 0; i < numOps; i++) {
            String operation = scanner.nextWord();
            char op = operation.charAt(0);

            //Increment operation
            if (op == '+')
                update(fenwickTree, scanner.nextInt(), scanner.nextInt());

            //Query operation
            else
                scanner.println("" + sum(fenwickTree, scanner.nextInt()));
        }

        scanner.close();
    }

    static long sum(long[] arr, int index) {
        long sum = 0;

        while (index > 0) {
            sum += arr[index - 1];
            index &= index - 1;
        }

        return sum;
    }

    static void update(long[] arr, int index, long delta) {
        while (index < arr.length) {
            arr[index] += delta;
            index |= index + 1;
        }
    }
}

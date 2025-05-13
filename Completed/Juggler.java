import java.io.IOException;

public class Juggler {
    //Very similar to movie collection.

    public static void main(String[] args) throws IOException {
        FastIO io = new FastIO();

        int totalBalls = io.nextInt();

        long[] fwTree = new long[totalBalls];
        for (int i = 0; i < totalBalls; i++) update(fwTree, i, 1);

        int[] idToIndex = new int[totalBalls];
        for (int i = 0; i < totalBalls; i++) {
            //moves to get from ball to ball is just a subtraction of the sums
            int orderOfBall = io.nextInt();

            idToIndex[orderOfBall - 1] = i;
        }

        boolean[] inPlay = new boolean[totalBalls];
        for (int i = 0; i < totalBalls; i++) inPlay[i] = true;

        long totalMoves = 0;
        int hand = 0;
        for (int i = 0; i < totalBalls; i++) {
            //Clockwise = forward in the array
            int indexToDrop = idToIndex[i];
            
            //Get the number of balls we have to surpass in the Fenwick tree
            long clockwiseDist = Math.abs(sum(fwTree, indexToDrop) - sum(fwTree, hand));
            long counterclockwiseDist = (totalBalls - i) - clockwiseDist;

            //Total moves to get to the ball, and then drop it
            totalMoves +=  Math.min(clockwiseDist, counterclockwiseDist) + 1;

            //Update the Fenwick tree with the dropped ball
            update(fwTree, indexToDrop, -1);
            inPlay[indexToDrop] = false;

            //Bring the next clockwise ball into our hand - this might be too overcomplicated? Just the next one passed fine
            hand = (indexToDrop + 1 >= totalBalls) ? 0 : indexToDrop + 1;
            while (!inPlay[hand] && hand != indexToDrop) hand = (hand + 1 >= totalBalls) ? 0 : hand + 1;
        }

        io.println("" + totalMoves);

        io.close();
    }

    static long sum(long[] arr, int index) {
        long sum = 0;

        while (index > 0) {
            sum += arr[index - 1];
            index &= index - 1;
        }

        return sum;
    }

    static void update(long[] arr, int index, int delta) {
        while (index < arr.length) {
            arr[index] += delta;
            index |= index + 1;
        }
    }
}

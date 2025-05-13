import java.io.IOException;

public class Accounting {
    public static void main(String[] args) throws IOException {
        FastIO io = new FastIO();

        int people = io.nextInt();
        int lines = io.nextInt();

        long[] fwTree = new long[people];

        for (int i = 0; i < lines; i++) {
            String command = io.nextWord();

            //Set command
            if (command.equals("SET")) {
                int index = io.nextInt();
                int value = io.nextInt();

                //edge cas ehere
                if (index == 0) 
                        update(fwTree, index, value - (sum(fwTree, index)));
                    else
                        update(fwTree, index, value - (sum(fwTree, index) - sum(fwTree, index - 1)));
            }

            //The fw tree should look like:
            //value 2value value 4value value 2value value 8value

            //Restart command
            else if (command.equals("RESTART")) {
                int value = io.nextInt();

                for (int j = 0; j < people; j++) {
                    if (j  == 0) 
                        update(fwTree, j, value - (sum(fwTree, j)));
                    else
                        update(fwTree, j, value - (sum(fwTree, j) - sum(fwTree, j - 1)));
                }
            }

            //Print command
            else if (command.equals("PRINT")) {
                int index = io.nextInt();

                if (index > 0)
                    io.println("" + (sum(fwTree, index) - sum(fwTree, index - 1)));
                else
                    io.println("" + sum(fwTree, index));
            }
        }

        io.close();
    }

    static long getLSB(long value) {
        long lsb = 0;

        while (value > 0) {
            lsb++;
            value &= value - 1;
        }

        return lsb;
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

import java.io.IOException;
import java.util.HashMap;

public class MovieCollection {
    public static void main(String[] args) throws IOException {
        //Use a boolean array of the maximum possible length.

        //Determining how many movies are above a certain movie is just a range sum from (i + 1 to m + r - 1).
        //Store the bottom at the front of the array and the top at the back.

        //Use a map from movie identifier to array index (k).

        //Query from sum(k + 1, m + r -1)

        //The top of the stack needs to get tracked separately.

        //When we move a movie to the top, arr[top] = 1, and arr[k] = 0, and top++.

        //The array is basically just a boolean array of the max possible movie stack size.



        //When working through this - set the first however many indices in the stack to 1, based on the input.

        //Set up a reverse map, since the array is in reverse order.

        //The output takes the input from the map, then runs a sum from the index + 1 to the end of the array.

        //The length of the array we need is just the number of movies plus the number of requests.

        FastIO scanner = new FastIO();

        int testCases = scanner.nextInt();

        for (int i = 0; i < testCases; i++) {
            int movies = scanner.nextInt();
            int requests = scanner.nextInt();

            int[] movieStack = new int[movies + requests];
            HashMap<Integer, Integer> idToIndex = new HashMap<Integer, Integer>();

            for (int j = 0; j < movies; j++)  {
                update(movieStack, j, 1);
                idToIndex.put(j + 1, movies - (j + 1));
            }

            int top = movies;
            for (int j = 0; j < requests; j++) {
                int movieToPull = scanner.nextInt();

                int indexToPull = idToIndex.get(movieToPull);

                update(movieStack, indexToPull, -1);
                update(movieStack, top, 1);

                idToIndex.remove(movieToPull);
                idToIndex.put(movieToPull, top);

                scanner.write(sum(movieStack, top) - sum(movieStack, indexToPull) + " ");

                top++;
            }

            scanner.println("");
        }

        scanner.close();
    }

    static long sum(int[] arr, int index) {
        int sum = 0;

        while (index > 0) {
            sum += arr[index - 1];
            index &= index - 1;
        }

        return sum;
    }

    static void update(int[] arr, int index, int delta) {
        while (index < arr.length) {
            arr[index] += delta;
            index |= index + 1;
        }
    }
}

import java.io.IOException;

public class ShebasAmoebas {
    public static void main(String[] args) throws IOException {
        FastIO io = new FastIO();

        int width = io.nextInt();
        int height = io.nextInt();

        boolean[][] petriDish = new boolean[height + 2][width + 2]; //For padding

        for (int i = 0; i < width; i++) {
            String word = io.nextWord();

            for (int j = 0; j < height; j++) {
                petriDish[j + 1][i + 1] = word.charAt(j) == '#' ? true : false;
            }
        }

        //Perform flood-fill on the TRUE characters, accounting for diagonals too.

        //Go through the whole grid. If we find a #, then flood-fill till it's gone.
        int amoebas = 0;
        for (int i = 1; i < width + 2; i++) {
            for (int j = 1; j < height + 2; j++) {
                if (petriDish[j][i] == true) {
                    floodFill(petriDish, j, i);
                    amoebas++;
                }
            }
        }

        io.println(amoebas);
        
        io.close();
    }

    public static void floodFill(boolean[][] arr, int j, int i) {
        if (!arr[j][i]) return;

        arr[j][i] = false;

        int[][] diffs = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };

        for (int[] diff : diffs) {
            floodFill(arr, j + diff[0], i + diff[1]);
        }
    }
}
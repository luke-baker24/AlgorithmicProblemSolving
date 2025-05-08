import java.util.Scanner;

public class Pivot {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int numInputs = scanner.nextInt();

        //Notes:
        //When performing quicksort, the pivot remains in place, while everything else moves around it.
        //Anything less is moved to the left, anything greater to the right.
        int[] numbers = new int[numInputs];

        for (int i = 0; i < numInputs; i++)
            numbers[i] = scanner.nextInt();

        scanner.close();

        int[] maxes = new int[numInputs];
        maxes[0] = numbers[0];
        for (int i = 1; i < numInputs; i++) {
            if (numbers[i] > maxes[i - 1]) maxes[i] = numbers[i];
            else maxes[i] = maxes[i - 1];
        }
        
        int[] mins = new int[numInputs];
        mins[numInputs - 1] = numbers[numInputs - 1];
        for (int i = numInputs - 2; i >= 0; i--) {
            if (numbers[i] < mins[i + 1]) mins[i] = numbers[i];
            else mins[i] = mins[i + 1];
        }
        
        int pivots = 0;
        for (int i = 0; i < numInputs; i++)
            if (mins[i] == maxes[i]) pivots++;

        System.out.println(pivots);
    }
}

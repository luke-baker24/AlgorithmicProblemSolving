import java.util.Scanner;

public class SemiPrimeHNumbers {
    public static void main(String[] args) {
        //The product of any h-number is also an h-number.

        //Hash-set or array to keep track. Use a boolean array.

        int MAX_H = 1_000_001;

        boolean[] h_comp = new boolean[MAX_H + 1];
        boolean[] h_semiprime = new boolean[MAX_H + 1];

        for (int i = 5; i < MAX_H / 5 + 1; i+=4) {
            for (int j = 5; j <= i; j+=4) {
                int product = i * j;

                if (product > MAX_H) break;

                if (!h_comp[i] && !h_comp[j]) h_semiprime[product] = true;

                h_comp[product] = true;
            }
        }
        
        int[] h_semi_pref = new int[MAX_H + 1];
        h_semi_pref[0] = 0;

        for (int i = 1; i < MAX_H + 1; i++) {
            if (h_semiprime[i]) h_semi_pref[i] = h_semi_pref[i - 1] + 1;
            else h_semi_pref[i] = h_semi_pref[i - 1];
        }

        Scanner scanner = new Scanner(System.in);

        while (true) {
            int newVal = scanner.nextInt();

            if (newVal == 0) break;

            System.out.println(newVal + " " + h_semi_pref[newVal]);
        }
        
        //MAX_H = 1 000 001
        //Generate h-primes by looping from 5 to MAX_H / 5 + 1, called i
            //Use a second loop, going from 5 to the outer factor, called j
                //prod = i * j
                //If it's larger than MAX_H, break

                //Prod is now an h-composite.

                //This is an h-semi-prime iff i and j are both not h-composites.
        
        //Use a prefix table of H-semi-prime-counts, and then each query is O(1).

        scanner.close();
    }
}

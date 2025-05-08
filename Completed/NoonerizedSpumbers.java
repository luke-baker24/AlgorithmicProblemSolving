import java.util.Scanner;

public class NoonerizedSpumbers {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String line = scanner.nextLine();

        scanner.close();

        String str1 = line.split(" ")[0];
        String str2 = line.split(" ")[2];
        String stresult = line.split(" ")[4];

        char operation = line.split(" ")[1].toCharArray()[0];

        boolean multiplying = false;
        if (operation == '*') multiplying = true;

        //this seems like a backtracking problem - just brute-force it.
        //3^31 = 2147483648.. so prefixes of length 10-ish or shorter. so only 1000 possible combinations? 
        //yeah let's brute-force this 

        //Triple-for loop. We assume the first prefix for the first, then the first prefix for the second, etc.
        //In the inside of the for loop, we try all 6 possible swaps.
        for (int i = 0; i < str1.length(); i++) {
            //do something
            String prefix1 = str1.substring(0, i);
            String restOf1 = str1.substring(i);

            for (int j = 0; j < str2.length(); j++) {
                //do something
                String prefix2 = str2.substring(0, j);
                String restOf2 = str2.substring(j);

                for (int k = 0; k < stresult.length(); k++) {
                    //do something
                    String prefix3 = stresult.substring(0, k);
                    String result3 = stresult.substring(k);

                    //comparisons
                    if (multiplying) {
                        //this is the case where we don't have to swap anything
                        if      (Long.parseLong(prefix1 + restOf1) * Long.parseLong(prefix2 + restOf2) == Long.parseLong(prefix3 + result3)) {
                            System.out.println(prefix1 + restOf1 + " * " + prefix2 + restOf2 + " = " + prefix3 + result3); return; }
                        
                        else if (Long.parseLong(prefix1 + restOf1) * Long.parseLong(prefix3 + restOf2) == Long.parseLong(prefix2 + result3)) {
                            System.out.println(prefix1 + restOf1 + " * " + prefix3 + restOf2 + " = " + prefix2 + result3); return; }

                        else if (Long.parseLong(prefix2 + restOf1) * Long.parseLong(prefix1 + restOf2) == Long.parseLong(prefix3 + result3)) {
                            System.out.println(prefix2 + restOf1 + " * " + prefix1 + restOf2 + " = " + prefix3 + result3); return; }
                        
                        else if (Long.parseLong(prefix2 + restOf1) * Long.parseLong(prefix3 + restOf2) == Long.parseLong(prefix1 + result3)) {
                            System.out.println(prefix2 + restOf1 + " * " + prefix3 + restOf2 + " = " + prefix1 + result3); return; }
                        
                        else if (Long.parseLong(prefix3 + restOf1) * Long.parseLong(prefix1 + restOf2) == Long.parseLong(prefix2 + result3)) {
                            System.out.println(prefix3 + restOf1 + " * " + prefix1 + restOf2 + " = " + prefix2 + result3); return; }
                        
                        else if (Long.parseLong(prefix3 + restOf1) * Long.parseLong(prefix2 + restOf2) == Long.parseLong(prefix1 + result3)) {
                            System.out.println(prefix3 + restOf1 + " * " + prefix2 + restOf2 + " = " + prefix1 + result3); return; }
                    }
                    else {
                        if      (Long.parseLong(prefix1 + restOf1) + Long.parseLong(prefix2 + restOf2) == Long.parseLong(prefix3 + result3)) {
                            System.out.println(prefix1 + restOf1 + " + " + prefix2 + restOf2 + " = " + prefix3 + result3); return; }
                        
                        else if (Long.parseLong(prefix1 + restOf1) + Long.parseLong(prefix3 + restOf2) == Long.parseLong(prefix2 + result3)) {
                            System.out.println(prefix1 + restOf1 + " + " + prefix3 + restOf2 + " = " + prefix2 + result3); return; }

                        else if (Long.parseLong(prefix2 + restOf1) + Long.parseLong(prefix1 + restOf2) == Long.parseLong(prefix3 + result3)) {
                            System.out.println(prefix2 + restOf1 + " + " + prefix1 + restOf2 + " = " + prefix3 + result3); return; }
                        
                        else if (Long.parseLong(prefix2 + restOf1) + Long.parseLong(prefix3 + restOf2) == Long.parseLong(prefix1 + result3)) {
                            System.out.println(prefix2 + restOf1 + " + " + prefix3 + restOf2 + " = " + prefix1 + result3); return; }
                        
                        else if (Long.parseLong(prefix3 + restOf1) + Long.parseLong(prefix1 + restOf2) == Long.parseLong(prefix2 + result3)) {
                            System.out.println(prefix3 + restOf1 + " + " + prefix1 + restOf2 + " = " + prefix2 + result3); return; }
                        
                        else if (Long.parseLong(prefix3 + restOf1) + Long.parseLong(prefix2 + restOf2) == Long.parseLong(prefix1 + result3)) {
                            System.out.println(prefix3 + restOf1 + " + " + prefix2 + restOf2 + " = " + prefix1 + result3); return; }
                    }
                }
            }
        }
    }
}

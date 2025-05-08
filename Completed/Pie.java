import java.io.IOException;

public class Pie {
    public static void main(String[] args) throws IOException {
        FastIO scanner = new FastIO();

        int testCases = scanner.nextInt();

        //Solution is going to be to iterate through all of the pies. For each pie, try to cut a certain slice size out.
        //If we can't, go to the next pie. If we can, remove it, and keep trying to cut slices.
        //If the number of slices we can cut is greater than the number of people eating, then increase the volume.
        //If it's less than the number of people eating, then decrease the volume.
        //If it is equal, there is probably still more optimization to be done, and we keep trying to approach the value
        //where there isn't enough pie left until we settle on a value with 10^(-3) accuracy.

        for (int i = 0; i < testCases; i++) {
            int pies = scanner.nextInt();
            int friends = scanner.nextInt() + 1;

            double totalVolume = 0.0;
            double[] pieVolumes = new double[pies];

            for (int j = 0; j < pies; j++) {
                int radius = scanner.nextInt();

                double thisPieVolume = radius * radius * Math.PI;

                totalVolume += thisPieVolume;
                pieVolumes[j] = thisPieVolume;
            }
            
            double min = 0.0;
            double max = totalVolume / (double)friends;
            double guess = (max + min) / 2.0;

            while (true) {
                int friendsServed = 0;
                for (int j = 0; j < pies; j++)
                    friendsServed += (int)(pieVolumes[j] / guess);
                
                if (Math.abs(max - min) < 0.0001) 
                    break;
                
                if (friendsServed < friends)
                    max = guess;
                else
                    min = guess;

                guess = (max + min) / 2.0;
            }

            System.out.printf("%.4f\n", guess);
        }

        scanner.close();
    }
}

import java.io.IOException;
import java.util.Scanner;

public class CurseTheDarkness {
    public static void main(String[] args) {
        FastIO in = new FastIO();

        int testCases = in.nextInt();

        for (int i = 0; i < testCases; i++) {
            double bookX = in.nextDouble();
            double bookY = in.nextDouble();

            int candles = in.nextInt();

            boolean bookLit = false;
            for (int j = 0; j < candles; j++) {
                double candleX = in.nextDouble();
                double candleY = in.nextDouble();

                if (bookLit) continue;

                if (DistanceSquared(candleX, candleY, bookX, bookY) < 64d) {
                    System.out.println("light a candle");
                    bookLit = true;
                }
            }

            if (!bookLit) System.out.println("curse the darkness");
        }

        in.close();
    }

    public static double DistanceSquared(double x1, double y1, double x2, double y2) {
        return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    }
}
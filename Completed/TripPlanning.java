import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

public class TripPlanning {
    public static void main(String[] args) throws IOException {
        FastIO io = new FastIO();

        int numCities = io.nextInt();
        int numTrains = io.nextInt();

        HashMap<Integer, ArrayList<TrainLine>> graph = new HashMap<Integer, ArrayList<TrainLine>>();
        
        for (int i = 0; i < numTrains; i++) {
            int from = io.nextInt();
            int to = io.nextInt();

            if (!graph.containsKey(from)) graph.put(from, new ArrayList<TrainLine>());
            if (!graph.containsKey(to)) graph.put(to, new ArrayList<TrainLine>());

            graph.get(from).add(new TrainLine(to, i + 1));
            graph.get(to).add(new TrainLine(from, i + 1));
        }

        ArrayList<TrainLine> path = new ArrayList<TrainLine>();

        int currentCity = 1;
        while (true) {
            if (currentCity == 1 && path.size() == numCities) break;

            ArrayList<TrainLine> possibleTrains = graph.get(currentCity);

            if (possibleTrains == null) break;

            int desiredDestination;

            if (currentCity == numCities) desiredDestination = 1;
            else desiredDestination = currentCity + 1;

            boolean foundRoute = false;
            for (TrainLine line : possibleTrains) {
                if (line.destination == desiredDestination) {
                    path.add(line);

                    currentCity = line.destination;
                    foundRoute = true;

                    break;
                }
            }

            if (!foundRoute) break;
        }

        //System.out.println(path.size());

        if (path.size() == numCities)
            for (TrainLine city : path)
                io.println(city.number);
        else
            io.println("impossible");

        io.close();
    }    

    public static class TrainLine {
        public int destination;
        public int number;

        public TrainLine(int destination, int number) {
            this.destination = destination;
            this.number = number;
        }
    }
}

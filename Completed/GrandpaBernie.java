import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.io.IOException;

public class GrandpaBernie {
	public static void main(String[] args) throws IOException {
		FastIO reader = new FastIO();
		
		HashMap<String, ArrayList<Integer>> locations = new HashMap<String, ArrayList<Integer>>();
		
		int trips = reader.nextInt();
		for (int trip = 0; trip < trips; trip++) {
			String location = reader.nextWord();
			Integer year = reader.nextInt();
			
			if (!locations.containsKey(location))
				locations.put(location, new ArrayList<Integer>());
			
			locations.get(location).add(year);
		}

		for (String key : locations.keySet())
			Collections.sort(locations.get(key));
		
		int recalls = reader.nextInt();
		for (int recall = 0; recall < recalls; recall++) {
			String location = reader.nextWord();
			int visit = reader.nextInt() - 1;
			
			reader.println(locations.get(location).get(visit));
		}
		
		reader.close();
	}
}

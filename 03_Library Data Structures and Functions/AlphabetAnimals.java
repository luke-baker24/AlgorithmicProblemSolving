import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

public class AlphabetAnimals {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		
		String targAnimal = scanner.nextLine();
		
		int numAnimals = scanner.nextInt();
		scanner.nextLine();
		
		ArrayList<String> animals = new ArrayList<String>();
		
		for (int i = 0; i < numAnimals; i++)
			animals.add(scanner.nextLine());
		
		scanner.close();

		ArrayList<String> validPlays = new ArrayList<String>();

		for (String animal : animals)
			if (animal.toCharArray()[0] == targAnimal.charAt(targAnimal.length() - 1))
				validPlays.add(animal);

		HashMap<Character, Integer> startingChars = new HashMap<Character, Integer>();

		for (String animal : animals) {
			if (!startingChars.containsKey(animal.toCharArray()[0]))
				startingChars.put(animal.toCharArray()[0], 1);
			else
				startingChars.put(animal.toCharArray()[0], startingChars.get(animal.toCharArray()[0]) + 1);
		}

		Set<Character> allChars = new TreeSet<Character>();
		
		for (int i = 'a'; i < 'z'; i++)
			allChars.add((char)i);

		for (String animal : validPlays) {
			Set<Character> eliminationChars = new TreeSet<Character>(allChars);

			eliminationChars.removeAll(startingChars.keySet());
			
			Character lastAnimalChar = animal.charAt(animal.length() - 1);

			Character firstAnimalChar = animal.charAt(0);

			if (startingChars.get(firstAnimalChar) == 1) eliminationChars.add(firstAnimalChar);

			if (eliminationChars.contains(lastAnimalChar)) {
				System.out.println(animal + "!");
				return;
			}
		}

		for (String animal : validPlays) {
			System.out.println(animal);
			return;
		}

		System.out.println("?");
		return;









		
		// //Find an animal that will guarantee eliminate the next player - it ends in a letter that no remaining animal
		// //starts with, AFTER removing the animal that will be said.
		
		// //Second case, output any valid animal that starts with the correct letter.
		
		// //Third case, output ?, because we have no valid solutions.
		
		// ArrayList<String> validAnimals = new ArrayList<String>();
		// ArrayList<String> invalidAnimals = new ArrayList<String>();
		
		// for (int i = 0; i < numAnimals; i++) {
		// 	String animal = animals.get(i);
			
		// 	if (animal.toCharArray()[-1] == targAnimal.toCharArray()[0]) {
		// 		validAnimals.add(animal);
		// 	}
		// 	else {
		// 		invalidAnimals.add(animal);
		// 	}
		// }
		
		// //Well shoot, there aren't any valid animals, we're done here
		// if (validAnimals.isEmpty()) {
		// 	System.out.println("?");
			
		// 	return;
		// }
		
		// //Now realizing this solution is hilariously inefficient. Whatever, if this comment is still here it's fast enough
		// for (int i = 0; i < validAnimals.size(); i++) {
		// 	//Pop a valid animal off the queue
		// 	String validAnimal = animals.remove();
			
		// 	//We need to find all characters that other animals don't end in.
		// 	char finalChar = validAnimal.toCharArray()[-1];
			
		// 	//mwahaha.. we eliminate the next player if this works
		// 	Set<Character> mwahahaChars = new HashSet<Character>();
		// 	for (int j = 0; j < animals.size(); j++) {
		// 		String ugh = animals.remove();
				
		// 		mwahahaChars.add(ugh.toCharArray()[-1]);
				
		// 		animals.add(ugh);
		// 	}
			
		// 	if (validAnimal.toCharArray()[-1] == targAnimal.toCharArray()[0]) {
				
		// 	}
		// }
	}
}

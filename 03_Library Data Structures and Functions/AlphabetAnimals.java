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
	}
}

import java.util.Collections;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;
import java.util.Stack;

public class GuessTheDataStructure {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		
		while (scanner.hasNext()) {
			int amountOfLines = scanner.nextInt();
			
			Stack<Integer> testStack = new Stack<Integer>();
			Queue<Integer> testQueue = new LinkedList<Integer>();
			PriorityQueue<Integer> testPqueue = new PriorityQueue<Integer>(Collections.reverseOrder());
			
			boolean stackPossible = true;
			boolean queuePossible = true;
			boolean pQueuePossible = true;
			
			int elsAdded = 0;
			
			for (int i = 0; i < amountOfLines; i++) {
				int commandType = scanner.nextInt();
				int value = scanner.nextInt();

				if (!stackPossible && !queuePossible && !pQueuePossible) continue;
				
				//Issuing an add command
				if (commandType == 1) {
					if (stackPossible) testStack.push(value);
					if (queuePossible) testQueue.add(value);
					if (pQueuePossible) testPqueue.add(value);
					
					elsAdded++;
				}

				//Issuing a check-remove command
				else {
					if (elsAdded <= 0) {
						stackPossible = false;
						queuePossible = false;
						pQueuePossible = false;

						continue;
					}
					
					if (stackPossible && testStack.pop() != value) stackPossible = false;
					if (queuePossible && testQueue.remove() != value) queuePossible = false;
					if (pQueuePossible && testPqueue.remove() != value) pQueuePossible = false;
					
					elsAdded--;
				}
			}
			
			if (stackPossible && !queuePossible && !pQueuePossible) System.out.println("stack");
			else if (!stackPossible && queuePossible && !pQueuePossible) System.out.println("queue");
			else if (!stackPossible && !queuePossible && pQueuePossible) System.out.println("priority queue");
			else if (!stackPossible && !queuePossible && !pQueuePossible) System.out.println("impossible");
			else System.out.println("not sure");
		}
		
		scanner.close();
	}
}

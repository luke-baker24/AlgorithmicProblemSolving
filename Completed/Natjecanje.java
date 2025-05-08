import java.util.Scanner;

public class Natjecanje {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int numTeams = scanner.nextInt();
        int numDamagedTeams = scanner.nextInt();
        int numReserveTeams = scanner.nextInt();

        scanner.nextLine();

        int[] damagedTeams = new int[numDamagedTeams];

        for (int i = 0; i < numDamagedTeams; i++)
            damagedTeams[i] = scanner.nextInt() - 1;
        
        scanner.nextLine();

        int[] reserveTeams = new int[numReserveTeams];

        for (int i = 0; i < numReserveTeams; i++) 
            reserveTeams[i] = scanner.nextInt() - 1;
        
        scanner.nextLine();

        scanner.close();

        //This is probably the divide-and-conquer problem.

        //Go through the teams list and iterate. Add up the number of POTENTIAL "kayak loans." If both teams left and right have reserve, we have 2.
        //If only one team has one, get one. 
        //If neither teams left and right have one, then this team definitely can't start.

        //Then, pass through the list again and 

        short[] teams = new short[numTeams];

        for (int j = 0; j < numReserveTeams; j++)
            teams[reserveTeams[j]]++;

        for (int j = 0; j < numDamagedTeams; j++)
            teams[damagedTeams[j]]--;

        //Now we have an array of teams, where 1 indicates an extra kayak and -1 is a missing one. 

        //Naive solution?
        for (int i = 0; i < numDamagedTeams; i++) {
            int j = damagedTeams[i];

            if (teams[j] == 0) continue;

            //Array edge cases
            if (j == 0) {
                if (teams[j + 1] == 1) stealCanoe(teams, j + 1, j);
            }
            else if (j == numTeams - 1) {
                if (teams[j - 1] == 1) stealCanoe(teams, j - 1, j);
            }

            //And otherwise
            else {
                if (teams[j + 1] == 1 && teams[j - 1] != 1) stealCanoe(teams, j + 1, j);
                else if (teams[j - 1] == 1 && teams[j + 1] != 1) stealCanoe(teams, j - 1, j);
                else if (teams[j + 1] == 1 && teams[j - 1] == 1) stealCanoe(teams, j - 1, j);
            }
        }

        int unresolvedTeams = 0;

        for (int i = 0; i < numDamagedTeams; i++)
            if (teams[damagedTeams[i]] <= -1) unresolvedTeams++;
        
        System.out.println(unresolvedTeams);
    }

    static void stealCanoe(short[] arr, int fromIndex, int toIndex) {
        arr[fromIndex]--;
        arr[toIndex]++;
    }
}

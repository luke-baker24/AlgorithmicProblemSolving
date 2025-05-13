import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;
import java.time.LocalDateTime;

public class Booking {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		
		int inputs = scanner.nextInt();
		scanner.nextLine();
		
		for (int i = 0; i < inputs; i++) {
			int thisSetInputs = scanner.nextInt();
			int thisSetTimeToClean = scanner.nextInt();
			scanner.nextLine();
			
			ArrayList<LocalDateWrapper> reservationTracker = new ArrayList<LocalDateWrapper>(thisSetInputs * 2);

			for (int j = 0; j < thisSetInputs; j++) {
				String thisReservation = scanner.nextLine();

				String[] firstDate = thisReservation.split(" ")[1].split("-");
				String[] firstTime = thisReservation.split(" ")[2].split(":");
				
				int startYear = Integer.parseInt(firstDate[0]);
				int startMonth = Integer.parseInt(firstDate[1]);
				int startDay = Integer.parseInt(firstDate[2]);
				
				int startHour = Integer.parseInt(firstTime[0]);
				int startMinute = Integer.parseInt(firstTime[1]);
				
				LocalDateTime startDate = LocalDateTime.of(startYear, startMonth, startDay, startHour, startMinute);

				String[] secondDate = thisReservation.split(" ")[3].split("-");
				String[] secondTime = thisReservation.split(" ")[4].split(":");
				
				int endYear = Integer.parseInt(secondDate[0]);
				int endMonth = Integer.parseInt(secondDate[1]);
				int endDay = Integer.parseInt(secondDate[2]);
				
				int endHour = Integer.parseInt(secondTime[0]);
				int endMinute = Integer.parseInt(secondTime[1]);
				
				LocalDateTime endDate = LocalDateTime.of(endYear, endMonth, endDay, endHour, endMinute);
				
				reservationTracker.add(new LocalDateWrapper(true, startDate));
				reservationTracker.add(new LocalDateWrapper(false, endDate.plusMinutes(thisSetTimeToClean)));
			}

			Collections.sort(reservationTracker);

			//Make a hashmap with a key of the room id. If the key doesn't exist yet, we found the start date. 
			//Enter the start index. Otherwise, enter the end index.
			int currentActiveReservations = 0;
			int maxRoomsNeeded = 0;

			for (int j = 0; j < thisSetInputs * 2; j++) {
				LocalDateWrapper date = reservationTracker.get(j);

				//If this date is the start of a range
				if (date.start)
					currentActiveReservations++;
				else
					currentActiveReservations--;

				if (currentActiveReservations > maxRoomsNeeded) maxRoomsNeeded = currentActiveReservations;
			}

			System.out.println(maxRoomsNeeded);
		}
		
		scanner.close();
	}

	static class LocalDateWrapper implements Comparable<LocalDateWrapper> {
		public boolean start;
		public LocalDateTime date;

		public LocalDateWrapper(boolean start, LocalDateTime date) {
			this.start = start;
			this.date = date;
		}

		@Override
		public int compareTo(LocalDateWrapper toCompare) {
			if (!toCompare.date.isEqual(this.date)) return this.date.compareTo(toCompare.date);
			else {
				if (this.start) return 0;
				else return -1;
			}
		}

		@Override
		public String toString() {
			return start + date.toString();
		}
	}
}
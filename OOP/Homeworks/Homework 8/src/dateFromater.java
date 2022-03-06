
import java.util.Scanner;

public class dateFromater {
	
	static int month = -1;
	static int day = -1;
	static int year = -1;
	static boolean input = false;

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		
		System.out.print("Enter date (mm/dd/yyyy): ");
		String[] date = scanner.next().split("/");
		
		while(month == -1) {
			try {
				if(input) {
					System.out.print("Enter a month (range: 1 - 12): ");
					date[0] = scanner.nextLine();
				}
				
				if(!isMonth(date[0])) {
					throw new MonthException("Not a valid month.");
				}
				month = Integer.parseInt(date[0]);

			}
			catch(MonthException monthException) {
				System.out.println(monthException);
				System.out.println();
				input = true;
				
			}
		}
		
		input = false;
		while(day == -1) {
			try {
				if(input) {
					System.out.print("Enter a day: ");
					date[1] = scanner.nextLine();
				}
				
				if(!isDay(date[1])) {
					throw new DayException("Not a valid day in month: " + month);
				}
				day = Integer.parseInt(date[1]);
			}
			catch(DayException dayException) {
				System.out.println(dayException);
				System.out.println();
				input = true;
			}
			
			
		}
		
		input = false;
		while(year == -1) {
			try {
				if(input) {
					System.out.print("Enter a year: ");
					date[2] = scanner.nextLine();
				}
				
				if(!isYear(date[2])) {
					throw new YearException("Year not in range between 1000 and 3000");
				}
				year = Integer.parseInt(date[2]);
			}
			catch(YearException yearException) {
				System.out.println(yearException);
				System.out.println();
				input = true;
			}
			
		}
		
		System.out.println(monthify(month) + " " + day + ", " + year);
	}
	
	static boolean isMonth(String input) {
		if(!isNumeric(input)) {
			return false;
		}
		
		if(1 <= Integer.parseInt(input) && Integer.parseInt(input) <= 12) {
			return true;
		}
		return false;		
	}
	
	static boolean isDay(String input) {
		
		if(!isNumeric(input)) {
			return false;
		}
		
		switch(month) {
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if(1 <= Integer.parseInt(input) && Integer.parseInt(input) <= 31) {
					return true;
				}
				return false;
			case 4:
			case 6:
			case 9:
			case 11:
				if(1 <= Integer.parseInt(input) && Integer.parseInt(input) <= 30) {
					return true;
				}
				return false;
			case 2:
				if(1 <= Integer.parseInt(input) && Integer.parseInt(input) <= 28) {
					return true;
				}
				return false;
		}
		return false;
	}
	
	static boolean isYear(String input) {
		if(!isNumeric(input)) {
			return false;
		}
		
		if(1000 <= Integer.parseInt(input) && Integer.parseInt(input) <= 3000) {
			return true;
		}
		return false;		
	}
	
	static boolean isNumeric(String str) {
		try {
			Double.parseDouble(str);
			return true;
		} catch(NumberFormatException e){
			return false;  
		} 
	}
	
	static String monthify(int intMonth) {
		switch(intMonth) {
			case 1:
				return "January";
			case 2:
				return "February";
			case 3:
				return "March";
			case 4:
				return "April";
			case 5:
				return "May";
			case 6:
				return "June";
			case 7:
				return "July";
			case 8:
				return "August";
			case 9:
				return "September";
			case 10:
				return "October";
			case 11:
				return "Novemeber";
			case 12:
				return "December";
		}
		return null;
	}
}

class MonthException extends RuntimeException {
	
	public MonthException(String errorMessage) {
		super(errorMessage);
	}
	
}

class DayException extends RuntimeException {
	
	public DayException(String errorMessage) {
		super(errorMessage);
	}
}

class YearException extends RuntimeException {
	
	public YearException(String errorMessage) {
		super(errorMessage);
	}
	
}
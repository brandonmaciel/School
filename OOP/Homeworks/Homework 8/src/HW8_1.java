
import java.util.Scanner;

public class HW8_1 extends Exception{
	
	static int N; // number of positive integers

	public static void main(String[] args) {
		promptUserN();
		promptUserNIntegers();
	}
	
	static int promptUserN() {
		Scanner scanner = new Scanner(System.in);
		
		while(true) {
			try {
				System.out.print("Enter the N, the amount of positive integers: ");
				N = scanner.nextInt();
				
				if(N < 0) {
					throw new Exception("N must be positive");
				}
				System.out.println();
				return N;
			}
			catch(Exception e) {
				System.out.println(e);
				System.out.println();
			}
			
		}
		
	}
	
	static void promptUserNIntegers() {
		Scanner scanner = new Scanner(System.in);
		int tmp = 1;
		
		while(N-- > 0) {
			
			while(true) {
				try {
					System.out.print("Enter a positive integer (N = " + tmp + "): ");
					
					if(!(scanner.hasNextInt())) {
						scanner.nextLine();
						throw new Exception("Enter a positive integer.");
					}
					else {
						if(scanner.nextInt() < 0) {
							throw new Exception("Enter a positive integers.");
						}
						else {
							System.out.println();
							tmp++;
							break;
							
						}
					}
				}
				catch(Exception e) {
					System.out.println(e);
					System.out.println();
				}
				
			}
		}
	}
}

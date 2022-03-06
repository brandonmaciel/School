import java.util.Scanner;

public class TestEmployee {

	public static void main(String[] args) {
		
		Scanner keyboard = new Scanner(System.in);
		
		String tmpName;
		int tmpID;
		String tmpPosition;
		
//		first employee
		System.out.print("Employee 1 name: ");
		tmpName = keyboard.nextLine();
		
		System.out.print("Employee 1 ID: ");
		tmpID = keyboard.nextInt();
		keyboard.nextLine();
		
		System.out.print("Employee 1 position: ");
		tmpPosition = keyboard.nextLine();
		
		Employee emp1 = new Employee(tmpName, tmpID, tmpPosition);
		
//		second employee
		System.out.print("\nEmployee 2 name: ");
		tmpName = keyboard.nextLine();
		
		System.out.print("Employee 2 ID: ");
		tmpID = keyboard.nextInt();
		keyboard.nextLine();
		
		System.out.print("Employee 2 position: ");
		tmpPosition = keyboard.nextLine();
		
		Employee emp2 = new Employee(tmpName, tmpID, tmpPosition);
		
//		third employee
		System.out.print("\nEmployee 3 name: ");
		tmpName = keyboard.nextLine();
		
		System.out.print("Employee 3 ID: ");
		tmpID = keyboard.nextInt();
		keyboard.nextLine();
		
		System.out.print("Employee 3 position: ");
		tmpPosition = keyboard.nextLine();
		
		Employee emp3 = new Employee(tmpName, tmpID, tmpPosition);
		
		
//		display employees
		emp1.display();
		emp2.display();
		emp3.display();
		
		keyboard.close();

	}

}

class Employee{
	private String name;
	private int ID;
	private String position;
	
	public Employee(String name, int ID, String position) {
		this.name = name;
		this.ID = ID;
		this.position = position;
	}
	
	public void display() {
		System.out.println("\nEmployee: " + name);
		System.out.printf("ID: %d\n", ID);
		System.out.println("Position: " + position);
	}
	
}

import java.util.Scanner;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class ViewExamGrages {

	public static void main(String[] args) {
		
		File file = new File("/Users/brandonmaciel/Eclipse/OOP Homework/Homework5/src/students.txt");
		
		
		
		try {
			Scanner keyboard = new Scanner(file);
			
			while (keyboard.hasNextLine()) {
                String line = keyboard.nextLine();
                System.out.println(line);
            }
			keyboard.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
//		System.out.print(file);
		

	}

}

class StudentInterface {
	
	String userID;
	String pwrd;
	
	void displayLogin() {
		Scanner keyboard = new Scanner(System.in);
		
		System.out.print("User ID: ");
		userID = keyboard.nextLine();
		
		System.out.print("password: ");
		pwrd = keyboard.nextLine();
		
//		checkStudent(userID, pwrd);
		
		
	}
//	
//	void sectionSelection();
//	
//	void displayGrade(double grade);
}

class account extends StudentInterface{
	
	int students;
	
	int checkStudent(String id, String pwd) {

		return 0;
	}
	
	void parse() {

	}
	
	
}

class grade {
	
}








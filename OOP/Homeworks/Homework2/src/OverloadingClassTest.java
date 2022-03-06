// Problem 1

public class OverloadingClassTest {

	public static void main(String[] args) {
		OverloadingClass test = new OverloadingClass();
		
		test.overloadMethod(1.0);
		test.overloadMethod(5, 8, 7);
		test.overloadMethod(5, 2);
		test.overloadMethod("Anna", 29);
		

	}

}

class OverloadingClass{
	void overloadMethod(double a) {
		System.out.println(a);
	}
	
	void overloadMethod(int a, int b, int c) {
		System.out.println("a, b, and c: " + a + ", " + b + ", " + c);
	}
	
	void overloadMethod(int a, int b) {
		System.out.println("The sum of the number is: " + a + "+" + b + "=" + (a + b));
	}
	
	void overloadMethod(String name, int age) {
		System.out.println(name  + " is " + age + " years old.");
	}
}
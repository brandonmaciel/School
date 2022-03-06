import java.util.Scanner;

public class TestRectangle {

	public static void main(String[] args) {
		
		Scanner keyboard = new Scanner(System.in);
		
		Rectangle rect = new Rectangle();
		boolean test;
		
//		length
		while(true) {			
			System.out.print("Enter rectangle length: ");
			test = rect.setLength(keyboard.nextDouble());
			
			if(test) {
				break;
			}
			System.out.println("Please input a value between 1 and 49.\n");
		}
		
//		width
		while(true) {			
			System.out.print("Enter rectangle width: ");
			test = rect.setWidth(keyboard.nextDouble());
			
			if(test) {
				break;
			}
			System.out.println("Please input a value between 1 and 49.\n");
		}
		
		rect.getArea();
		rect.getPerimeter();
		
		keyboard.close();
	}

}

class Rectangle{
	private double length;
	private double width;
	
	public boolean setLength(double length) {
		if((0 < length) && (length < 50)) {
			this.length = length;
			return true;
		}
		return false;

	}
	
	public boolean setWidth(double width) {
		if((0 < width) && (width < 50)) {
			this.width = width;
			return true;
		}
		else {
			return false;
		}
	}
	
	public double getArea() {
		System.out.printf("\nLength: %.2f \n", length);
		System.out.printf("Width: %.2f \n", width);
		System.out.println("The area of the rectangle is " + (length*width));
		return length * width;
	}
	
	public double getPerimeter() {
		System.out.printf("\nLength: %.2f \n", length);
		System.out.printf("Width: %.2f \n", width);
		System.out.println("The perimeter of the rectangle is " + ((2 * length) + (2 * width)));
		return (2 * length) + (2 * width);
	}
	
}


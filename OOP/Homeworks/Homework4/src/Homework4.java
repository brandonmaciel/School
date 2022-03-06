
public class Homework4 {

	public static void main(String[] args) {
		CarbonFootprint building = new Building();
		CarbonFootprint car = new Car();
		CarbonFootprint bicycle = new Bicycle();
		
		building.getCarbonFoorprint();
		car.getCarbonFoorprint();
		bicycle.getCarbonFoorprint();

	}

}

interface CarbonFootprint {
	public void getCarbonFoorprint();
}



class Building implements CarbonFootprint{
	
	public void getCarbonFoorprint() {
		System.out.println("This message is from Building CarbonFoot.");
	}

}

class Car implements CarbonFootprint {
	
	public void getCarbonFoorprint() {
		System.out.println("This message is from Car CarbonFoot.");
	}

}

class Bicycle implements CarbonFootprint {
	
	public void getCarbonFoorprint() {
		System.out.println("This message is from Bicycle CarbonFoot.");
	}

}



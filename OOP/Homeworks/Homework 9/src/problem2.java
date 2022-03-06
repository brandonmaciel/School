
public class problem2 <T extends Number>{
	
	T[] arr;
	
	problem2(T[] arr) {
		this.arr = arr;
	}
	
	double getAverage() {
		double tmp = 0;
		
		for(T val: arr) {
			tmp += val.doubleValue();
		}
		
		return tmp/arr.length;
	}

	public static void main(String[] args) {
		
		Double[] testDouble = {1.0, 2.0, 4.0, 8.0, 16.0};
		problem2<Double> avgDouble = new problem2<Double>(testDouble);
		System.out.println("Double average: " + avgDouble.getAverage());

		Integer[] testInteger = {2, 4, 8, 16, 32};
		problem2<Integer> avgInteger = new problem2<Integer>(testInteger);
		System.out.println("Integer average: " + avgInteger.getAverage());

	}

}

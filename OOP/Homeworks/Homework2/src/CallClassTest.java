// Problem 2

public class CallClassTest {

	public static void main(String[] args) {
		int a = 4;
		CallClass test = new CallClass(a);
		
		// Call by value		
		System.out.println("\'a\' before call by value: " + a);
		test.callByValue(a);
		System.out.println("\'a\' after call by value: " + a + " (unchanged)\n");
		
		
		// Call by reference
		System.out.println("\'test.a\' before call by reference: " + test.a);
		test.callByReference(test);
		System.out.println("\'test.a\' after call by reference: " + test.a + " (changed)");
	}

}

class CallClass{
	int a;
	
	CallClass(int a){
		this.a = a;
	}
	
	void callByValue(int a) {
		a = a * 5;
	}
	
	void callByReference(CallClass ref) {
		a = ref.a * 5;
	}
}



public class SimpleCalculation {
	
	static int math(String operation, int num) {
		
		if(operation.equals("add")) {
			return 10 + num;
		}
		else if(operation.equals("multiply")) {
			return 10 * num;
		}
		
		return num;
	}
}

class MessageBufferResponse {
	int n;
	boolean valueSet = false;
	String operation;
	int num;
	
	
	synchronized void send(String operation, int num) {
		this.operation = operation;
		this.num = num;
		
		while(valueSet)
			try {
				wait();
			} catch(InterruptedException e) {
				System.out.println("InterruptedException caught");
			}

		this.n = num;
		valueSet = true;
      	notify();
	}
	
	synchronized void receive(String operation, int num) {
		this.operation = operation;
		this.num = num;
		
		while(valueSet)
			try {
				wait();
			} catch(InterruptedException e) {
				System.out.println("InterruptedException caught");
			}

		this.n = num;
		valueSet = true;
      	notify();
	}
	
	synchronized int reply() {
		while(!valueSet)
			try {
				wait();
			} catch(InterruptedException e) {
				System.out.println("InterruptedException caught");
			}
		System.out.println("Consumer: " + SimpleCalculation.math(operation, num));
		valueSet = false;
		notify();
		return n;
	}
}

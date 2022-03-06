
public class Homework7 {
	
	public static void main(String[] args) {
		MessageBufferResponse buffer = new MessageBufferResponse();
	    Producer producer = new Producer(buffer);
	    new Consumer(buffer);
	    producer.startProducerThread();
	    
	    producer.send("add", 5);
	    producer.send("multiply", 9);
	    producer.send("multiply", 4);
	    producer.send("add", 3);
	    producer.send("add", 10);
	    producer.send("add", 30);
	    producer.send("multiply", 7);
	}

}

class Producer implements Runnable {
	MessageBufferResponse buffer;
	String operation;
	
	Producer(MessageBufferResponse buffer) {
		this.buffer = buffer;
	}

	public void run() {
	  
	}

	void send(String operation, int num) {
		System.out.println("Producer: (" + operation + ", " + num + ")");
		buffer.receive(operation, num);
	}
	  
	void startProducerThread() {
		new Thread(this, "Producer").start();
	}
}

class Consumer implements Runnable {
	MessageBufferResponse buffer;

	Consumer(MessageBufferResponse buffer) {
		this.buffer = buffer;
		new Thread(this, "Consumer").start();
	}

	public void run() {
		for(int i = 0; i < 7; i++) {
			buffer.reply();
		}
	}
}
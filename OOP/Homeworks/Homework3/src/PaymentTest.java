// problem 1

public class PaymentTest {
	public static void main(String[] args) {
		Payment cash1 = new CashPayment();
		cash1.setAmount(32.22);
		Payment cash2 = new CashPayment();
		cash2.setAmount(420.63);
		
		Payment card1 = new CreditCardPayment("Tony Stark", "02/26/2021", "123456789");
		card1.setAmount(12.22);
		Payment card2 = new CreditCardPayment("Iron Man", "12/19/2021", "987654321");
		card2.setAmount(823.34);
		
		cash1.paymentDetails();
		cash2.paymentDetails();
		card1.paymentDetails();
		card2.paymentDetails();
		
	}
}

class Payment {
	double amount;		// payment amount

	public double getAmount() {
		return amount;
	}

	public void setAmount(double amount) {
		this.amount = amount;
	}
	
	void paymentDetails() {
		System.out.println("Payment amount: $" + amount + "\n");		
	}
	
}

class CashPayment extends Payment {
	
	CashPayment() {
	}
	
	CashPayment(double amount) {
		super.amount = amount;
	}
	
	void paymentDetails() {
		System.out.println("Cash payment.");
		super.paymentDetails();
	}
}

class CreditCardPayment extends Payment {
	private String ccName;
	private String ccExpDate;
	private String ccNumber;
	
	CreditCardPayment(String name, String ExpDate, String ccNum){
		ccName = name;
		ccExpDate = ExpDate;
		ccNumber = ccNum;
	}
	
	void paymentDetails() {
		System.out.println("Credit card payment. Details:");
		System.out.println("Credit Card name: " + ccName);
		System.out.println("Credit Card expiration date: " + ccExpDate);
		System.out.println("Credit Card number: " + ccNumber);
		super.paymentDetails();
	}
}





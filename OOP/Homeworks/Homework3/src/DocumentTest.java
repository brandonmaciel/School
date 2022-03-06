// problem 2

public class DocumentTest {
	public static void main(String[] args) {
		Email email1 = new Email("This is the body of the email.");
		email1.setSender("John Appleseed");
		email1.setRecipient("Sir Isaac Newton");
		email1.setTitle("Title of email");
		
		Email email2 = new Email("Body of email is here.");
		email2.setSender("Texas Tech");
		email2.setRecipient("Jane Seedapple");
		email2.setTitle("Email title");
		
		File file1 = new File("This is the content of the text file.");
		file1.setPathname("/Downloads/file");
		
		File file2 = new File("Content of file.");
		file2.setPathname("/Downloads/folder/file");

		System.out.println("Email1 test: " + ContainsKeyword(email1, "This is the"));
		System.out.println("Email2 test: " + ContainsKeyword(email2, "Body of email"));
		System.out.println("File1 test: " + ContainsKeyword(file1, "content of the text"));
		System.out.println("File2 test: " + ContainsKeyword(file2, "Content of file"));
		
		
		/* un comment to print document content */		
//		System.out.println();
//		System.out.println(email1);
//		System.out.println();
//		System.out.println(email2);
//		System.out.println();
//		System.out.println(file1);
//		System.out.println();
//		System.out.println(file2);
	}
	
	public static boolean ContainsKeyword(Document docObject, String keyword) {
		if (docObject.toString().indexOf(keyword,0) >= 0) return true ;
		return false;
	}

}

class Document {
	String text; // stores any textual content for the document
	
	Document(String input) {
		text = input;
	}
	
	public String toString() {
		return text;
	}
	
}

class Email extends Document {
	private String sender;
	private String recipient;
	private String title;
	
	Email(String emailBody) {
		super(emailBody);				// store body of email in inherited variable 'text'
	}
	
	void setSender(String name) {
		sender = name;
	}
	
	String getSender() {
		return sender;
	}
	
	void setRecipient(String name) {
		recipient = name;
	}
	
	String getRecipient() {
		return recipient;
	}
	
	void setTitle(String title) {
		this.title = title;
	}
	
	String getTitle() {
		return title;
	}
	
	public String toString() {
		return "Sender: " + sender + "\n" + "Recipient: " + recipient + "\n" + title + "\n" + text;
	}
	
}

class File extends Document {
	private String pathname;
	
	File(String fileText) {
		super(fileText);				// store textual contents of the file in inherited variable 'text'
	}
	
	void setPathname(String path) {
		pathname = path;
	}
	
	String getPathname() {
		return pathname;
	}
	
}






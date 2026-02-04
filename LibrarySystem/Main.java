
import java.util.ArrayList;
import java.util.Scanner;

/**
 * The main class for the Library Management System. Provides the interactive menu to access the library class
 */
public class Main {

	/**
	 * The main method that provides the menu loop
	 */
	public static void main(String[] args) {
		Scanner scnr = new Scanner(System.in);
		Library lib = new Library();
		boolean exit = false;
		
		while (!exit) {
			System.out.println("Library Management System");
            System.out.println("1. Add Book");
            System.out.println("2. Add Member");
            System.out.println("3. Search Book");
            System.out.println("4. Issue Book");
            System.out.println("5. Return Book");
            System.out.println("6. List Borrowed Books");
            System.out.println("7. Exit");
            System.out.print("Choose an option: ");

            String choice = scnr.nextLine();
            
            switch(choice) {
            	case "1":
            		 System.out.print("Enter book title: ");
                     String title = scnr.nextLine();
                     System.out.print("Enter book author: ");
                     String author = scnr.nextLine();
                     System.out.print("Enter book ISBN: ");
                     String isbn = scnr.nextLine();
                     System.out.print("Enter number of copies: ");
                     int copies = Integer.parseInt(scnr.nextLine());

                     Book b = new Book(title, author, isbn, copies);
                     lib.addBook(b);
                     System.out.println("");
                     break;
                     
            	case "2":
            		System.out.print("Enter member name: ");
                    String name = scnr.nextLine();
                    lib.addMember(name);
                    System.out.println("");
                    break;
                    
            	case "3":
            		 System.out.println("Search book by:");
                     System.out.println("1. Title");
                     System.out.println("2. ISBN");
                     System.out.println("3. Author");
                     System.out.print("Choose an option: ");
                     String sChoice = scnr.nextLine();

                     if (sChoice.equals("1")) {
                         System.out.print("Enter the book title: ");
                         String searchTitle = scnr.nextLine();
                         Book foundBook = lib.findBookByTitle(searchTitle);
                         if (foundBook != null) {
                             System.out.println("Book found: " + foundBook.toString());
                         } else {
                             System.out.println("Book not found.");
                         }

                     } else if (sChoice.equals("2")) {
                         System.out.print("Enter book ISBN: ");
                         String searchISBN = scnr.nextLine();
                         Book foundBook = lib.findBookByISBN(searchISBN);
                         if (foundBook != null) {
                             System.out.println("Book found: " + foundBook.toString());
                         } else {
                             System.out.println("Book not found.");
                         }

                     } else if (sChoice.equals("3")) {
                         System.out.print("Enter the author name: ");
                         String searchAuthor = scnr.nextLine();
                         ArrayList<Book> booksByAuthor = lib.findBooksByAuthor(searchAuthor);
                         if (!booksByAuthor.isEmpty()) {
                             System.out.println("Books by " + searchAuthor + ":");
                             for (Book book : booksByAuthor) {
                                 System.out.println(book.toString());
                             }
                         } else {
                             System.out.println("No books found by this author.");
                         }

                     } else {
                         System.out.println("Invalid choice.");
                     }
                     System.out.println("");
                     break;
                     
            	case "4":
            		System.out.print("Enter member ID: ");
                    String issueMemberID = scnr.nextLine();
                    System.out.print("Enter book title to borrow: ");
                    String issueTitle = scnr.nextLine();
                    lib.issueBook(issueMemberID, issueTitle);
                    System.out.println("");
                    break;
                    
            	case "5":
            		System.out.print("Enter member ID: ");
                    String returnMemberID = scnr.nextLine();
                    System.out.print("Enter book title to return: ");
                    String returnTitle = scnr.nextLine();
                    lib.returnBook(returnMemberID, returnTitle);
                    System.out.println("");
                    break;
                    
            	case "6":
            		System.out.print("Enter member ID to list borrowed books: ");
                    String listMemberID = scnr.nextLine();
                    lib.listBorrowedBooks(listMemberID);
                    System.out.println("");
                    break;
                    
            	case "7":
            	 System.out.println("Exiting...");
                 exit = true;
                 System.out.println("");
                 break;
                 
            	default:
            		System.out.println("Invalid choice. Please select again.");
            		System.out.println("");
            }
		}
				
	}
}

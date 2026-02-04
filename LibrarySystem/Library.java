
import java.util.ArrayList;

/**
 * Stores books and members, while also implementing methods for books to be searched, added, issued, and returned
 */
public class Library {
	private ArrayList<Book> bLibrary = new ArrayList<>();
	private ArrayList<Member> mLibrary = new ArrayList<>();
	private int nextMember = 1;
	
	
	/**
	 * Adds a book if it is not already in the list
	 * 
	 * @param b is the book to be added 
	 */
	public void addBook(Book b) {
		for (Book books : bLibrary) {
			if(books.bookEquals(b)) {
				books.addCopies(b.getTCopies());
				System.out.println("Book already exists. Updated the number of copies in the library.");
				System.out.println("Copies available for borrowing: " + b.getACopies());
				return;
			}
		}
		bLibrary.add(b);
		System.out.println("Book added: "+ b.getTitle() + " by " + b.getAuthor() + " (ISBN: " + b.getIsbn() + ").");
		System.out.println("Copies available for borrowing: " + b.getACopies());
	}
	
	/**
	 * Adds a new member with an ID number
	 * @param name of the member to be added
	 */
	public void addMember(String name) {
		String mId = "M" + nextMember;
		nextMember++;
		Member m = new Member (name, mId);
		mLibrary.add(m);
		System.out.println("Member added: " + name + " (Member ID: " + mId + ")");
	}
	
	/**
	 * Finds a book by its title
	 * 
	 * @param title of the book
	 * @return books the book that share a title 
	 */
	public Book findBookByTitle(String title) {
		for (Book books: bLibrary) {
			if (books.getTitle().equalsIgnoreCase(title)) {
				return books;
			}
		}
		return null;
	}
	
	/**
	 * Finds a book by its ISBN
	 * 
	 * @param isbn of the book
	 * @return books the book that shares its isbn 
	 */
	public Book findBookByISBN(String isbn) {
		for (Book books: bLibrary) {
			if (books.getIsbn().equalsIgnoreCase(isbn)) {
				return books;
			}
		}
		return null;
	}
	
	
	/**
	 * Finds all the books written by the specified author
	 * 
	 * @param author the author to find the books of 
	 * @return result a list of books written by the author 
	 */
	public ArrayList<Book> findBooksByAuthor(String author) {
		ArrayList<Book> result = new ArrayList<>();
		for (Book books : bLibrary) {
			if(books.getAuthor().equalsIgnoreCase(author)) {
				result.add(books);
			}
		}
		return result;
	}
	
	
	/**
	 * Find a member by ID
	 * 
	 * @param mId the ID to find a member of 
	 * @return
	 */
	public Member findMember(String mId) {
		for (Member m : mLibrary) {
			if (m.getId().equalsIgnoreCase(mId)) {
				return m;
			}
		}
		return null;
	}
	
	
	/**
	 * Issues a book to a member 
	 * 
	 * @param mId member the book is issued too 
	 * @param title of the book issued to the member
	 */
	public void issueBook(String mId, String title) {
		Member m = findMember(mId);
		Book b = findBookByTitle(title);
		
		if (m == null) {
			System.out.println("Member not found");
			return;
		}
		
		if (b == null) {
			System.out.println("Book not found");
			return;
		}
		
		if (m.hasBorrowed(b)) {
			System.out.println(mId + " have already borrowed this book: " + title);
			System.out.println("Could not issue the book");
			return;
		}
		
		
		if (b.getACopies() == 0) {
			System.out.println("This book is currently unavailable. Could not issue the book.");
            return;
		}
		
		b.borrowCopy();
		m.borrowBook(b);
		System.out.println("Book issued: " + title + " to " + mId);
	}
	
	
	/**
	 * Returns a book from a member back to the library
	 * 
	 * @param mId the member returning the book
	 * @param title the title of the book being returned
	 */
	public void returnBook(String mId, String title) {
		Member m = findMember(mId);
		Book b = findBookByTitle(title);
		
		if (m == null) {
			System.out.println("Member not found");
			return;
		}
		
		if (b == null) {
			System.out.println("Book not found");
			return;
		}
		
		if (!m.hasBorrowed(b)) {
			System.out.println(mId + " has not borrowed this book: " + title + " by " + b.getAuthor() + ".");
			return;
		}
		
		
		b.returnCopy();
		m.returnBook(b);
		System.out.println("Book returned: " + b.toString());
	}
	
	/**
	 * Lists all of the borrowed books of the specified member
	 * 
	 * @param mId the id of the member having their borrowed books listed
	 */
	public void listBorrowedBooks(String mId) {
		Member m = findMember(mId);
		if (m == null) {
			System.out.println("Member not found.");
			return;
		}
		
		ArrayList<Book> borrowed = m.getBorrowedBooks();
		
		System.out.println(mId + " borrowed books: ");
		for (Book books : borrowed) {
			System.out.println(books.getTitle() + " (ISBN: " + books.getIsbn() + ").");
			}
		}
}
			

/**
 * Stores a book in a library with all its necessary information 
 */
public class Book {
	private String title;
	private String author;
	private String isbn;
	private int tCopies;
	private int aCopies;
	
	/**
	 * Creates a new book 
	 * 
	 * @param title book title
	 * @param author book author
	 * @param isbn unique identifier
	 * @param copies amount of copies 
	 */
	public Book(String title, String author, String isbn, int copies) {
		this.title = title;
		this.author = author;
		this.isbn = isbn;
		this.tCopies = copies;
		this.aCopies = copies;
	}
	
	/**
	 * Provides the title
	 * 
	 * @return title a String containing the title
	 */
	public String getTitle() {
		return title;
	}
	
	/**
	 * Provides the author
	 * 
	 * @return author a String containing the author
	 */
	public String getAuthor() {
		return author;
	}
	
	/**
	 * Provides the ISBN
	 * 
	 * @return isbn a String containing the ISBN
	 */
	public String getIsbn() {
		return isbn;
	}
	
	/**
	 * Provides the amount of total copies of the book
	 * 
	 * @return tCopies an int of the total copies of the book
	 */
	public int getTCopies() {
		return tCopies;
	}
	
	/**
	 * Provides the amount of current available copies of the book
	 * 
	 * @return aCopies the amount of current available copies
	 */
	public int getACopies() {
		return aCopies;
	}
	
	/**
	 * If there are copies available will borrow one
	 * 
	 * @return true if there copies left to borrow, false if not
	 */
	public boolean borrowCopy() {
		if (aCopies > 0) {
			aCopies--;
			return true;
		}
		return false;
	}
	
	/**
	 * Returns a single copy unless all copies are returned 
	 */
	public void returnCopy() {
		if (aCopies < tCopies) aCopies++;
	}
	
	
	/** 
	 * Increases the number of copies if positive
	 * 
	 * @param copies to add 
	 */
	public void addCopies(int copies) {
		if(copies<1) return;
		tCopies += copies;
		aCopies += copies;
	}
	

	/**
	 * Checks if two books have the same title, author, and ISBN
	 * 
	 * @param b book to compare
	 * @return true if they are the same book, false if not
	 */
	public boolean bookEquals(Book b) {
		return title.equalsIgnoreCase(b.title) && author.equalsIgnoreCase(b.author) && isbn.equalsIgnoreCase(b.isbn);
	}

	
	/**
	 * Overrides the toString method to print all of the Book information
	 * 
	 * @return String listing all of the books information
	 */
	@Override 
	public String toString() {
		return title + " by " + author + " (ISBN: " + isbn + "). Copies available for borrowing: " + aCopies;
	}
}

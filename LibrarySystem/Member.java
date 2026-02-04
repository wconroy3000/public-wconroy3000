import java.util.ArrayList;

/**
 * Represents a library member and stores their name, ID, and books they have borrowed
 */
public class Member {
    private String name;
    private String id;
    private ArrayList<Book> borrowedBooks;

    /**
     * Creates a new member and a list for their borrowed books to be stored
     * 
     * @param name name of the member
     * @param id the Id of the member
     */
    public Member(String name, String id) {
        this.name = name;
        this.id = id;
        borrowedBooks = new ArrayList<>();
    }
    
    /**
     * Provides the name of the member
     * 
     * @return name a String containing the member's name
     */
    public String getName() {
        return name;
    }
    
    /**
     * Provides the Id of the member
     * 
     * @return id a String containing the member's id
     */
    public String getId() {
        return id;
    }

    /**
     * Returns the list of borrowed books
     * 
     * @return borrowedBooks an ArrayList of the borrowed books
     */
    public ArrayList<Book> getBorrowedBooks() {
        return borrowedBooks;
    }

    /**
     * Checks if the member has already borrowed the specified book
     * 
     * @param b the book being checked
     * @return true if the member has borrowed the book, false if not
     */
    public boolean hasBorrowed(Book b) {
        for (Book books : borrowedBooks) {
            if (books.bookEquals(b)) {
                return true;
            }
        }
        return false;
    }


    /**
     * Adds a book to the members borrowed book list
     * 
     * @param b the book to be added
     */
    public void borrowBook(Book b) {
        if (!hasBorrowed(b)) {
            borrowedBooks.add(b);
        }
    }


    /**
     * removes a book from the member's borrowed list
     * 
     * @param b the book to be removed
     */
    public void returnBook(Book b) {
        for (Book books : borrowedBooks) {
        	if (books.bookEquals(b)) {
        		borrowedBooks.remove(books);
        		return;
        	}
        }
    }
}

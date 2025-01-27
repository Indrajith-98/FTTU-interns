# Library Management System

This Library Management System allows users to manage a collection of books, track user progress, and interact with books using a simple command-line interface.

## **Project Structure**

The project consists of the following files:

1. **`library_manager.py`**: Contains the `LibraryManager` class, which handles the core functionalities like loading books, adding books, and saving data to a JSON file.
2. **`book.py`**: Contains the `Book` class, which represents individual books and their associated functionalities like adding users and updating progress.
3. **`main.py`**: Acts as the entry point of the application. It provides a menu for the user to interact with the library and books.
4. **`library_data.json`**: Stores the book data in JSON format.

---

## **Features**

### **1. Library Menu**
- **Add a New Book**: Add a new book to the library by providing details such as title, author, total pages, topic, and chapters.
- **List All Books**: Display all the books in the library.
- **Remove a Book**: Delete a book from the library by specifying its title.
- **Save Changes**: Save any changes made to the library data back to the JSON file.

### **2. Book Menu**
- **Add User to Book**: Add a user to a specific book to track their reading progress.
- **Update User Progress**: Update the reading progress of a user for a specific book.
- **View All Users**: Display all users and their reading progress for a specific book.

---

## **Usage**

1. **Run the Program**:
   Run `main.py` to start the application.

   ```bash
   python main.py
   ```

2. **Choose a Menu**:
   - The program will prompt you to select the `Library Menu` or `Book Menu`.

3. **Perform Actions**:
   - Follow the on-screen instructions to interact with the library or books.

---

## **File Details**

### **library_manager.py**
- Manages the collection of books.
- Functions include:
  - `load_library()`: Load books from the JSON file.
  - `save_library()`: Save changes to the JSON file.
  - `add_book()`: Add a new book to the library.
  - `remove_book()`: Remove a book from the library.
  - `list_books()`: List all books in the library.

### **book.py**
- Represents individual books and their functionalities.
- Functions include:
  - `add_user()`: Add a new user to the book.
  - `update_user_progress()`: Update a user's reading progress.
  - `display_users()`: Display all users and their progress.

### **main.py**
- Provides the main interface for the user to interact with the system.
- Functions include:
  - `show_library_menu()`: Display options to manage the library.
  - `show_book_menu()`: Display options to manage individual books.

### **library_data.json**
- Stores library data in the following structure:

```json
{
  "books": {
    "Book Title": {
      "title": "Book Title",
      "author": "Author Name",
      "total_pages": 300,
      "topic": "Fiction",
      "chapters": ["Chapter 1", "Chapter 2", "Chapter 3"],
      "users": {
        "User1": {
          "current_page": 100,
          "current_chapter": "Chapter 2"
        }
      }
    }
  }
}
```

---

## **How to Extend**

1. **Add New Features**:
   - Modify `library_manager.py` or `book.py` to include new functionalities, such as filtering books by topic or exporting user progress.

2. **Improve the Interface**:
   - Integrate a graphical user interface (GUI) using libraries like Tkinter or PyQt.

---

## **Requirements**

- Python 3.x

---

## **Example Interaction**

```plaintext
Welcome to the Library Management System

1. Library Menu
2. Book Menu
3. Exit

Select an option: 1

--- Library Menu ---
1. Add Book
2. List All Books
3. Remove Book
4. Save Changes
5. Go Back

Select an option: 2

--- List of Books ---
1. The Great Gatsby
2. To Kill a Mockingbird
...
```

---

## **License**
This project is open-source and available for modification and distribution.

---

## **Author**
Sakthi Santhosh

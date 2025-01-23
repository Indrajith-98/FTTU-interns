# **E-Book Library Management System**

The **E-Book Library Management System** is a Python-based application that enables users to manage and access e-books in a streamlined manner. It offers features for both administrators and regular users, providing a secure and efficient platform to manage e-books, track reading progress, and ensure controlled access.

### **Key Features**
1. **User Management**:
   - Users can sign up, log in, and access e-books.
   - Admins can manage the e-book collection.

2. **Admin Privileges**:
   - Admins can add or delete books in the library.
   - Admin creation requires a security key (`ebook2025@12345`) to ensure secure access.

3. **E-Book Management**:
   - View the list of available e-books.
   - Track and update reading progress, including the current page and topic.

4. **Database Design**:
   - Single `users` table with an `is_admin` column to differentiate between regular users and admins.
   - `books` table for storing book details.
   - `reading_status` table for tracking user progress on specific books.

5. **Security**:
   - Admin privileges are protected by a security key to prevent unauthorized access.

6. **Scalability**:
   - Modular code structure ensures easy extension and maintenance.

### **How It Works**
- **Sign-Up & Log-In**: Users can create accounts and log in to access the system. Admins can also log in using their credentials.
- **Admin Operations**: Admins can add or remove books and view all available books in the system.
- **User Operations**: Users can browse e-books, start reading, and update their progress. Reading progress is saved in the database for later reference.
- **Database Interaction**: All data (users, books, and reading statuses) is stored in an SQLite database.



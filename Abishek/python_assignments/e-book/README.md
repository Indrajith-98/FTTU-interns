# **Python Assignment**

## **Task Overview**
This project implements a console-based E-Book Management System using SQLite for database management. It provides user authentication, book management, and reading progress tracking functionalities.

### **Key Features**:

#### **User Management**:
* Users can register and log in securely.
* Each user’s reading progress is tracked individually.

#### **Book Management**:
* Admins can add books to the system.
* Users can view available books with details like author, page count, and readers.

#### **Reading Progress Tracking**:
* Users can start or resume reading a book.
* The system saves the last read page and topic for each book per user.

#### **Database Operations**:
* Uses SQLite to store user credentials, book details, and reading progress.
* Ensures data integrity with unique constraints and relationships between tables.

#### **Admin Privileges**:
* Admins can add books after entering a password.

## **Project Folder Contents**

### **ebook_app.db**
The sqlite database.

### **main.py**
The python file which contains the implementation.
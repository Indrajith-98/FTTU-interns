import csv
import os

class Book:
    def __init__(self, title):
        self.title = title
        
        self.data_file = os.path.join("Abhinav/python_assignments", f"{title}_data.csv")

        # Ensure the CSV file exists
        if not os.path.exists(self.data_file):
            with open(self.data_file, mode="w", newline="") as file:
                writer = csv.writer(file)
                writer.writerow(["Username", "Page Number", "Current Page Number", "Topic"])
       


    def update_user_info(self, username, page_number, current_page, topic):
        users = self.load_data()
        user_found = False

        # Update user information if they already exist in the CSV
        for user in users:
            if user["Username"] == username:
                user["Page Number"] = page_number
                user["Current Page Number"] = current_page
                user["Topic"] = topic
                user_found = True
                break

        # Add new user if not found
        if not user_found:
            users.append({
                "Username": username,
                "Page Number": page_number,
                "Current Page Number": current_page,
                "Topic": topic
            })

        self.save_data(users)
        print(f"Updated information for {username}.")

    def get_user_info(self, username):
        users = self.load_data()
        for user in users:
            if user["Username"] == username:
                return user
        return None

    def load_data(self):
        users = []
        with open(self.data_file, mode="r") as file:
            reader = csv.DictReader(file)
            for row in reader:
                users.append(row)
        return users

    def save_data(self, users):
        with open(self.data_file, mode="w", newline="") as file:
            writer = csv.DictWriter(file, fieldnames=["Username", "Page Number", "Current Page Number", "Topic"])
            writer.writeheader()
            writer.writerows(users)

# Example usage
if __name__ == "__main__":
    book = Book("eBookUser")

    while True:
        print("\nOptions:")
        print("1. Update User Info")
        print("2. Get User Info")
        print("3. Exit")

        choice = input("Enter your choice: ")

        if choice == "1":
            username = input("Enter username: ")
            page_number = input("Enter total page number: ")
            current_page = input("Enter current page number: ")
            topic = input("Enter topic: ")
            book.update_user_info(username, page_number, current_page, topic)

        elif choice == "2":
            username = input("Enter username: ")
            user_info = book.get_user_info(username)
            if user_info:
                print("\nUser Information:")
                print(f"Username: {user_info['Username']}\nPage Number: {user_info['Page Number']}\nCurrent Page Number: {user_info['Current Page Number']}\nTopic: {user_info['Topic']}")
            else:
                print("User not found.")

        elif choice == "3":
            print("Exiting the application.")
            break

        else:
            print("Invalid choice. Please try again.")

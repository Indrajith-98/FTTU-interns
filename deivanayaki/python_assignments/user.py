class User:
    def __init__(self,name,email,password,fav_genre):
        self.name=name
        self.email=email
        self.password=password
        self.fav_genre=fav_genre
    
    def register_msg(self):
        return f"Hii {self.name}, Your data was registered successfully!!"

    def login_msg(self):
        return f"Hii {self.name}, login successfully!! let's explore books!!"
    
    def to_csv(self):
        return [self.name,self.email,self.password,self.fav_genre]
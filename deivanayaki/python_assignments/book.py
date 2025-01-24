class Book:
    def __init__(self,name,author,genre,total_pg,book_topics):
        self.name=name
        self.author=author
        self.genre=genre
        self.total_pg=total_pg
        self.book_topics=book_topics
    
    def to_csv(self):
        return [self.name,self.author,self.genre,self.total_pg,self.book_topics]
    
    def __str__(self):
        return f"Name        : {self.name}\nAuthor      : {self.author}\nGenre       : {self.genre}\nTotal Pages : {self.total_pg}\nBook Topics : {self.book_topics}\n"
    





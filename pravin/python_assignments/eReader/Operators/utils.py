# utils.py
def paginate(content, lines_per_page):
    for i in range(0, len(content), lines_per_page):
        yield content[i:i + lines_per_page]

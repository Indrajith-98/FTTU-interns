import csv
import os

def file_path(filename):
    # Get the directory of the current script (E-Library folder)
    base_dir = os.path.dirname(os.path.abspath(__file__))
    directory = os.path.join(base_dir, "data")
    
    # Ensure the data directory exists
    if not os.path.exists(directory):
        os.makedirs(directory)
    return os.path.join(directory, filename)

def read_csv(filepath):
    if not os.path.exists(filepath):
        return []
    with open(filepath, mode="r") as file:
        return list(csv.DictReader(file))

def write_csv(filepath, data):
    if not data:
        return
    with open(filepath, mode="w", newline="") as file:
        writer = csv.DictWriter(file, fieldnames=data[0].keys())
        writer.writeheader()
        writer.writerows(data)

#!/bin/bash

# Define paths
SOURCE_FILE="user-1/main.c"
OUTPUT_FILE="user-1/main"

# Check if the source file exists
if [ ! -f "$SOURCE_FILE" ]; then
    echo "Error: Source file $SOURCE_FILE does not exist."
    exit 1
fi

# Compile the C program
gcc "$SOURCE_FILE" -o "$OUTPUT_FILE"

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    # Run the compiled program
    "$OUTPUT_FILE"
else
    echo "Compilation failed. Please check the errors."
    exit 1
fi

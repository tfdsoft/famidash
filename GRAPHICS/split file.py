import sys
import os

def split_chr_file(input_file):
    try:
        # Read the entire .chr file in binary mode
        with open(input_file, 'rb') as file:
            data = file.read()

        # Determine the midpoint
        midpoint = len(data) // 2

        # First half
        first_half = data[:midpoint]
        # Second half
        second_half = data[midpoint:]

        # Get the base file name (without extension) and directory
        base_name = os.path.splitext(input_file)[0]

        # Write the first half to a new file
        with open(f'{base_name}_first_half.chr', 'wb') as file1:
            file1.write(first_half)

        # Write the second half to a new file
        with open(f'{base_name}_second_half.chr', 'wb') as file2:
            file2.write(second_half)

        print(f"Successfully split '{input_file}' into two halves.")
    except FileNotFoundError:
        print(f"Error: File '{input_file}' not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Main entry point
if __name__ == '__main__':
    if len(sys.argv) > 1:
        # File was provided via drag-and-drop or as a command-line argument
        split_chr_file(sys.argv[1])
    else:
        print("Please drag and drop a .chr file onto this script.")


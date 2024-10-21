import sys
import os

def remove_every_other_1kb(input_file):
    try:
        # Read the entire file in binary mode
        with open(input_file, 'rb') as file:
            data = file.read()

        # Split the data into 1KB blocks
        block_size = 1024  # 1KB
        blocks = [data[i:i + block_size] for i in range(0, len(data), block_size)]

        # Keep every other block, starting with the first
        filtered_blocks = [blocks[i] for i in range(len(blocks)) if i % 2 == 0]

        # Combine the filtered blocks back into a single binary data
        result_data = b''.join(filtered_blocks)

        # Get the base file name (without extension) and directory
        base_name = os.path.splitext(input_file)[0]

        # Write the filtered data to a new file
        output_file = f'{base_name}_filtered.chr'
        with open(output_file, 'wb') as output:
            output.write(result_data)

        print(f"Successfully removed every other 1KB from '{input_file}' and saved it as '{output_file}'.")

    except FileNotFoundError:
        print(f"Error: File '{input_file}' not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Main entry point
if __name__ == '__main__':
    if len(sys.argv) > 1:
        # File was provided via drag-and-drop or as a command-line argument
        remove_every_other_1kb(sys.argv[1])
    else:
        print("Please provide a file by drag-and-drop or as a command-line argument.")


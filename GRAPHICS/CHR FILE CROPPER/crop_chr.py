import os

def crop_chr_by_transparent_row(input_file_path, output_dir):
    tile_width_pixels = 8
    tile_height_pixels = 8
    bits_per_pixel = 2
    bytes_per_tile = (tile_width_pixels * tile_height_pixels * bits_per_pixel) // 8
    tiles_per_row = 16  # Assuming a standard 128-pixel wide pattern table

    transparent_color_index = 0
    if bits_per_pixel == 2:
        blank_tile_data = bytes([0x00] * bytes_per_tile) # All pixels are color index 0
    else:
        print("Error: Script currently only handles 2 bits per pixel.")
        return

    input_filename = os.path.basename(input_file_path)
    output_filename = input_filename.replace(".chr", "_cropped.chr")
    output_file_path = os.path.join(output_dir, output_filename)
    success = False

    try:
        with open(input_file_path, 'rb') as infile:
            data = infile.read()
            num_tiles = len(data) // bytes_per_tile

            for row_start_tile in range(0, num_tiles, tiles_per_row):
                is_blank_row = True
                for i in range(tiles_per_row):
                    tile_index = row_start_tile + i
                    if tile_index < num_tiles:
                        tile_data = data[tile_index * bytes_per_tile : (tile_index + 1) * bytes_per_tile]
                        if tile_data != blank_tile_data:
                            is_blank_row = False
                            break
                    else:
                        break # Reached end of data

                if is_blank_row:
                    # Found a blank row, truncate the data here
                    cropped_data = data[:row_start_tile * bytes_per_tile]
                    with open(output_file_path, 'wb') as outfile:
                        outfile.write(cropped_data)
                    print(f"Cropped {input_filename} at row {row_start_tile // tiles_per_row} to {output_filename} in {output_dir}")
                    success = True
                    return success  # Indicate success

            # If no blank row is found, copy the original file
            with open(output_file_path, 'wb') as outfile:
                outfile.write(data)
            print(f"No completely transparent row found to crop in {input_filename}, copied to {output_filename} in {output_dir}")
            success = True
            return success  # Indicate success

    except FileNotFoundError:
        print(f"Error: Input file '{input_filename}' not found.")
    except Exception as e:
        print(f"An error occurred processing '{input_filename}': {e}")

    return success # Return success status

if __name__ == "__main__":
    input_directory = "INPUT"
    output_directory = "OUTPUT"

    # Create INPUT directory if it doesn't exist
    if not os.path.exists(input_directory):
        os.makedirs(input_directory)
        print(f"Created directory: {input_directory}. Please place your input CHR files here.")

    # Create OUTPUT directory if it doesn't exist
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)
        print(f"Created directory: {output_directory}")

    for filename in os.listdir(input_directory):
        if filename.lower().endswith(".chr"):
            input_chr_file = os.path.join(input_directory, filename)
            if crop_chr_by_transparent_row(input_chr_file, output_directory):
                try:
                    os.remove(input_chr_file)
                    print(f"Removed: {input_chr_file} from INPUT folder.")
                except OSError as e:
                    print(f"Error removing {input_chr_file}: {e}")

    print("\nFinished processing CHR files.")
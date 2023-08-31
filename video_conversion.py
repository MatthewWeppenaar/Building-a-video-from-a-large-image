import cv2
import os
#partially created using chatGPT

def convert_pgm_to_video(image_folder, output_file):
    # Get the list of PGM files in the image folder
    file_list = [f for f in os.listdir(image_folder) if f.endswith('.pgm')]

    # Sort the file list by filename
    file_list.sort()

    # Read the first image to get the dimensions
    first_image_path = os.path.join(image_folder, file_list[0])
    first_image = cv2.imread(first_image_path, cv2.IMREAD_GRAYSCALE)
    height, width = first_image.shape

    # Create the video writer
    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    video_writer = cv2.VideoWriter(output_file, fourcc, 60.0, (width, height))

    # Iterate over the image files and write frames to the video
    for file_name in file_list:
        image_path = os.path.join(image_folder, file_name)
        image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

        # Convert the image to 3 channels (grayscale to BGR)
        image = cv2.cvtColor(image, cv2.COLOR_GRAY2BGR)

        # Write the frame to the video
        video_writer.write(image)

    # Release the video writer and close the video file
    video_writer.release()

    print("Video conversion complete!")

# Usage example

image_folder = 'out'
output_file = 'output_video.mp4'
convert_pgm_to_video(image_folder, output_file)

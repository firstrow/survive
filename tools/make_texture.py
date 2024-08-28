import sys
import json
from os import listdir
from os.path import isfile, join, exists
from PIL import ImageColor
from PIL import Image

# this script makes a sprite-sheet texture from blender rendered files

# dirs = ["N", "NE", "E", "SE", "S", "SW", "W", "NW"]
# dirs = ["3", "4", "5", "6", "7", "0", "1", "2"]
# dirs = ["0", "1", "2", "3", "4", "5", "6", "7"]
dirs = ["1", "2", "3", "4", "5", "6", "7", "0"]

def list_folders(p):
    return [f for f in listdir(p) if isfile(join(p, f)) == False]

def list_files(p):
    return [f for f in listdir(p) if isfile(join(p, f))]

def count_files(p):
    return len(list_files(p))

def create_canvas(frame_width, frame_height, max_frames):
    return Image.new('RGBA', (frame_width*max_frames, frame_height*8));

def read_json(path):
    with open(path, 'r') as f:
        return json.load(f)

def main(root_path):
    animations = list_folders(root_path)
    for anim_name in animations:
        animData = read_json(join(root_path, anim_name, 'data.json'))
        maxFrames = animData['frames']
        frame_width = animData['width']
        frame_height = animData['height']
        canvas = create_canvas(frame_width, frame_height, maxFrames)
        row = 0
        for direction in dirs:
            direction_folder = join(root_path, anim_name, direction)
            for i in range(1, maxFrames + 1): # direciton name
                file_path = join(direction_folder, str(i) + '.png')
                frame = Image.open(file_path)
                x = (i - 1) * frame_width
                canvas.paste(frame, (x, row*frame_height))
            row += 1
        canvas.save(join(root_path, anim_name + '.png'))

if __name__ == "__main__":
    main(sys.argv[1]);

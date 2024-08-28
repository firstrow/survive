#!/usr/bin/env python3

import sys, code
import pdb
from os import listdir
from os.path import isfile, join, exists
from PIL import ImageColor
from PIL import Image

frames_per_row = 10

def list_folders(p):
    return [f for f in listdir(p) if isfile(join(p, f)) == False]

def list_files(p):
    return [f for f in listdir(p) if isfile(join(p, f))]

def count_files(p):
    return len(list_files(p))

def create_canvas(frame_width, frame_height, max_frames):
    return Image.new('RGBA', (frame_width*max_frames, frame_height));

def main(root_path):
    files = list_files(root_path);
    sample = Image.open(join(root_path, files[0]))
    canvas = create_canvas(sample.width, sample.height, 8)
    x = 0
    for file in files:
        f = Image.open(join(root_path, file))
        canvas.paste(f, (x, 0))
        x += sample.width

    canvas.save(join(root_path, 'texture.png'))

if __name__ == "__main__":
    main(sys.argv[1]);

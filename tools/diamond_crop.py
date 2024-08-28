#!/usr/bin/env python3

from PIL import ImageColor
from PIL import Image

def map_coords(x, y):
    mx = (x - y) * (64 / 2)
    my = (x + y) * (32 / 2)
    return (mx, my)

mask = Image.open('/home/andrew/code/c/survive/assets/diamond_mask.png')

all = Image.new('RGBA', (512, 256))

def get_masked(mx, my, texture):
        pos = map_coords(mx , my)
        canvas = Image.new('RGBA', (64, 32))
        for x in range(64):
                for y in range(32):
                        col = mask.getpixel((x, y))
                        if col[3] == 255:
                                brush = texture.getpixel((x+pos[0]+512/2-32,y+pos[1]))
                                canvas.putpixel((x,y), brush)
        return canvas

tasks = [
    ("watershore", Image.open('/home/andrew/code/c/survive/assets/watershore.png')),
    ("masks", Image.open('/home/andrew/code/c/survive/assets/icewater.png')),
    ("grass", Image.open('/home/andrew/code/c/survive/assets/grass.png')),
    ("water", Image.open('/home/andrew/code/c/survive/assets/water.png')),
    ("beach", Image.open('/home/andrew/code/c/survive/assets/beach.png')),
]

for row in tasks:
        for mx in range(0, 8):
                for my in range(0, 8):
                        all.paste(get_masked(mx, my, row[1]), (mx*64,my*32))
        all.save('/home/andrew/code/c/survive/assets/cropped/'+row[0]+'.png')

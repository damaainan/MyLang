#!/usr/bin/env python3
# -*- coding: utf-8 -*-

''' 识别图像文件 '''

from __future__ import print_function
import sys
from PIL import Image

for infile in sys.argv[1:]:
    try:
        with Image.open(infile) as im:
            print(infile, im.format, "%dx%d" % im.size, im.mode)
    except IOError:
        pass
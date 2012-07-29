#
#  capture script
#
import commands
import os
import random
import re
import sys

def parse_info(info):
  matches = re.search('Duration: ([0-9]+):([0-9]+):([0-9]+)\.[0-9]+', info)
  if matches is None:
    print 'bandai: invalid video info'
    raise

  total = 0
  for i, num in enumerate(matches.groups()):
    total += int(num) * (60 ** (2 - i))

  return { 'total' : total }

def get_info(video_name):
  return commands.getoutput("ffmpeg -i " + video_name)

def capture(time, video_path, capture_path, frame):
  capture_command = 'ffmpeg -ss ' + str(time) + ' -vframes ' + str(frame) + ' -i ' + video_path + ' -f image2 ' + capture_path 
  os.system(capture_command)

def capture_op(video_time, dir_name, video_name):
  CAPTURE_COUNT = 3
  for c in range(CAPTURE_COUNT):
    capture_time = c * video_time / (CAPTURE_COUNT - 1)
    capture_path = dir_name + '/' + str(c) + '.jpg'
    capture(capture_time, video_name, capture_path, 1)

def capture_full(video_time, dir_name, video_name):
  CAPTURE_LIMIT = 360
  for c in range(min(video_time, CAPTURE_LIMIT)):
    frame = 1 if c % 2 < 1 else 12
    capture_path = dir_name + '/' + str(c) + '.jpg'
    capture(c, video_name, capture_path, frame)

def is_op():
  return len(sys.argv) > 2 and sys.argv[2] == 'op'

# main
CAPTURE_COUNT = 3
video_exps = re.compile('(.*)\.mp4')
video_name = sys.argv[1]
video_time = parse_info(get_info(video_name)).get('total', -1)

if video_time < 1:
  print 'bandai: invalid video time'
  raise

dir_name = 'op' if is_op() else 'full'
dir_path = '/home/myatsumoto/c++/bandai/raw/' + dir_name + '/' + video_exps.match(video_name).groups()[0]

if not os.path.exists(dir_path):
  os.mkdir(dir_path)

if is_op():
  capture_op(video_time, dir_path, video_name)
else:
  capture_full(video_time, dir_path, video_name)

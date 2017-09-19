#!/usr/bin/env python3

import sys
import subprocess
import tempfile
import os

tool = sys.argv[1]
command = os.path.splitext(os.path.split(tool)[1])[0]
target = sys.argv[2]

def trdummy(target):
	file = tempfile.NamedTemporaryFile("w+", prefix=".", suffix=".pro", dir=os.path.dirname(target), delete=False)
	file.write("include(" + os.path.abspath(target) + ")\n")
	file.write("TRANSLATIONS += $$QPM_TRANSLATIONS\n")
	file.close()

	return file

file = None

if command == "lupdate":
	suffix = os.path.splitext(target)[1]
	if suffix == ".pri":
		file = trdummy(target)
	elif suffix == ".pro":
		file = tempfile.NamedTemporaryFile("w+", prefix=".", suffix=".pro", dir=os.path.dirname(target), delete=False)
		with open(target) as orig:
			for line in orig:
				if "vendor.pri" not in line:
					file.write(line)
		file.close()
	else:
		print("Unrecognized file type")
		sys.exit(1)
elif command == "lrelease":
	file = trdummy(target)
else:
	print("Usage: qpm-translate.py lupdate|lrelease pro-file|pri-file [command args...]")
	sys.exit(1)

args = sys.argv[3:]
args.insert(0, tool)
args.append(file.name)
subprocess.run(args)

os.remove(file.name)

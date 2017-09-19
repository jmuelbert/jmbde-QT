#!/usr/bin/env python3

import sys
import subprocess
import os

tool = sys.argv[1]
prodir = sys.argv[2]
translations = sys.argv[3:]

filesmap = {}
namemap = {}

for ts in translations:
	name = os.path.splitext(ts)[0]
	index = name.rindex("_")
	lang = name[index+1:]
	filesmap[lang] = []
	namemap[lang] = os.path.split(name)[1]

for root, subdirs, files in os.walk(prodir, followlinks=True):
	for file in files:
		if file[-3:] == ".qm":
			name = os.path.splitext(file)[0]
			index = name.rindex("_")
			lang = name[index+1:]
			if lang in filesmap:
				filesmap[lang].append(os.path.join(root, file))

for lang in filesmap:
	command = [
		tool,
		"-i"
	]
	command += filesmap[lang]
	command.append("-o")
	command.append(namemap[lang] + ".qm")

	subprocess.run(command)

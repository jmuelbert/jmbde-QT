#!/bin/sh
lrelease -compress -nounfinished ./*.ts
mv *.qm ../packages/de.jmuelbert.setup/meta/

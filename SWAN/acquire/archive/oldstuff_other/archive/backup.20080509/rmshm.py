#!/usr/bin/python

# rmshm.py
# Program to remove shared memory segments with permission 666
#
# Created by Jayanth Chennamangalam

import commands

print "Removing shared memory segments with permission 666..."

(status, output) = commands.getstatusoutput("ipcs -m | grep 666")
if ("" ==output):
    print "No shared memory segment found with permission 666!"
    exit(0)
if (status != 0):
    print "rmshm: ERROR running ipcs!"
    print output
    exit(1)

lines = output.splitlines()

i = 0
for line in lines:
    startindex = line.find(" ") + 1
    stopindex = line.find(" ", startindex)
    shmid = line[startindex: stopindex]
    print "Removing shared memory segment with shmid " + shmid + "...",
    (status, output) = commands.getstatusoutput("ipcrm -m " + shmid)
    if (0 == status):
        print "DONE"
    else:
        print "FAILED: " + output
    i = i + 1

print "Shared memory removal complete."

(status, output) = commands.getstatusoutput("ipcs -m")
if (status != 0):
    print "rmshm: ERROR running ipcs!"
    print output
    exit(1)
print output


#!/usr/bin/python

# checkintegrity.py
# Program to automate the integrity checking of data acquired using
#   the 'acquire' program
#
# Created by Jayanth Chennamangalam

import sys
import commands

# definitions
filenameprefix = "packet"
checkprogram = "long_mark_gap"

# get the command line arguments
expectedargc = 5
argc = len(sys.argv)
if (argc != expectedargc):
    print "ERROR: Invalid number of arguments!"
    print "    Usage: " + sys.argv[0] + " <path> <num_files_to_be_processed>",
    print "<num_slips_allowed> <output_filename>"
    exit(1)

path = sys.argv[1]                  # directory containing the data files

if (False == sys.argv[2].isdigit()):
    print "ERROR: Invalid argument!"
    print "    Usage: " + sys.argv[0] + " <path> <num_files_to_be_processed>",
    print "<num_slips_allowed> <output_filename>"
    exit(1)
numfiles = int(sys.argv[2])         # number of files that are to be processed

if (False == sys.argv[3].isdigit()):
    print "ERROR: Invalid argument!"
    print "    Usage: " + sys.argv[0] + " <path> <num_files_to_be_processed>",
    print "<num_slips_allowed> <output_filename>"
    exit(1)
numslipsallowed = int(sys.argv[3])  # number of slips allowed

outputfilename = sys.argv[4]        # output file name

print "Batch integrity check commencing..."

f = open(outputfilename, 'w')

fileindices = xrange(0, numfiles)
for i in fileindices:
    file = path + "/" + filenameprefix + str(i)
    print "Checking file " + file + "...",
    sys.stdout.flush()
    (status, output) = commands.getstatusoutput("~/src/acquire/" \
                                                + checkprogram \
                                                + " " \
                                                + file \
                                                + " " \
                                                + str(numslipsallowed))
    print "DONE"
    f.write(output)
    f.write("\n\n");
    f.write("----------------------------------------------------------------");
    f.write("\n\n");

f.close()

print "Batch integrity check completed."


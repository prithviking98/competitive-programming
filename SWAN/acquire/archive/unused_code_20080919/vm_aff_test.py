#!/usr/bin/python

# vm_aff_test.py
# Automated test suite for testing with kernel pdflush parameters and processor
#   affinity
# Usage: vm_aff_test.py <vm.dirty_expire_centisecs>
#
# Created by Jayanth Chennamangalam

import sys
import commands

# get the command line argument
expectedargc = 2
argc = len(sys.argv)
if (argc != expectedargc):
    print "ERROR: Invalid number of arguments!"
    print "    Usage: " + sys.argv[0] + " <sampling_rate_in_MHz>"
    exit(1)

if (False == sys.argv[1].isdigit()):
    print "ERROR: Invalid argument!"
    print "    Usage: " + sys.argv[0] + " <sampling_rate_in_MHz>"
    exit(1)
dirty_expire_centisecs = sys.argv[1]    # vm.dirty_expire_centisecs

# definitions
max_runs = 20
dir_commands = "~/src/acquire/"
dir_reports = "~/run/reports/"
cmd_acq = "acquire_1056bytes"
cmd_affinity = "taskset 0x00000001 "
cmd_check = "long_mark_gap"
dev = "eth0"
wr_check_file_prefix = "wr_check_"

print "Test commencing..."

print "Setting the value of vm.dirty_expire_centisecs to " \
      + dirty_expire_centisecs
(status, output) = commands.getstatusoutput("sysctl -w " \
                                            + "vm.dirty_expire_centisecs=" \
                                            + dirty_expire_centisecs)
print "Creating directories..."
(status, output) = commands.getstatusoutput("mkdir " \
                                            + dirty_expire_centisecs \
                                            + "_na")
(status, output) = commands.getstatusoutput("mkdir " \
                                            + dirty_expire_centisecs \
                                            + "_wa")
(status, output) = commands.getstatusoutput("mkdir " \
                                            + dir_reports \
                                            + dirty_expire_centisecs \
                                            + "_na")
(status, output) = commands.getstatusoutput("mkdir " \
                                            + dir_reports \
                                            + dirty_expire_centisecs \
                                            + "_wa")

# test case 1:
# no affinity
print "Running test case 1 (no affinity)..."

print "Acquiring data..."
# acquire data and write it to shared memory
(status, output) = commands.getstatusoutput(dir_commands \
                                            + cmd_acq \
                                            + " " \
                                            + dev \
                                            + " " \
                                            + str(max_runs))

indices = xrange(0, max_runs)
for i in indices:
    print "Checking data set " + str(i) + " for slips...",
    sys.stdout.flush()
    # check for slips
    (status, output) = commands.getstatusoutput(dir_commands \
                                                + cmd_check \
                                                + " packet" \
                                                + str(i) \
                                                + " 4 20 10" \
                                                + " > " \
                                                + dir_reports \
                                                + dirty_expire_centisecs \
                                                + "_na" \
                                                + "/" \
                                                + wr_check_file_prefix \
                                                + str(i))
    print "DONE"

# move the data files to the proper directory
(status, output) = commands.getstatusoutput("mv packet* " \
                                            + dirty_expire_centisecs \
                                            + "_na")
print "Test case 1 completed."

# test case 2:
# with affinity
print "Running test case 2 (with affinity)..."

print "Acquiring data..."
# acquire data and write it to shared memory
(status, output) = commands.getstatusoutput(cmd_affinity \
                                            + dir_commands \
                                            + cmd_acq \
                                            + " " \
                                            + dev \
                                            + " " \
                                            + str(max_runs))

indices = xrange(0, max_runs)
for i in indices:
    print "Checking data set " + str(i) + " for slips...",
    sys.stdout.flush()
    # check for slips
    (status, output) = commands.getstatusoutput(dir_commands \
                                                + cmd_check \
                                                + " packet" \
                                                + str(i) \
                                                + " 4 20 10" \
                                                + " > " \
                                                + dir_reports \
                                                + dirty_expire_centisecs \
                                                + "_wa" \
                                                + "/" \
                                                + wr_check_file_prefix \
                                                + str(i))
    print "DONE"

# move the data files to the proper directory
(status, output) = commands.getstatusoutput("mv packet* " \
                                            + dirty_expire_centisecs \
                                            + "_wa")
print "Test case 2 completed."

print "Resetting the value of vm.dirty_expire_centisecs to the default"
(status, output) = commands.getstatusoutput("sysctl -w " \
                                            + "vm.dirty_expire_centisecs=" \
                                            + "3000")

print "Test completed."


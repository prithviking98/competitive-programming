#!/usr/bin/python

# runraw.py
# Automated test suite for raw socket data acquisition
# Usage: runraw.py
#
# Created by Jayanth Chennamangalam

import sys
import commands

# definitions
max_runs = 20
dir_commands = "~/src/acquire/"
dir_reports = "~/run/reports/"
subdir_reports = "raw/"
subdir_packets = "raw/"
cmd_sanity = "acquire_rawsock_check"
cmd_acq = "acquire_rawsock_shm"
cmd_runboth = "runbothraw"
cmd_check = "long_mark_gap packet 4 20 10"
cmd_rmshm = "rmshm.py"
dev = "eth0"
sanity_file = "sanity"
w_shm_acq_file_prefix = "w_shm_acq_"
wr_shm_acq_file_prefix = "wr_shm_acq_"
wr_shm_hd_file_prefix = "wr_shm_hd_"
wr_shm_check_file_prefix = "wr_shm_check_"
packet_file_prefix = "packet_"

print "Test commencing..."

print "Performing sanity check..."
sys.stdout.flush()
(status, output) = commands.getstatusoutput(dir_commands \
                                            + cmd_sanity \
                                            + " " \
                                            + dev \
                                            + " > " \
                                            + dir_reports \
                                            + subdir_reports \
                                            + sanity_file)
print "Sanity check completed."

print "Performing write to shm test..."
indices = xrange(0, max_runs)
for i in indices:
    print "Run number " + str(i) + "...",
    sys.stdout.flush()

    # acquire data and write it to shared memory
    (status, output) = commands.getstatusoutput(dir_commands \
                                                + cmd_acq \
                                                + " " \
                                                + dev \
                                                + " > " \
                                                + dir_reports \
                                                + subdir_reports \
                                                + w_shm_acq_file_prefix \
                                                + str(i))

    # remove the shared memory segments
    (status, output) = commands.getstatusoutput(dir_commands \
                                                + cmd_rmshm)
    print "DONE"
print "Write to shm test completed."

print "Performing write to and read from shm test..."
indices = xrange(0, max_runs)
for i in indices:
    print "Run number " + str(i) + "...",
    sys.stdout.flush()

    # acquire data and write it to disk
    (status, output) = commands.getstatusoutput(cmd_runboth)

    # rename the stdout files and move them to the proper directory
    (status, output) = commands.getstatusoutput("mv " \
                                                + dir_reports \
                                                + "aout" \
                                                + " " \
                                                + dir_reports \
                                                + subdir_reports \
                                                + wr_shm_acq_file_prefix \
                                                + str(i))
    (status, output) = commands.getstatusoutput("mv " \
                                                + dir_reports \
                                                + "wout" \
                                                + " " \
                                                + dir_reports \
                                                + subdir_reports \
                                                + wr_shm_hd_file_prefix \
                                                + str(i))

    # check for slips
    (status, output) = commands.getstatusoutput(dir_commands \
                                                + cmd_check \
                                                + " > " \
                                                + dir_reports \
                                                + subdir_reports \
                                                + wr_shm_check_file_prefix \
                                                + str(i))

    # rename the packet file and move it to the proper directory
    (status, output) = commands.getstatusoutput("mv packet " \
                                                + subdir_packets \
                                                + packet_file_prefix \
                                                + str(i))

    # remove the shared memory segments
    (status, output) = commands.getstatusoutput(dir_commands \
                                                + cmd_rmshm)
    print "DONE"
print "Write to and read from shm test completed."

print "Test completed."


#!/usr/bin/python

# run.py
# Automated test suite
# Usage: run.py <sampling_rate_in_MHz>
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
samp_rate = sys.argv[1]     # sampling rate chosen, in MHz

# definitions
max_runs = 20
dir_commands = "~/src/acquire/"
dir_reports = "~/run/reports/"
cmd_sanity = "acquire_1056_check"
cmd_acq = "acquire_1056_shm"
cmd_runboth = "runboth"
cmd_check = "long_mark_gap packet 4 20 10"
cmd_rmshm = "rmshm.py"
dev = "eth1"
sanity_file = "sanity"
w_shm_acq_file_prefix = "w_shm_acq_"
wr_shm_acq_file_prefix = "wr_shm_acq_"
wr_shm_hd_file_prefix = "wr_shm_hd_"
wr_shm_check_file_prefix = "wr_shm_check_"
packet_file_prefix = "packet_"

print "Test commencing..."

print "Sampling rate is " + samp_rate + "MHz."

print "Performing sanity check..."
sys.stdout.flush()
(status, output) = commands.getstatusoutput(dir_commands \
                                            + cmd_sanity \
                                            + " " \
                                            + dev \
                                            + " > " \
                                            + dir_reports \
                                            + samp_rate + "mhz/" \
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
                                                + samp_rate + "mhz/" \
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
                                                + samp_rate + "mhz/" \
                                                + wr_shm_acq_file_prefix \
                                                + str(i))
    (status, output) = commands.getstatusoutput("mv " \
                                                + dir_reports \
                                                + "wout" \
                                                + " " \
                                                + dir_reports \
                                                + samp_rate + "mhz/" \
                                                + wr_shm_hd_file_prefix \
                                                + str(i))

    # check for slips
    (status, output) = commands.getstatusoutput(dir_commands \
                                                + cmd_check \
                                                + " > " \
                                                + dir_reports \
                                                + samp_rate + "mhz/" \
                                                + wr_shm_check_file_prefix \
                                                + str(i))

    # rename the packet file and move it to the proper directory
    (status, output) = commands.getstatusoutput("mv packet " \
                                                + samp_rate + "mhz/" \
                                                + packet_file_prefix \
                                                + str(i))

    # remove the shared memory segments
    (status, output) = commands.getstatusoutput(dir_commands \
                                                + cmd_rmshm)
    print "DONE"
print "Write to and read from shm test completed."

print "Test completed."


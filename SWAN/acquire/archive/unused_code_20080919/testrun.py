#!/usr/bin/python

# testrun.py
# Program to test the single-task acquisition program with different parameters
#
# Created by Jayanth Chennamangalam

import commands

# definitions
maxrun = 20

print "Test commencing..."

runindices = xrange(0, maxrun)

# test case 1:
# no affinity
# default vm.dirty_expire_centisecs (3000)
(status, output) = commands.getstatusoutput("sysctl -w " \
                                            + "vm.dirty_expire_centisecs=3000")
(status, output) = commands.getstatusoutput("~/src/acquire/" \
                                            + "oldstuff_other/" \
                                            + "acquire_1056bytes eth0 " \
                                            + str(maxrun))
(status, output) = commands.getstatusoutput("mv packet* nadv");
#for i in runindices:
#    (status, output) = commands.getstatusoutput("~/src/acquire/long_mark_gap " \
#                                                + "packet" \
#                                                + str(i) \
#                                                + " 4 20 10 " \
#                                                + " > nadv_check_out_" \
#                                                + str(i))

# test case 2:
# no affinity
# set vm.dirty_expire_centisecs to 1000
(status, output) = commands.getstatusoutput("sysctl -w " \
                                            + "vm.dirty_expire_centisecs=1000")
(status, output) = commands.getstatusoutput("~/src/acquire/" \
                                            + "oldstuff_other/" \
                                            + "acquire_1056bytes eth0 " \
                                            + str(maxrun))
(status, output) = commands.getstatusoutput("mv packet* namv");
#for i in runindices:
#    (status, output) = commands.getstatusoutput("~/src/acquire/long_mark_gap " \
#                                                + "packet" \
#                                                + " 4 20 10 " \
#                                                + str(i) \
#                                                + " > namv_check_out_" \
#                                                + str(i))

# test case 3:
# with affinity
# default vm.dirty_expire_centisecs (3000)
(status, output) = commands.getstatusoutput("sysctl -w " \
                                            + "vm.dirty_expire_centisecs=3000")
(status, output) = commands.getstatusoutput("taskset 0x00000001 " \
                                            + "~/src/acquire/" \
                                            + "oldstuff_other/" \
                                            + "acquire_1056bytes eth0 " \
                                            + str(maxrun))
(status, output) = commands.getstatusoutput("mv packet* wadv");
#for i in runindices:
#    (status, output) = commands.getstatusoutput("~/src/acquire/long_mark_gap " \
#                                                + "packet" \
#                                                + str(i) \
#                                                + " 4 20 10 " \
#                                                + " > wadv_check_out_" \
#                                                + str(i))

# test case 4:
# with affinity
# set vm.dirty_expire_centisecs to 1000
(status, output) = commands.getstatusoutput("sysctl -w " \
                                            + "vm.dirty_expire_centisecs=1000")
(status, output) = commands.getstatusoutput("taskset 0x00000001 " \
                                            + "~/src/acquire/" \
                                            + "oldstuff_other/" \
                                            + "acquire_1056bytes eth0 " \
                                            + str(maxrun))
(status, output) = commands.getstatusoutput("mv packet* wamv");
#for i in runindices:
#    (status, output) = commands.getstatusoutput("~/src/acquire/long_mark_gap " \
#                                                + "packet" \
#                                                + str(i) \
#                                                + " 4 20 10 " \
#                                                + " > wamv_check_out_" \
#                                                + str(i))

print "Test completed."

# resetting vm.dirty_expire_centisecs to default value (3000)
(status, output) = commands.getstatusoutput("sysctl -w " \
                                            + "vm.dirty_expire_centisecs=3000")


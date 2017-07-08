# hwfwinfo
Bachelor degree thesis in Computer Science and Engineering at University of Cesena [UNIBO]. Linux tool developed to check firmware and hardware alterations.

Usage: hwfwinfo [OPTIONS]
Options are:
-h,				Display all possible commands
-hw,				Display all infos about BIOS, Graphic Cards, Hard Disks, RAM and Network Cards installed on your system
-hw -l,				Generate a log under /var/log/hwfwinfo/HW with infos BIOS, Graphic Cards, Hard Disks, RAM and Network Cards installed on your system
-hw -l 'Path',			Generate a log under the path specified with infos BIOS, Graphic Cards, Hard Disks, RAM and Network Cards installed on your system
-hw -c,		  		Check your system infos with logged infos under /var/log/hwinfo/HW/
-hw -c -n,		  	Check your system infos with logged infos under /var/log/hwinfo/HW/, the -n param specifies the revision number to use
-hw -c 'Path',		  	Check your system infos with logged infos under the directory specified
-hw -c 'Path' -n ,		Check your system infos with logged infos under the directory specified, the -n param specifies the revision number
-fw,				Display all infos about FW installed under your /lib/firmware/ directory
-fw -l,				Generate a log under /var/log/hwfwinfo/FW with infos about your current firmwares
-fw -l 'Path',			Generate a log under the path specified with infos about your current firmwares
-fw -c,				Check your current firmware infos with logged infos under /var/log/hwfwinfo/FW
-fw -c 'Path',			Check your current firmware infos with a firmware log

# hwfwinfo
Bachelor degree thesis in Computer Science and Engineering at University of Cesena [UNIBO]. Linux tool developed to check firmware and hardware alterations. <br>

Usage: hwfwinfo [OPTIONS] <br>
Options are: <br>
-h,				Display all possible commands <br>
-hw,				Display all infos about BIOS, Graphic Cards, Hard Disks, RAM and Network Cards installed on your system <br>
-hw -l,				Generate a log under /var/log/hwfwinfo/HW with infos BIOS, Graphic Cards, Hard Disks, RAM and Network Cards installed on your system <br>
-hw -l 'Path',			Generate a log under the path specified with infos BIOS, Graphic Cards, Hard Disks, RAM and Network Cards installed on your system <br>
-hw -c,		  		Check your system infos with logged infos under /var/log/hwinfo/HW/ <br>
-hw -c -n,		  	Check your system infos with logged infos under /var/log/hwinfo/HW/, the -n param specifies the revision number to use <br>
-hw -c 'Path',		  	Check your system infos with logged infos under the directory specified <br>
-hw -c 'Path' -n ,		Check your system infos with logged infos under the directory specified, the -n param specifies the revision number <br>
-fw,				Display all infos about FW installed under your /lib/firmware/ directory <br>
-fw -l,				Generate a log under /var/log/hwfwinfo/FW with infos about your current firmwares <br>
-fw -l 'Path',			Generate a log under the path specified with infos about your current firmwares <br>
-fw -c,				Check your current firmware infos with logged infos under /var/log/hwfwinfo/FW <br>
-fw -c 'Path',			Check your current firmware infos with a firmware log <br>

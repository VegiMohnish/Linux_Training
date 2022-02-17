cmd_/home/ignitarium/Linux_Training/mutex/modules.order := {   echo /home/ignitarium/Linux_Training/mutex/mutex.ko; :; } | awk '!x[$$0]++' - > /home/ignitarium/Linux_Training/mutex/modules.order

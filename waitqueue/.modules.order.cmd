cmd_/home/ignitarium/Linux_Training/waitqueue/modules.order := {   echo /home/ignitarium/Linux_Training/waitqueue/waitqueue.ko; :; } | awk '!x[$$0]++' - > /home/ignitarium/Linux_Training/waitqueue/modules.order

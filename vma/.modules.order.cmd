cmd_/home/ignitarium/Linux_Training/vma/modules.order := {   echo /home/ignitarium/Linux_Training/vma/vma.ko; :; } | awk '!x[$$0]++' - > /home/ignitarium/Linux_Training/vma/modules.order

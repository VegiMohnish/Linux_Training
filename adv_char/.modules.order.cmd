cmd_/home/ignitarium/Linux_Training/adv_char/modules.order := {   echo /home/ignitarium/Linux_Training/adv_char/ioctl_driver.ko; :; } | awk '!x[$$0]++' - > /home/ignitarium/Linux_Training/adv_char/modules.order

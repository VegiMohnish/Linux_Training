cmd_/home/ignitarium/Linux_Training/char_driver/modules.order := {   echo /home/ignitarium/Linux_Training/char_driver/char_driver.ko; :; } | awk '!x[$$0]++' - > /home/ignitarium/Linux_Training/char_driver/modules.order
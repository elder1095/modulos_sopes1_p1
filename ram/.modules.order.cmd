cmd_/home/elder/modules/ram/modules.order := {   echo /home/elder/modules/ram/ram.ko; :; } | awk '!x[$$0]++' - > /home/elder/modules/ram/modules.order

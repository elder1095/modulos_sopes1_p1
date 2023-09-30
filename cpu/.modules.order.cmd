cmd_/home/elder/modules/cpu/modules.order := {   echo /home/elder/modules/cpu/cpu.ko; :; } | awk '!x[$$0]++' - > /home/elder/modules/cpu/modules.order

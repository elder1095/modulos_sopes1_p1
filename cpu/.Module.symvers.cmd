cmd_/home/elder/modules/cpu/Module.symvers := sed 's/\.ko$$/\.o/' /home/elder/modules/cpu/modules.order | scripts/mod/modpost -m -a  -o /home/elder/modules/cpu/Module.symvers -e -i Module.symvers   -T -

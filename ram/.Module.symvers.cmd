cmd_/home/elder/modules/ram/Module.symvers := sed 's/\.ko$$/\.o/' /home/elder/modules/ram/modules.order | scripts/mod/modpost -m -a  -o /home/elder/modules/ram/Module.symvers -e -i Module.symvers   -T -
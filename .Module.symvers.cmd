cmd_/home/cs111/lab0/Module.symvers := sed 's/\.ko$$/\.o/' /home/cs111/lab0/modules.order | scripts/mod/modpost  -a  -o /home/cs111/lab0/Module.symvers -e -i Module.symvers  -N -T -

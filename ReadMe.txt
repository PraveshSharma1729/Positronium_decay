#Put all the .cc file in new directory named src & put all the .hh files in new directory named include
#First source the Geant .sh file

#create folder named build
$mkdir build

# Go inside that folder
$cd mkdir

#Do Cmake
$cmake ..

#Do make 
$make 

#run simulation
$./sim

##### HOW TO COMPILE  #########
1. install the dependencies using these command on Ubuntu:

sudo apt-get install build-essential
sudo apt-get install libsdl2-dev libsdl2-image-dev

On OSX you can use these commands after installing Homebrew:

brew install sdl2 sdl2_image

2. After being in the path of the source code, run:

make all 

3. To delete all the files built:

make clean

###### WHAT IS NEW IN THIS VERSION  #######

for each object type only one sprite is created. too many sprites was leading to crush because they were destroyed with the object but the reference/pointer was still in used by the engine.

###### NEED TO BE FIXED  ########


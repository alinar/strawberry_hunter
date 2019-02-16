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


###### NEED TO BE FIXED  ########

static lists should be used in a lock protected wrapper. One way is to wrap it in a class with protected reader/modifiers.

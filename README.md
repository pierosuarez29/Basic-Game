# Basic-Game
Vintage Arcade in C++

Hello, here you have some C++ code.
It was my final project for a university course, and I completed it with some partners.

Well, it's quite basic, but I did try to use threads for the first time. I think it's cool.
This code includes music for each game, so there is music in the game's menu.
However, if you want to hear it and use the threads, you have to follow some steps.

There are exactly two steps:

1. Navigate to your compiler settings.
2. In the linker section, paste the following two options: -lwinmm -lpthread

-lwinmm: This is for handling sounds.
-lpthread: Enables the use of threads.

Finally, compile and execute the file named 'main'; everything is linked to 'main'.

I recommend maximizing the execution console for a better experience and to avoid bugs. 
At the moment, only the main menu has threads activated; however, 
I will be gradually implementing threads throughout the entire project and fixing some bugs. 

Thanks for visiting! :D

#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <cmath>

int main(int argc, char *argv[]){
  WPPMAT001::FrameSequence image;
  int xs = std::stoi(argv[3]);//reading start and end points
  int ys = std::stoi(argv[4]);
  int xe = std::stoi(argv[5]);
  int ye = std::stoi(argv[6]);
  int frameheight = std::stoi(argv[8]);//frame dimensions
  int framewidth  = std::stoi(argv[9]);
  

  std::string imagefilename;
  imagefilename = argv[1];
  image.read(imagefilename,xs,ys,xe,ye,frameheight,framewidth);

    
   int arg = 10;
   /*
   std::string w = argv[++arg];
      while(w == "-w"){
         std::string option = argv[++arg];
         
         if(option == "none"){
            image.write(frameheight,framewidth);
            std::string filename = argv[++arg];
          
         }
         else if(option == "reverse"){
            image.reverse(frameheight,framewidth);
            std::string filename = argv[++arg];
          
         }
         
         else if(option == "invert"){
            image.invert(frameheight,framewidth);
            std::string filename = argv[++arg];
          
         }
         
         else if(option == "reinvert"){
            image.invert(frameheight,framewidth);
            std::string filename = argv[++arg];
          
         }
         
         w =  w = argv[++arg];
          
      }
      */
  
   return 0;

}
#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <cmath>

int main(int argc, char *argv[]){
  WPPMAT001::FrameSequence image;
  int xs;
  int ys;
  int xe;
  int ye;
  int frameheight;
  int framewidth;
  int arg = 0;
  std::string imagefilename;
  if(argc>1){
   imagefilename = argv[++arg];
   std:: string t = argv[++arg];
 
   if(t == "-t"){
      xs = std::stoi(argv[++arg]);
      ys = std::stoi(argv[++arg]);
      
      xe = std::stoi(argv[++arg]);
      ye = std::stoi(argv[++arg]);
   
   }
   
   std::string s = argv[++arg];
   if(s == "-s"){
      frameheight = std::stoi(argv[++arg]);
      framewidth = std::stoi(argv[++arg]);
      
   }
   std::cout<<imagefilename<<std::endl<<xs<<std::endl<<ys<<std::endl<<xe<<std::endl<<ye<<std::endl;
   image.read(imagefilename,xs,ys,xe,ye,frameheight,framewidth);
   
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
  }
  
   return 0;

}
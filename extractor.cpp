#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
//used to store frame writing options
struct options {
    std::string operation;
    std::string name;
};
int main(int argc, char *argv[]){
  WPPMAT001::FrameSequence image;
  int xs = std::stoi(argv[3]);//reading start and end points
  int ys = std::stoi(argv[4]);
  int xe = std::stoi(argv[5]);
  int ye = std::stoi(argv[6]);
  int frameheight = std::stoi(argv[8]);//frame dimensions
  int framewidth  = std::stoi(argv[9]);
  
  std::vector<options> frameOptions;

  std::string imagefilename;
  imagefilename = argv[1];
  image.read(imagefilename,xs,ys,xe,ye,frameheight,framewidth);//creating frames along trajectory
  
  //collecting all the frame operations into a vector
  for(int i=10;i<argc; i++){
   options frame;
   frame.operation = argv[++i];
   frame.name = argv[++i];
   frameOptions.push_back(frame);
   }

   //applying each operation to frames
   //TO-DO: write an apply function to eleminate the need for "if" and else statements 
    for (const auto& frame : frameOptions) {
       if (frame.operation == "none"){
            image.write(frameheight,framewidth,frame.name);
       }

       else if (frame.operation == "reverse"){
            image.reverse(frameheight,framewidth,frame.name);
       }

       else if (frame.operation == "invert"){
            image.invert(frameheight,framewidth,frame.name);
       }

       else if (frame.operation == "reverse_invert"){
            image.reverse_invert(frameheight,framewidth,frame.name);
       }

    }

  
   return 0;

}
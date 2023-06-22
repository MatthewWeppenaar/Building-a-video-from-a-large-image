#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
//used to store frame writing options
struct options {
    std::string operation;
    std::string name;
};
int main(int argc, char *argv[]){
  WPPMAT001::FrameSequence image;
  std::cout<<argv[2]<<std::endl;
  
  //finding the indexes of '-s' and '-w' in argv
  int dimensions = -1;
  int operations = -1;

for (int i = 0; i < argc; i++) {
    if (std::string(argv[i]) == "-s") {
        dimensions = i;
    } else if (std::string(argv[i]) == "-w") {
        operations = i;
        i+= argc;//to ensure that only the first '-w' is stored
    }
}

  int frameheight = std::stoi(argv[dimensions+1]);//frame dimensions
  int framewidth  = std::stoi(argv[dimensions+2]);
  
  std::vector<options> frameOptions;

  std::string imagefilename;
  imagefilename = argv[1];
  //reading in the input image data
  image.read(imagefilename);
  //single point trajectory
  if(std::string(argv[2]) == "-t"){
   int xs = std::stoi(argv[3]);//reading start and end points
   int ys = std::stoi(argv[4]);
   int xe = std::stoi(argv[5]);
   int ye = std::stoi(argv[6]);
   std::vector<WPPMAT001::origion_coords> coords= image.generate_trajectory(xs,ys,xe,ye);
   //creating frames along trajectory
   image.generate_frame_sequence(frameheight,framewidth,coords);
  }
  else if(std::string(argv[2]) == "-p"){
   std::vector<WPPMAT001::origion_coords> coords;
   int num_points = std::stoi(argv[3]);
   for(int i = 4; i<2+ num_points *2;i+=2){
      std::vector<WPPMAT001::origion_coords> coords1 = image.generate_trajectory(std::stoi(argv[i]),std::stoi(argv[i+1]),std::stoi(argv[i+2]),std::stoi(argv[i+3]));
      coords.insert(coords.end(), coords1.begin(), coords1.end());
   }
   
   image.generate_frame_sequence(frameheight,framewidth,coords);
  }
  std::cout << image.size() << std::endl;
  //collecting all the frame operations into a vector
  for(int i=operations;i<argc; i++){
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
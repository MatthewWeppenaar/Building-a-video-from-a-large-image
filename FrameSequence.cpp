#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <cmath>

void WPPMAT001::FrameSequence::add(unsigned char ** test){imageSequence.push_back(test);}
int WPPMAT001::FrameSequence:: size(){return imageSequence.size();}
unsigned char** WPPMAT001::FrameSequence::getFrame(int frame){return imageSequence[frame];}
std::vector<unsigned char **> WPPMAT001::FrameSequence::getSequence(){return imageSequence;}
void WPPMAT001::FrameSequence::read(std::string filename, int xorigion, int yorigion, int xfinal, int yfinal, int fheight, int fwidth){
   std::cout<<"read"<<std::endl;
   int xstart = xorigion;
   int xend = xfinal;
   int ystart = yorigion;
   int yend = yfinal;
   std::vector<WPPMAT001::origion_coords> coords;
   //trajectory calculation
   float g = float(yend-ystart)/float(xend-xstart);
   WPPMAT001::origion_coords coord;
   if (std::fabs(g)  < 1.0){ 
   
   
   
   if(xend>xstart){
   float y = ystart;
   coord.xcoord = xstart;
   coord.ycoord = y;
   //coords.push_back(coord);
   for (int x=xstart; x <= xend; ++x){
      y = y + g; 
      coord.xcoord = x;
      coord.ycoord = std::round(y);
      coords.push_back(coord);
      }   
   }
   else{ 
      float y = ystart;
      coord.xcoord = xstart;
      coord.ycoord = y;
      //coords.push_back(coord);
      for (int x=xstart-1; x >= xend; --x){
         y = y + g;
         coord.xcoord = x;
         coord.ycoord = std::round(y);
         coords.push_back(coord);
      } 
      }
   }
   
   //opening file
   std::ifstream infile(filename, std::ios::binary);
   if (!infile) {
        std::cerr << "Error opening file" << std::endl;
    }
    std::string magic;
    int width, height, maxval;
    infile >> magic >> width >> height >> maxval;
    if (magic != "P5" || maxval > 255) {
        std::cerr << "Invalid pgm format" << std::endl;
    }
    //reading file into 2d unsigned array
   infile.ignore(1, '\n'); 
   unsigned char ** two_pointer;
   two_pointer = new unsigned char * [width];
      for(int j = 0;j<height;j++){
         two_pointer[j] = new unsigned  char[height];
         for(int k = 0;k<width;k++){
            infile.read((char*)&two_pointer[j][k], 1);
         }
    }
    infile.close();
   //creating frames using coordinates and adding to image sequence
   std::cout<<coords.size()<<std::endl;
   for(int i = 0 ; i<coords.size(); i++){
      int y = coords[i].ycoord;
      unsigned char **  frame = new unsigned char * [fheight];
         //std::cout<<x<<' '<<y<<std::endl;        
         for(int j = 0; j<fheight;j++){
            int x = coords[i].xcoord;
            frame[j] = new unsigned char [fwidth];
            for(int k = 0;k<fwidth;k++){
               
               frame[j][k] = two_pointer[y][x];
               x++;
            }
            y++; 
            
         
         }
         imageSequence.push_back(frame);         
      }
//dealocating memoory from big image    
for(int i = 0; i < width; ++i){
		delete [] two_pointer[i];
	   }
      delete [] two_pointer;
          
}

void WPPMAT001::FrameSequence:: write(int height, int width){
   std::cout<<"none"<<std::endl;
   //writing frames unchanged 
   for(int i = 0; i<imageSequence.size();i++){
      std::string filename1 = "out/"+std::to_string(i)+"test.pgm";
      std::ofstream out(filename1, std::ofstream::binary);
      out<<"P5\n";
      out<< width<<" "<<height <<"\n";
      out<< 255 <<"\n";
      for(int l = 0;l<height;l++){
       out.write((char *)imageSequence[i][l],width);
      }
      out.close();
   }
}
void WPPMAT001::FrameSequence:: reverse(int height, int width){
   std::cout<<"reverse"<<std::endl;
   for(int i = 0; i<imageSequence.size();i++){
      std::string filename1 = "out/"+std::to_string(i)+ "reverse_test.pgm";
      std::ofstream out(filename1, std::ofstream::binary);
      out<<"P5\n";
      out<< width<<" "<<height <<"\n";
      out<< 255 <<"\n";
      for (int k = height-1; k>=0 ; k--)
      
        {
         for(int j = width-1;j>=0;j--){
            unsigned char  ptr = getFrame(i)[k][j];
            unsigned char* ptr2 = &(ptr);
            out.write((char*)ptr2, 1);
            }
        }
         
      out.close();
   }

}

void WPPMAT001::FrameSequence:: invert(int height, int width){
   std::cout<<"invert"<<std::endl;
   for(int i = 0; i<imageSequence.size();i++){
      std::string filename1 = "out/"+std::to_string(i)+ "invert_test.pgm";
      std::ofstream out(filename1, std::ofstream::binary);
      out<<"P5\n";
      out<< width<<" "<<height <<"\n";
      out<< 255 <<"\n";
      for (int k = 0; k <height ; k++)
      
        {
         for(int j = 0;j<width;j++){
            unsigned char  ptr = 255-imageSequence[i][k][j];
            unsigned char* ptr2 = &(ptr);
            out.write((char*)ptr2, 1);
            }
        }
         
      out.close();
   }
}


void WPPMAT001::FrameSequence:: reverse_invert(int height, int width){
  std::cout<<"reverse_invert"<<std::endl;
  for(int i = 0; i<imageSequence.size();i++){
      std::string filename1 = "out/"+std::to_string(i)+ "reverse_invert_test.pgm";
      std::ofstream out(filename1, std::ofstream::binary);
      out<<"P5\n";
      out<< width<<" "<<height <<"\n";
      out<< 255 <<"\n";
      for (int k = height-1; k>=0 ; k--)
      
        {
         for(int j = width-1;j>=0;j--){
            unsigned char  ptr = 255-getFrame(i)[k][j];
            unsigned char* ptr2 = &(ptr);
            out.write((char*)ptr2, 1);
            }
        }
         
      out.close();
   }


}


WPPMAT001::FrameSequence::FrameSequence(){};

WPPMAT001::FrameSequence::~FrameSequence(){
   for(int i = 0;i <imageSequence.size()-1;i++){
      if(imageSequence[i] != nullptr){
       for(int j = 0 ;j<640;j++){
          delete [] imageSequence[j];
      }
      delete[] imageSequence[i];
   }
  }
};    
   

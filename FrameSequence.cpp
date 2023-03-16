#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <cmath>

void WPPMAT001::FrameSequence::add(unsigned char ** test){imageSequence.push_back(test);}
int WPPMAT001::FrameSequence:: size(){return imageSequence.size();}
unsigned char** WPPMAT001::FrameSequence::getFrame(int frame){return imageSequence[frame];}
std::vector<unsigned char **> WPPMAT001::FrameSequence::getSequence(){return imageSequence;}
void WPPMAT001::FrameSequence::read(std::string filename, int xorigion, int yorigion, int xfinal, int yfinal, int fheight, int fwidth){
   int xstart = xorigion;
   int xend = xfinal;
   int ystart = yorigion;
   int yend = yfinal;
   std::vector<WPPMAT001::origion_coords> coords;
   
   float g = float(yend-ystart)/float(xend-xstart);
   WPPMAT001::origion_coords coord;
   if (std::fabs(g)  < 1.0){ 
   if(xend>xstart){
   float y = ystart;
   coord.xcoord = xstart;
   coord.ycoord = y;
   coords.push_back(coord);
   for (int x=xstart+1; x <= xend; ++x){
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
      coords.push_back(coord);
      for (int x=xstart-1; x >= xend; --x){
         y = y + g;
         coord.xcoord = x;
         coord.ycoord = std::round(y);
         coords.push_back(coord);
      } 
      }
   }
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
     //std::string filename1 ="test_sloan.pgm";
      //std::ofstream out(filename1, std::ofstream::binary);
     // out<<"P5\n";
      //out<< 480<<" "<<640 <<"\n";
      //out<< 255 <<"\n";
    //for (int j = 0; j < 640 ; j++)
      
        //{
         //for(int k = 0;k<480;k++){
         //out.write((char*)&two_pointer[j][k], 1);
         //unsigned char* ptr = &(two_pointer[j][k]) ;
            //if (i<10){&
              // std::cout<<two_pointer[i][i]<<std::endl;
            //}
           //out.write((char*)ptr, 1);
            //}
       //}
     //out.close();

    
    
   //unsigned char **  frame = new unsigned char *[640];
   
   for(int i = 0 ; i<coords.size(); i++){
      //unsigned char ** frame = nullptr;
      
      int y = coords[i].ycoord;
       unsigned char **  frame = new unsigned char * [640];
         //std::cout<<x<<' '<<y<<std::endl;        
         for(int j = 0; j<640;j++){
            int x = coords[i].xcoord;
            frame[j] = new unsigned char [480];
            for(int k = 0;k<480;k++){
               
               frame[j][k] = two_pointer[y][x];
               x++;
            }
            y++; 
         
         
         }
         //std::cout<<imageSequence.size()<<std::endl;
         imageSequence.push_back(frame);
      //std::string filename1 = std::to_string(i)+"test.pgm";
      //std::ofstream out(filename1, std::ofstream::binary);
      //out<<"P5\n";
      //out<< 480<<" "<<640 <<"\n";
      //out<< 255 <<"\n";
      
      //for(int l = 0;l<640;l++){
       //out.write((char *)imageSequence[i][l],480);
      //}
     //unsigned char ** printSequence = images.getFrame(i);
      /*for (int k = 0; k < 480 ; k++){
         for(int j = 0;j<640;j++){
         unsigned char* ptr = &([k][j]) ;
            //if (i<10){&
              // std::cout<<two_pointer[i][i]<<std::endl;
            //}
           out.write((char*)frame[j], 480);
            }
       //}*/
         
      //out.close();
   
   


}
for(int i = 0; i < width; ++i){
		delete [] two_pointer[i];
	   }
      delete [] two_pointer;
          
}

void WPPMAT001::FrameSequence:: write(){
   for(int i = 0; i<imageSequence.size();i++){
     std::string filename1 = std::to_string(i)+"test.pgm";
      std::ofstream out(filename1, std::ofstream::binary);
      out<<"P5\n";
      out<< 480<<" "<<640 <<"\n";
      out<< 255 <<"\n";
      for(int l = 0;l<640;l++){
       out.write((char *)imageSequence[i][l],480);
      }
      out.close();
   }
}
void WPPMAT001::FrameSequence:: reverse(){
   for(int i = 0; i<imageSequence.size();i++){
     std::string filename1 = std::to_string(i)+"reverse_test.pgm";
      std::ofstream out(filename1, std::ofstream::binary);
      out<<"P5\n";
      out<< 480<<" "<<640 <<"\n";
      out<< 255 <<"\n";
      
      for(int l = 640;l>0;l--){
       out.write((char *)imageSequence[i][l],480);
      }
         
      out.close();
}


}

void WPPMAT001::FrameSequence:: invert(){
   //for(int i = 0; i<imageSequence.size();i++){
     //std::string filename1 = std::to_string(i)+"test.pgm";
     /// std::ofstream out(filename1, std::ofstream::binary);
      //out<<"P5\n";
      //out<< 480<<" "<<640 <<"\n";
      ///out<< 255 <<"\n";
      //for(int l = 0;l<640;l++){
       //out.write((char *)imageSequence[i][l],480);
      //}
      //out.close();
   //}
   
   for(int i = 0; i<imageSequence.size();i++){
      std::string filename1 =std::to_string(i)+ "invert_test.pgm";
      std::ofstream out(filename1, std::ofstream::binary);
      out<<"P5\n";
      out<< 480<<" "<<640 <<"\n";
      out<< 255 <<"\n";
      //unsigned char ** printSequence = images.getFrame(i);
      for (int k = 0; k <640 ; k++)
      
        {
         for(int j = 0;j<480;j++){
         unsigned char  ptr = 255-imageSequence[i][k][j];
         unsigned char* ptr2 = &(ptr);
         //ptr = &two_pointer[i][j];
            //if (i<10){
              // std::cout<<two_pointer[i][i]<<std::endl;
            //}
            out.write((char*)ptr2, 1);
            }
        }
         
      out.close();
   }
   
   
   
}


void WPPMAT001::FrameSequence:: reverse_invert(){
   for(int i = 0; i<imageSequence.size();i++){
      std::string filename1 =std::to_string(i)+ "test.pgm";
      std::ofstream out(filename1, std::ofstream::binary);
      out<<"P5\n";
      out<< 480<<" "<<640 <<"\n";
      out<< 255 <<"\n";
      //unsigned char ** printSequence = images.getFrame(i);
      for (int k = 480; k >0 ; k--)
      
        {
         for(int j = 640;j>0;j--){
         unsigned char  ptr = 255-imageSequence[i][k][j];
         unsigned char* ptr2 = &(ptr);
         //ptr = &two_pointer[i][j];
            //if (i<10){
              // std::cout<<two_pointer[i][i]<<std::endl;
            //}
            out.write((char*)ptr2, 1);
            }
        }
         
      out.close();
   }


}


WPPMAT001::FrameSequence::FrameSequence(){};
WPPMAT001::FrameSequence::~FrameSequence(){
   for(int i = 0;i <imageSequence.size();i++){
      if(imageSequence[i] != nullptr){
       for(int j = 0 ;j<640;j++){
          delete [] imageSequence[i];
      }
      //delete[] imageSequence;
   }
  }
};    
   

#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <filesystem>
void WPPMAT001::FrameSequence::add(unsigned char ** test){imageSequence.push_back(test);}
int WPPMAT001::FrameSequence:: size(){return imageSequence.size();}
unsigned char** WPPMAT001::FrameSequence::getFrame(int frame){return imageSequence[frame];}
std::vector<unsigned char **> WPPMAT001::FrameSequence::getSequence(){return imageSequence;}
void WPPMAT001::FrameSequence::read(std::string filename){
  std::cout << "read" << std::endl;
//opening file
std::ifstream infile(filename, std::ios::binary);
if (!infile) {
    std::cerr << "Error opening file" << std::endl;
}

std::string magic;
int width, height, maxval;
infile >> magic >> width >> height >> maxval;
imageHeight = height;
imageWidth = width;

if (magic != "P5" || maxval > 255) {
    std::cerr << "Invalid pgm format" << std::endl;
}

infile.ignore(1, '\n');
//unsigned char** two_pointer;
//Allocating space for input image- height, then width
image = new unsigned char* [height]; 

for (int j = 0; j < height; j++) { 
    image[j] = new unsigned char[width];
    for (int k = 0; k < width; k++) { 
        infile.read((char*)&image[j][k], 1);//assigning pixel value to pointer address
    }
}
infile.close();
}

void WPPMAT001::FrameSequence::deleteImage(){
   //deleating space allocated for large image
   
   for (int i = 0; i < imageHeight; ++i) { 
      delete[] image[i];
   }
   delete[] image;
}

std::vector<WPPMAT001::origion_coords> WPPMAT001::FrameSequence::generate_trajectory(int xorigion, int yorigion, int xend, int yend){
int xstart = xorigion;
//int xend = xend;
int ystart = yorigion;
//int yend = yend;
float g = float(yend - ystart) / float(xend - xstart);
std::vector<WPPMAT001::origion_coords> coords;
WPPMAT001::origion_coords coord;
//Vertical trajectory
if(xend == xstart){
   if(yend>ystart){
   for (int i = ystart;i<yend;i++){
         coord.xcoord = 0;
         coord.ycoord = std::round(i);
         coords.push_back(coord);
      }
   }
   else{
      for (int i = ystart;i>yend;i--){
         coord.xcoord = 0;
         coord.ycoord = std::round(i);
         coords.push_back(coord);
      }
   }
}
//positive diagonal trajectory
if (g > 0) {
    if (xend > xstart) {
        float y = ystart;
        coord.xcoord = xstart;
        coord.ycoord = y;
        for (int x = xstart; x <= xend; ++x) {
            y = y + g;
            coord.xcoord = x;
            coord.ycoord = std::round(y);
            coords.push_back(coord);
        }
    }
    else {
        if(xend!=xstart){
        float y = ystart;
        coord.xcoord = xstart;
        coord.ycoord = y;
        for (int x = xstart-1; x >= xend; --x) {
            y = y - g;
            coord.xcoord = x;
            coord.ycoord = std::round(y);
            coords.push_back(coord); 
         }
      }
   }
}
//negative diagonal trajectory
else if(g<0){
   if(xend!=xstart){
   if(xend<xstart){
        float y = ystart;
        coord.xcoord = xstart;
        coord.ycoord = y;
        for (int x = xstart; x > xend; --x) {
            y = y - g;
            coord.xcoord = x;
            coord.ycoord = std::round(y);
            std::cout << coord.ycoord << std::endl;
            coords.push_back(coord); 
         }
   }
   else{
      float y = ystart;
      coord.xcoord = xstart;
      coord.ycoord = y;
      for (int x = xstart; x < xend; ++x) {
            y = y + g;
            coord.xcoord = x;
            coord.ycoord = std::round(y);
            coords.push_back(coord); 
         }
   }
   }
}
else{
   //horizontal line
      if(xstart<xend){
       for (int i = xstart;i<xend;i++){
         coord.ycoord = 0;
         coord.xcoord = std::round(i);
         coords.push_back(coord);
         }
      }
      else{
        for (int i = xstart;i>xend;i--){
         coord.ycoord = 0;
         coord.xcoord = std::round(i);
         coords.push_back(coord);
         } 
      }
}

return coords;
}

void WPPMAT001::FrameSequence::generate_frame_sequence(int height, int width, std::vector<origion_coords> coords){
  for (int i = 0; i < coords.size(); i++) {
        int y = coords[i].ycoord;
        if (y >= 0 && y + height <= imageHeight) {  // Check y-coordinate bounds, ignore if out of bounds
            unsigned char** frame = new unsigned char*[height];
            for (int j = 0; j < height; j++) {
                int x = coords[i].xcoord;
                if (x >= 0 && x + width <= imageWidth) {  // Check x-coordinate bounds,ignore if out of bounds
                    frame[j] = new unsigned char[width];
                    for (int k = 0; k < width; k++) {
                        frame[j][k] = image[y][x];
                        x++;
                    }
                    y++;
                }
            }
            imageSequence.push_back(frame);
        } 
    }
    create_output_file();   
    //deallocating memory from big image
    deleteImage();
}

void WPPMAT001::FrameSequence::create_output_file(){
   namespace fs = std::filesystem;
   std::string folderPath = "out";

    // Check if the directory exists
    if (!fs::exists(folderPath)) {
        // Create the directory if it doesn't exist
        if (fs::create_directory(folderPath)) {
            std::cout << "Directory created: " << folderPath << std::endl;
        } else {
            std::cout << "Failed to create directory: " << folderPath << std::endl;
        }
    } else {
        std::cout << "Directory already exists: " << folderPath << std::endl;
    }
}

void WPPMAT001::FrameSequence::write(int height, int width, std::string fileName)
{
std::cout << "none" << std::endl;
// writing frames unchanged
for (int i = 0; i < imageSequence.size(); i++)
{
    std::string str = std::to_string(i);
    size_t n = 4;
    std::ostringstream ss;
    ss << std::setw(n) << std::setfill('0') << str;
    std::string s = ss.str();
    std::string filename1 = "out/" + fileName + "-" + s + ".pgm";
    std::ofstream out(filename1, std::ofstream::binary);
    out << "P5\n";
    out << width << " " << height << "\n";
    out << 255 << "\n";
    for (int l = 0; l < height; l++)
    {
        out.write((char *)imageSequence[i][l], width);
    }
    out.close();
}
}
void WPPMAT001::FrameSequence:: reverse(int height, int width,std::string fileName){
   std::cout<<"reverse"<<std::endl;
   for(int i = imageSequence.size()-1; i>=0;i--){
      std::string str = std::to_string(imageSequence.size()-i);
      size_t n = 4;
      std::ostringstream ss;
      ss << std::setw(n) << std::setfill('0') << str;
      std::string s = ss.str();
      std::string filename1 = "out/"+fileName+"-"+s+".pgm";
      std::ofstream out(filename1, std::ofstream::binary);
      out<<"P5\n";
      out<< width<<" "<<height <<"\n";
      out<< 255 <<"\n";
      for (int k = 0; k<height ; k++)
      
        {
         for(int j = 0;j<width;j++){
            unsigned char  ptr = getFrame(i)[k][j];
            unsigned char* ptr2 = &(ptr);
            out.write((char*)ptr2, 1);
            }
        }
         
      out.close();
   }

}

void WPPMAT001::FrameSequence:: invert(int height, int width,std::string fileName){
   std::cout<<"invert"<<std::endl;
   for(int i = 0; i<imageSequence.size();i++){
      std::string str = std::to_string(i);
      size_t n = 4;
      std::ostringstream ss;
      ss << std::setw(n) << std::setfill('0') << str;
      std::string s = ss.str();
      std::string filename1 = "out/"+fileName+"-"+s+".pgm";
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


void WPPMAT001::FrameSequence:: reverse_invert(int height, int width,std::string fileName){
  std::cout<<"reverse_invert"<<std::endl;
  for(int i = imageSequence.size()-1; i>=0;i--){
      std::string str = std::to_string(imageSequence.size()-i);
      size_t n = 4;
      std::ostringstream ss;
      ss << std::setw(n) << std::setfill('0') << str;
      std::string s = ss.str();
      std::string filename1 = "out/"+fileName+"-"+s+".pgm";
      std::ofstream out(filename1, std::ofstream::binary);
      out<<"P5\n";
      out<< width<<" "<<height <<"\n";
      out<< 255 <<"\n";
      for (int k = 0; k<height ; k++)
      
        {
         for(int j = 0;j<width;j++){
            unsigned char  ptr = 255-getFrame(i)[k][j];
            unsigned char* ptr2 = &(ptr);
            out.write((char*)ptr2, 1);
            }
        }
         
      out.close();
   }

}

WPPMAT001::FrameSequence::FrameSequence(){};

WPPMAT001::FrameSequence::~FrameSequence() {
   int fheight = sizeof(imageSequence[0])/sizeof(imageSequence[0][0]); //getting height of image
    for (int i = 0; i < imageSequence.size(); i++) {
        if (imageSequence[i] != nullptr) {//checking if array of image is not null
            for (int j = 0; j < fheight; j++) { 
                delete[] imageSequence[i][j];
            }
            delete[] imageSequence[i];
        }
    }
};  
   

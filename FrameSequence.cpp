#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <cmath>

void WPPMAT001::FrameSequence::add(unsigned char ** test){imageSequence.push_back(test);}
int WPPMAT001::FrameSequence:: size(){return imageSequence.size();}
unsigned char** WPPMAT001::FrameSequence::getFrame(int frame){return imageSequence[frame];}
std::vector<unsigned char **> WPPMAT001::FrameSequence::getSequence(){return imageSequence;}
void WPPMAT001::FrameSequence::read(std::string filename, int xorigion, int yorigion, int xend, int yend, int height, int width){
   int xstart = xorigion;
   int xend = yorigion;
   int ystart = xend;
   int yend = yend;
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
        return 1;
    }
    std::string magic;
    int width, height, maxval;
    infile >> magic >> width >> height >> maxval;
    if (magic != "P5" || maxval > 255) {
        std::cerr << "Invalid pgm format" << std::endl;
        return 1;
    }
   infile.ignore(1, '\n'); 
   unsigned char ** two_pointer;
   two_pointer = new unsigned char * [width];
      for(int j = 0;j<width;j++){
         two_pointer[j] = new unsigned  char[height];
         for(int k = 0;k<height;k++){
           
            infile.read((char*)&two_pointer[j][k], 1);
         }
    }
    infile.close();
    
    for(int i = 0 ; i<coords.size(); i++){
      unsigned char ** frame = nullptr;
      int x = coords[i].xcoord;
      int y = coords[i].ycoord;
      frame = new unsigned char * [480];
                 
         for(int j = 0; j<480;j++){
            x++;
            frame[j] = new unsigned char [640];
            for(int k = 0;k<640;k++){
               y++;
               frame[j][k] = two_pointer[x][y];
            }
            y = coords[i].ycoord; 
         
         imagesSequence.push_back(frame);
         }
        

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

int main(void){;
   int xstart = 0;
   int xend = 10;
   int ystart = 1;
   int yend = 10;
   std::vector<WPPMAT001::origion_coords> coords;
   WPPMAT001::FrameSequence images;
   std::ifstream infile("examples/sloan_image.pgm", std::ios::binary);
   if (!infile) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    
    std::string magic;
    int width, height, maxval;
    infile >> magic >> width >> height >> maxval;
    if (magic != "P5" || maxval > 255) {
        std::cerr << "Invalid pgm format" << std::endl;
        return 1;
    }

    
   infile.ignore(1, '\n'); 
   unsigned char ** two_pointer;
   two_pointer = new unsigned char * [width];
      for(int j = 0;j<width;j++){
         two_pointer[j] = new unsigned  char[height];
         for(int k = 0;k<height;k++){
           
            infile.read((char*)&two_pointer[j][k], 1);
         }
    }
    //images.push_back(data);
   
    // Read the pixel values and store them in the char array
   // Ignore the newline character after the header
    //infile.read((char*)(data), width * height);
    // Close the ifstream object
    infile.close();
    
    std::string filename = "test.pgm";
      std::ofstream out(filename, std::ofstream::binary);
       out<<"P5\n";
      out<< width<<" "<<height <<"\n";
      out<< maxval <<"\n";
      for (int i = 0; i < width ; i++)
      
        {
         for(int j = 0;j<height;j++){
            unsigned char* ptr = &two_pointer[i][j];
            out.write((char*)ptr, 1);
            }
        }
         
      out.close();
   
    //std::cout<< sizeof(data);
    //std::cout<sizeof(data char*);
    // Use the char array to process the pgm image
    //std::cout<<data[100];
    // Free the memory allocated for the char array
    //for(int i = 0; i < width; ++i)
	//{
   
   //std::string filename = "test.pgm";
     /// std::ofstream out(filename,std::ios::out | std::ios::binary);
       //out.write((char*)data,width*height);
    
      
      
    
      //unsigned char ** two_pointer = new unsigned char * [width];
     // for(int j = 0;j<width;j++){
      //   two_pointerr[j] = new unsigned  char[height];
       //  for(int k = 0;k<height;k++){
        //    two_pointer[j][k] = data[j*height+k];
           //std::cout<<two_pointer[k/height][k%height]<<std::endl;
        // }
         
         
      // delete[] data;
      
      
      
      
       
      //}
     
      //unsigned char** frame = new unsigned char * [480];
      //for(int l = 0;l<480;l++){
        // frame[l] = new unsigned  char[640];
          //for(int m = 0;m<height;m++){
           // frame[l][m] = two_pointer[l][m];
            
         //}
         
      
      //}
     // std::cout<<"hi";
      //unsigned char* tdframe = new unsigned char[width*height];
      //for (int i = 0; i < width; ++i) {
       // for (int j = 0; j < height; ++j) {
           // tdframe[i*height+j] = two_pointer[i][j];
          //std::cout<<tdframe[i*height+j]<<std::endl;
       // }}
       //std::cout<<"hi2";
       //std::string filename = "1test.pgm";
       //std::ofstream out(filename, std::ios::binary);
       //out >>"P5" >>std::endl>>480 >>640;
       //out.write((char*)data,width*height);

        // out.write((char*)tdframe,width*height);
      //std::cout<<frame[500][500]<<std::endl<<two_pointer[500][500];
      //unsigned char* dframe = new unsigned char[480*640];
      //for (int i = 0; i < 480; ++i) 
        //for (int j = 0; j < 640; ++j) {
         //   dframe[i*480+j] = frame[i][j];
        //}

       //std::string filename = "test.pgm";
       //std::ofstream out(filename, std::ios::binary);
       //out >>"P5" >>std::endl>>480 >>640;
       //out.write((char*)data,width*height);

         //out.write((char*)dframe,480*640);
         
      
    
		 // Release the memory allocated to the int array at position i in the 2D array.
	//}

	//delete [] data; // Release the memory allocated to our int * array.

   
      for(int i = 0 ; i<coords.size(); i++){
      unsigned char ** frame = nullptr;
      int x = coords[i].xcoord;
      int y = coords[i].ycoord;
      frame = new unsigned char * [480];
                 
         for(int j = 0; j<480;j++){
            x++;
            frame[j] = new unsigned char [640];
            for(int k = 0;k<640;k++){
               y++;
               frame[j][k] = two_pointer[x][y];
            }
            y = coords[i].ycoord; 
         
         }
      images.add(frame);  

    }
   std::cout<<images.size();
   
   for(int i = 0; i<images.size();i++){
      std::string filename1 =std::to_string(i)+ "test.pgm";
      std::ofstream out(filename1, std::ofstream::binary);
      out<<"P5\n";
      out<< 480<<" "<<640 <<"\n";
      out<< maxval <<"\n";
      //unsigned char ** printSequence = images.getFrame(i);
      for (int k = 0; k < 480 ; k++)
      
        {
         for(int j = 0;j<640;j++){
         unsigned char* ptr = &((images.getFrame(i))[k][j]);
         //ptr = &two_pointer[i][j];
            //if (i<10){
              // std::cout<<two_pointer[i][i]<<std::endl;
            //}
            out.write((char*)ptr, 1);
            }
        }
         
      out.close();
   }
   for(int i = 0; i < width; ++i)
	{
		delete [] two_pointer[i]; // Release the memory allocated to the int array at position i in the 2D array.
	}

	delete [] two_pointer;
   
   //std::string filename = "1test.pgm";
     // std::ofstream out(filename, std::ofstream::binary);
      //out<<"P5\n";
      //out<< 480<<" "<<640 <<"\n";
      //out<< maxval <<"\n";
      //for (int i = 0; i < 480 ; i++)
      
        //{
         //for(int j = 0;j<640;j++){
         //unsigned char* ptr = &two_pointer[i][j];
         //ptr = &two_pointer[i][j];
            //if (i<10){
              // std::cout<<two_pointer[i][i]<<std::endl;
            //}
           // out.write((char*)ptr, 1);
          //  }
        //}
         
      //out.close();
   /*
   else{
      float x = xstart;
      //frame_coord=(xstart, ystart); // starting frame coord
      for (int y = ystart+1; y <= yend; ++y)
      { x = x + g; 
      //frame_coord=(std::round(x), y);
      }
   
   
   
   }*/
   //unsigned char ** two_pointer = new unsigned char * [640];
   //for(int i)
   
     ///unsigned char ** two_pointer = new unsigned char * [480];
      //for(int j = 0;j<480;j++){
        // two_pointer[j] = new unsigned  char[640];
         //for(int k = 0;k<640;k++){
           // two_pointer[j][k] = data[j][k];
            //std::cout<<two_pointer[j][k];
         //}
      //}
      //images.add(two_pointer);
   /*for(int i = 0; i<coords.size();i++){
      unsigned char ** two_pointer = new unsigned char * [640];
      for(int j = coords[i].xcoord;j<coords[i].xcoord+640;j++){
         two_pointer[j] = new unsigned  char[480];
         for(int k = coords[i].ycoord;k<coords[i].ycoord+480;k++){
            two_pointer[j][k] = data[j][k];
            //std::cout<<two_pointer[j][k];
         }
         
        
      }
       images.add(two_pointer);
   }*/
   //std::string filename = std::to_string(0)+".pgm";
   //std::ofstream out(filename,std::ios::out | std::ios::binary);
   //for(int x = 0;x<480;++x){
     // for(int y= 0 ;y<640;y++){
       //  unsigned char pixel = images.getFrame(0)[x][y];
         //out<<pixel;
      
      //}
   //}
   
   /*
   std::cout<<images.size();
   for(int i = 0;i<images.size();i++){
      std::string filename = std::to_string(i)+".pgm";
      std::ofstream out(filename,std::ios::out | std::ios::binary);
      //unsigned char ** test = images.getFrame(i);
      //std::cout<<test[i];
      out.write((const char*)images.getFrame(i)[i],480*640*sizeof(const char*));
      }
   
   
   for(int i = 0; i<coords.size(); i++){
      //std::cout<<coords[i].xcoord<<" "<<coords[i].ycoord<<std::endl;
      unsigned char ** two_pointer = new unsigned char * [640];
      for (int j = coords[i].xcoord; j < 640; ++j)
	{
		two_pointer[j] = new unsigned  char[480]; // Create a new integer array on the heap. Store its address using our two_pointer variable.
		for (int k =coords[i].ycoord; k < 480; ++k)
		{
			two_pointer[j][k] = data[coords[i].xcoord*width+coords[i].ycoord]; // Read in the next integer value from the file.
		}
		
	}
   
      images.add(two_pointer);
      
      continue;
      
   }*/
   //delete[] data;

   //std::cout<<images.size();
   //images.~FrameSequence();
   /*std::vector<unsigned char **> img = images.getSequence();
   for(int i = 1;i<images.size();i++){
      std::cout<<img[i]<<std::endl;
      std::string filename = std::to_string(i)+".pgm";
      std::ofstream out(filename,std::ios::out | std::ios::binary);
      //unsigned char ** test = images.getFrame(i);
      for(int j = 1; j<480;j++){
      out.write((const char*)img[j],480);
      std::cout<<"here";
      }
      
   }
   for(int i = 0;i<images.size();i++){
      std::string filename = std::to_string(i)+".pgm";
      std::ofstream out(filename,std::ios::out | std::ios::binary);
      unsigned char ** test = images.getFrame(i);
      std::cout<<test[i];
      }*/
   
}

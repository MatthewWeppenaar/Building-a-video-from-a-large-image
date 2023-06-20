#ifndef __FRAMESEQUENCE
#define __FRAMESEQUENCE
#include <vector>

namespace WPPMAT001{
   struct origion_coords{//used to store frame start points
      int xcoord;
      int ycoord;
   
   
   };
   class FrameSequence{
      //local variables
      std::vector<unsigned char **> imageSequence;
      
      
      public:
         unsigned char ** image;
         FrameSequence(void);
         ~FrameSequence(); // Destructor
         void add(unsigned char ** test);
         int size();
         unsigned char ** getFrame(int frame);
         std::vector<unsigned char **> getSequence();
         std::vector<WPPMAT001::origion_coords> generate_trajectory(int xorigion, int yorigion, int xend, int yend);//generate a trajectory
         void generate_frame_sequence(int height, int width,std::vector<origion_coords> coords);//generate a frame sequence
         void read(std::string filename);//reading pgm into a data structure
         void deleteImage();//deleting space allocated for big image
         void write(int height, int width,std::string fileName);
         void reverse(int height, int width,std::string fileName);
         void invert(int height, int width,std::string fileName);
         void reverse_invert(int height, int width,std::string fileName);
         
   
   };
   
   
#endif  
   
   
   




}
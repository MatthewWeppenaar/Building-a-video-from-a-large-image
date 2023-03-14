#ifndef __FRAMESEQUENCE
#define __FRAMESEQUENCE
#include <vector>

namespace WPPMAT001{
   class FrameSequence{
      //local variables
      std::vector<unsigned char **> imageSequence;
      
      public:
         FrameSequence(void);
         ~FrameSequence(); // Destructor
         void add(unsigned char ** test);
         int size();
         unsigned char ** getFrame(int frame);
         std::vector<unsigned char **> getSequence();
   
   };
   
   struct origion_coords{//used to store frame start points
      int xcoord;
      int ycoord;
   
   
   };
#endif  
   
   
   




}
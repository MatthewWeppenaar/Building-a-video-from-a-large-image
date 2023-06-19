extractor.exe: FrameSequence.o extractor.o
	g++ FrameSequence.o extractor.o -o extractor.exe -std=c++20

FrameSequence.o: FrameSequence.cpp
	g++ -c FrameSequence.cpp -o FrameSequence.o -std=c++20

extractor.o: extractor.cpp
	g++ -c extractor.cpp -o extractor.o -std=c++20

clean:
	rm *.o extractor.exe out/*.pgm *.mp4

run:
	./extractor.exe examples/sloan_image.pgm  -t 0 1 200 200 -s 640 480 -w none sequence2 

run1:
	./extractor.exe examples/larger_image.pgm  -t 0 1 500 500 -s 640 480 -w invert invseq -w none sequence2 -w reverse sequence3 
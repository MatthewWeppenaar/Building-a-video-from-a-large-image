extractor.exe: FrameSequence.o extractor.o
	g++ FrameSequence.o extractor.o -o extractor.exe -std=c++20

FrameSequence.o: FrameSequence.cpp
	g++ -c FrameSequence.cpp -o FrameSequence.o -std=c++20

extractor.o: extractor.cpp
	g++ -c extractor.cpp -o extractor.o -std=c++20

clean:
	rm *.o extractor.exe out/*.pgm *.mp4

run: #positive trajectory
	./extractor.exe examples/sloan_image.pgm  -t 0 0 500 500 -s 720 1080 -w none sequence2 -w reverse sequence_rev 

run1: #positive trajectory with a few operations
	./extractor.exe examples/larger_image.pgm  -t 0 1 500 500 -s 640 480 -w invert invseq -w none sequence2 -w reverse sequence3 

run2: #positive trajectory with a few operations
	./extractor.exe examples/sloan_image.pgm  -t 0 1 200 200 -s 640 480 -w invert sequence_invert -w reverse_invert sequence_rev_invert 

run3: #positive trajectoty in reverse direction
	./extractor.exe examples/sloan_image.pgm  -t 200 200 0 0 -s 640 480 -w none sequence2

run4: #negative trajectory
	./extractor.exe examples/sloan_image.pgm  -t 100 0 0 100 -s 640 480 -w none sequence2

run5: #negative trajectory in reverse direction
	./extractor.exe examples/sloan_image.pgm  -t 0 100 100 0 -s 640 480 -w none sequence2

run6: #vertical trajectory
	./extractor.exe examples/sloan_image.pgm  -t 0 0 0 100 -s 640 480 -w none sequence3

run7: #horizontal trajectory
	./extractor.exe examples/sloan_image.pgm  -t 0 0 100 0 -s 640 480 -w none sequence4

run8: #horizontal trajectory in revese direction
	./extractor.exe examples/sloan_image.pgm  -t 100 0 0 0 -s 640 480 -w none sequence4

run9: #horizontal trajectory reverse direction
	./extractor.exe examples/sloan_image.pgm  -t 0 100 0 0 -s 640 480 -w none sequence5

run10: #positive trajectory
	./extractor.exe examples/sloan_image.pgm  -t 0 0 10000 10000 -s 640 480 -w none sequence2 -w reverse sequence_rev

run11: #multi-point trajectory - 3 points 
	./extractor.exe examples/sloan_image.pgm  -p 3 0 0 1000 1000 1200 0 -s 640 480 -w none sequence2

generate_video:
	python3 video_conversion.py
remove_images:
	rm out/*.pgm
all:
	g++ -o pacman.exe pacman.cc Cell.cc Map.cc ParticlePacman.cc ParticleGhost.cc Graph.cc Arduino.cc -lpthread -std=c++11 -lglut -lGLU -lGL -lm /usr/local/lib/libjpeg.a -I/usr/include/python2.7 -lpython2.7 


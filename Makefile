all:
	g++ -o pacman.exe pacman.cc Cell.cc Map.cc ParticlePacman.cc ParticleGhost.cc Graph.cc -lglut -lGLU -lGL -lm /usr/local/lib/libjpeg.a


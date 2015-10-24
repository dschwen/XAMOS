CC=g++

CFLAGS=-c -Wall -pedantic -O3 -D USESDL -D USEBOOST
LDFLAGS=-lSDLmain -lSDL -lSDL_image -lSDL_mixer -lSDL_gfx -lSDL_ttf -lGL -lGLU

SOURCES=main.cpp XAMOS.cpp SDL_collide.cpp Console.cpp AMALDebugTest.cpp PrintStream.cpp AMALBank.cpp AMALEnvGen.cpp AMALParser.cpp AMALInterpreter.cpp AMALCompiler.cpp AmalPrograms.cpp Timer.cpp AMOS_Sprite.cpp MequaScript.cpp AMOS_System.cpp GameEngineWrapper.cpp Mytype.cpp Mytypearray.cpp TheTokens.cpp Parser.cpp Dumper.cpp Interpreter.cpp CommandWrapper.cpp ActiveObject.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=../XAMOS

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) *.o


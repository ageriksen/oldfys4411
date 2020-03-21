#Compiler options, libs and target
cc= c++ -Wall # -03 # last one for optimization
char = characterClass

objdir = obj
srcdir = src

_objs = main.o gui.o characterClass.o #attributeClass.o featClass.o  
objs = $(patsubst %, $(objdir)/%, $(_objs))
# potential libraries
lib= -lX11

build : ${objs} 
	${cc} ${lib} -o main.exe ${objs}

$(objdir)/%.o : $(srcdir)/%.cpp
	$(cc) -c $(lib) -o $@ $<

clean : 
	rm -f $(objdir)/*.o

	


#objs : ${objs}
#
#main.o : main.cpp ${objs}
#	${cc} ${lib} -c  main.cpp 
#
#gui.o : gui.cpp gui.h
#	${cc} -c gui.cpp
#
#characterClass.o : characterClass.cpp characterClass.h
#	${cc} -c characterClass.cpp
#featClass.o : featClass.cpp #featClass.h
#	${cc} -c featClass.cpp
#attributeClass.o : attributeClass.cpp #attributeClass.h
#	${cc} -c featClass.cpp
#
#clean: ${objs} main.exe
#	rm *
#	rm *.exe

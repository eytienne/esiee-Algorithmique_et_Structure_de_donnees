runProject: compileProject
	./main structures/PROJET/text.txt

compileProject:
	gcc \
		my_c_lib/BinaryPath.c \
		my_c_lib/LinkedList.c \
		my_c_lib/Queue.c \
		my_c_lib/PriorityQueue.c \
		my_c_lib/ShallowStack.c \
		my_c_lib/StackTrace.c \
		my_c_lib/TreeNode.c \
		my_c_lib/Vector.c \
		structures/PROJET/compression.c \
		structures/PROJET/main.c \
		-o main

checkProject:
	frama-c \
		my_c_lib/BinaryPath.c \
		my_c_lib/LinkedList.c \
		my_c_lib/Queue.c \
		my_c_lib/PriorityQueue.c \
		my_c_lib/ShallowStack.c \
		my_c_lib/TreeNode.c \
		my_c_lib/Vector.c \
		structures/PROJET/compression.c \
		structures/PROJET/main.c \

testTree:
	gcc -g -rdynamic \
		my_c_lib/BinaryPath.c \
		my_c_lib/ShallowStack.c \
		my_c_lib/StackTrace.c \
		my_c_lib/*Tree*.c \
		my_c_lib/Vector.c \
		structures/TP5/testTree2.c \
		-o main \
	&& ./main

testBinaryPath:
	gcc \
		my_c_lib/BinaryPath.c \
		my_c_lib/ShallowStack.c \
		my_c_lib/*Tree*.c \
		structures/PROJET/testBinaryPath.c \
		-o main \
	&& ./main

testShallowStack:
	gcc \
		my_c_lib/ShallowStack.c \
		structures/PROJET/testShallowStack.c \
		-o main \
	&& ./main

testVector:
	gcc \
		my_c_lib/Vector.c \
		structures/TP4/testVector.c \
		-o main \
	&& ./main

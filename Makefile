runProject: compileProject
	./hzip compress us.txt

compileProject:
	gcc \
		my_c_lib/BinarySequence.c \
		my_c_lib/FileUtils.c \
		my_c_lib/LinkedList.c \
		my_c_lib/Queue.c \
		my_c_lib/PriorityQueue.c \
		my_c_lib/ShallowStack.c \
		my_c_lib/TreeNode.c \
		my_c_lib/Vector.c \
		structures/PROJET/hzip.c \
		structures/PROJET/main.c \
		-o hzip $g

staticCheckProject:
	frama-c \
		my_c_lib/BinarySequence.c \
		my_c_lib/FileUtils.c \
		my_c_lib/LinkedList.c \
		my_c_lib/Queue.c \
		my_c_lib/PriorityQueue.c \
		my_c_lib/ShallowStack.c \
		my_c_lib/TreeNode.c \
		my_c_lib/Vector.c \
		structures/PROJET/hzip.c \
		structures/PROJET/main.c \

valgrindProject: compileProject
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck --num-callers=16 --leak-resolution=high \
		--main-stacksize=100000000 \
		./hzip compress --table us.txt

testTree:
	gcc -g -rdynamic \
		my_c_lib/BinarySequence.c \
		my_c_lib/ShallowStack.c \
		my_c_lib/StackTrace.c \
		my_c_lib/*Tree*.c \
		my_c_lib/Vector.c \
		structures/TP5/testTree2.c \
		-o main \

testBinarySequence:
	gcc \
		my_c_lib/BinarySequence.c \
		my_c_lib/ShallowStack.c \
		my_c_lib/*Tree*.c \
		structures/PROJET/testBinarySequence.c \
		-o main \

testShallowStack:
	gcc \
		my_c_lib/ShallowStack.c \
		structures/PROJET/testShallowStack.c \
		-o main \

testVector:
	gcc -g \
		my_c_lib/Vector.c \
		structures/TP4/testVector.c \
		-o main \
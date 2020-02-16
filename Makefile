runProject: compileProject
	./main structures/PROJET/text.txt

compileProject:
	gcc my_c_lib/LinkedList.c \
		my_c_lib/Queue.c \
		my_c_lib/PriorityQueue.c \
		my_c_lib/TreeNode.c \
		my_c_lib/Vector.c \
		structures/PROJET/compression.c \
		structures/PROJET/main.c \
		-o main


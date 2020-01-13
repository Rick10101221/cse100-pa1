editsrc:
	gvim -p src/bst/*.hpp

edittest:
	gvim -p test/bst/test*.cpp

editall:
	gvim -p src/bst/*.hpp && gvim -p test/bst/test*.cpp

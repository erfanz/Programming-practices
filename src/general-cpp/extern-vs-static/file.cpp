#include <iostream>

// this is another compilation unit

extern int global_var_1;			// this is just 'decleration', meaning that it is defined somewhere else. Also, its linkage is external.
int global_var_2 = 2;				// this is 'definition', and its linkage is external. main.cpp can access this variable if it declares ihis variable in its file.
static int private_var_file = 10; 	// because of 'static' keyword, its linkage is internal, meaning that it can only be access from within this compilation unit, and not main.cpp


void print_and_increment_private_var_of_file();		// this function is defined globally, so other compilation units can access it if they declare this function in their files.

void print_and_increment_private_var_of_file() {
	std::cout << "file.cpp: the value of 'private_var_file' is: " << private_var_file << std::endl; 
	++private_var_file;;
} 

void accessing_a_static_variable_with_none_linkage() {
	static int static_scoped_var = 100;	// the initialization only takes place once in the program, in the beginning of the compilation.
	std::cout << "file.cpp: static_scoped_var: " << static_scoped_var << std::endl;
	++static_scoped_var;	// static_scoped_var retains its value after the control passes over this functino and reaches the end
}
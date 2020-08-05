#include <iostream>


// Note that we have NOT included file.cpp in this compilation unit. However, global variable with external linkage can be accessed by ANY file across the module, as long as they are 'declared' with 'extern' keyword in those files.
int global_var_1;			// external linkage. This variable is 'defined' right here
extern int global_var_2;	// this is just a 'declaration', so somewhere else must bring the 'definition'
static int private_var_main;		// this is NOT a global variable and is 'private' to this compilation unut, as its linkage is local (all because of 'static' keyword behind it)

extern void print_and_increment_private_var_of_file();			// note that without these declarations, the program won't compile
extern void accessing_a_static_variable_with_none_linkage();	// note that without these declarations, the program won't compile

int main() {
	global_var_1 = 1;
	
	// altough that global_var_2 is not 'defined' here, but since we have declared it, we can access it.
	std::cout << "main.cpp: 'global_var_2' before modification: " << global_var_2 << std::endl;
	++global_var_2; 
	std::cout << "main.cpp: 'global_var_2' after modification: " << global_var_2 << std::endl;
	
	private_var_main = 3;
	std::cout << "main.cpp: 'private_var_main' which is a static var and is private to this compilation unit: " << private_var_main << std::endl;
	
	print_and_increment_private_var_of_file();
	print_and_increment_private_var_of_file();
	
	std::cout << "main.cpp: accessing a 'static' variable or function from another file creates a compilation error, since 'static' makes the linkage of variables and functions 'internal' " << std::endl;
	// uncommenting the following makes a compilation error
	// std::cout << "accessing the private variable of the other file causes an error. private_var_file: " << private_var_file << std::endl;
	
	accessing_a_static_variable_with_none_linkage();
	accessing_a_static_variable_with_none_linkage();
	
	
	return 0;
}
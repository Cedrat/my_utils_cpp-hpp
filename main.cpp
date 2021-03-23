#include "my_utils_cpp.h"

void create_hpp(std::string name)
{
    std::ofstream file;

    file.open(name + ".hpp");
    file << "#ifndef " << capslock(name) << "_HPP" << std::endl;
    file << "# define " << capslock(name) << "_HPP\n" << std::endl;
    file << "#include <string>\n" << std::endl;
    file << "class " << name << std::endl;
    file << "{" << std::endl;
    file << "\tpublic : " << std::endl;
    file << "\t\t" << name << "(void);" << std::endl;
    file << "\t\t" << name << "(Fixed const & src);" << std::endl;
    file << "\t\t~" << name << "();\n" << std::endl;
    file << "\t\t" << name << "\t&operator=(" << name << " const & rhs);" << std::endl;
    file << "};\n" << std::endl;
    file << "#endif" << std::endl;
    file.close();
}

void create_cpp(std::string name)
{
    std::ofstream cpp;
    std::ifstream hpp;
    std::string   class_name;
    std::string   line;
    char buffer[3];

    class_name = name.substr(0 , name.rfind(".hpp" , name.size()));
    hpp.open(name);
    cpp.open(class_name + ".cpp");
    cpp << "#include \"" << name << "\"" << std::endl;

    while (hpp.getline(buffer, 3))
        std::cout << buffer << std::endl;



}

void choose_operation(std::string operation, std::string file_or_name)
{
    if (operation == "CREATE_HPP")
        create_hpp(file_or_name);
    else if (operation == "CREATE_CPP")
        create_cpp(file_or_name);
}

int main(int argc, char **argv)
{
    if (argc != 3)
        errors(0);
    choose_operation(argv[1] ,argv[2]);
}
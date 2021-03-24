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

void write_constructor(std::string line, std::ofstream *cpp, std::string class_name)
{
    if (line.find("()") == class_name.size() || line.find("(void)") == class_name.size())
    {
        *cpp << class_name << "::" << class_name << "(void)" << std::endl;
        *cpp << "{\n\n}\n" << std::endl;
    }
    else if (line.find("(Fixed const & src)") == class_name.size())
    {
        *cpp << class_name << "::" << class_name << "(Fixed const & src)" << std::endl;
        *cpp << "{\n\t*this = src;\n}\n" << std::endl; 
    }
    else
    {
        int i;

        i = 0;
        *cpp << class_name << "::" << class_name << line.substr(line.find("("), line.find(")") - line.find("(") + 1) << " : ";
        while (line[i])
        {
            while (line[i] != ',' && line[i] != ')' && line[i])
                i++;
            *cpp << "_" << line.substr(line.rfind(" ", i) + 1, i - line.rfind(" ", i) - 1) << "(" << line.substr(line.rfind(" ", i) + 1, i - line.rfind(" ", i) - 1)
            << ")";
            if (line[i] == ')')
                break;
            *cpp << " , ";
            if (line[i])
                i++;
        }
        *cpp << std::endl;
        *cpp << "{\n\n}\n" << std::endl;
    }
}

void write_destructor(std::ofstream *cpp, std::string class_name)
{
    *cpp << class_name << "::~" << class_name << "()" << std::endl;
    *cpp << "{\n\n}\n" << std::endl;
}

void write_operator(std::string line, std::ofstream *cpp, std::string class_name)
{
    std::string ope;

    ope = find_operator(line);
    //if unary operator
    *cpp << class_name << " &" << class_name << "::operator" << ope << "(Fixed const & rhs)" << std::endl;
    *cpp << "{\n\tthis->[...] = rhs.[...]();" << std::endl;
    *cpp << "\treturn *this;" << std::endl;
    *cpp << "}\n" << std::endl;

}

void write_function(std::string line, std::ofstream *cpp, std::string class_name)
{
    std::string type;
    std::string name_variable;
    std::string param;

    type = line.substr(0, line.rfind("\t", line.size()));
    name_variable = line.substr(line.find("get") + 3, line.rfind("(", line.size()) - (line.find("get") + 3));
    param = line.substr(line.find("("), line.find(")") - line.find("(") + 1);
    *cpp << type << "\t" << class_name << "::get" << name_variable << param << " const" << std::endl;
    *cpp << "{\n\treturn (this->_" << lowercase(name_variable) << ");\n}\n" << std::endl;
}

void create_cpp(std::string name)
{
    std::ofstream cpp;
    std::ifstream hpp;
    std::string   class_name;
    std::string   line;
    char  buffer[256];

    class_name = name.substr(0 , name.rfind(".hpp" , name.size()));
    hpp.open(name);
    cpp.open(class_name + ".cpp");
    cpp << "#include \"" << name << "\"\n" << std::endl;

    int i = 0;
    while (hpp.getline(buffer, 256))
    {
        i = 0;
        while (buffer[i] == ' ' || buffer[i] == '\t')
            i++;
        line = &buffer[i];
        if (line.find(class_name) == 0 && line.find("operator") == std::string::npos)
            write_constructor(line, &cpp, class_name);
        else if (line.find("~" + class_name) == 0)
            write_destructor(&cpp, class_name);
        if (line.find("operator") != std::string::npos)
            write_operator(line, &cpp, class_name);
        else if (line.find("get") != std::string::npos)
            write_function(line, &cpp, class_name);

    }
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
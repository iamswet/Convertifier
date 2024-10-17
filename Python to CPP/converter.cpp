#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

// Function to handle simple type inference
std::string inferType(const std::string& value) {
    if (value.find("\"") != std::string::npos || value.find("'") != std::string::npos) {
        return "std::string";
    } else if (value.find(".") != std::string::npos) {
        return "double";
    } else {
        return "int";
    }
}

// Function to convert Python to C++ for a simple variable assignment
std::string convertAssignment(const std::string& line) {
    size_t equalsPos = line.find('=');
    std::string varName = line.substr(0, equalsPos - 1);
    std::string value = line.substr(equalsPos + 2);
    std::string varType = inferType(value);
    return varType + " " + varName + " = " + value + ";";
}

// Function to convert a Python 'for' loop into a C++ 'for' loop
std::string convertForLoop(const std::string& line) {
    size_t inPos = line.find("in");
    std::string varName = line.substr(4, inPos - 5);
    std::string range = line.substr(inPos + 3);
    return "for (int " + varName + " : " + range + ") {";
}

// Function to convert Python functions to C++ functions
std::string convertFunction(const std::string& line) {
    size_t defPos = line.find("def");
    size_t parenPos = line.find('(');
    std::string functionName = line.substr(defPos + 4, parenPos - defPos - 4);
    return "void " + functionName + "(" + line.substr(parenPos) + " {";
}

// Function to convert Python print statements to C++ std::cout statements
std::string convertPrint(const std::string& line) {
    std::string output = line.substr(6); // Strip off 'print('
    output.pop_back(); // Remove the closing parenthesis ')'
    return "std::cout << " + output + " << std::endl;";
}

// Main conversion function that converts Python lines to C++
std::string convertLine(const std::string& line) {
    if (line.find("print") == 0) {
        return convertPrint(line);
    } else if (line.find("for") == 0) {
        return convertForLoop(line);
    } else if (line.find("def") == 0) {
        return convertFunction(line);
    } else if (line.find("=") != std::string::npos) {
        return convertAssignment(line);
    } else if (line.find("return") != std::string::npos) {
        return line + ";";
    }
    return line;
}

// Function to read Python code from a file and convert it to C++
void convertPythonToCpp(const std::string& pythonFile, const std::string& cppFile) {
    std::ifstream pyFile(pythonFile);
    std::ofstream cppOut(cppFile);

    if (!pyFile.is_open()) {
        std::cerr << "Could not open Python file!" << std::endl;
        return;
    }

    if (!cppOut.is_open()) {
        std::cerr << "Could not create C++ file!" << std::endl;
        return;
    }

    std::string line;
    cppOut << "#include <iostream>\n#include <string>\n\nint main() {\n";
    
    while (std::getline(pyFile, line)) {
        std::string convertedLine = convertLine(line);
        cppOut << "    " << convertedLine << "\n";
    }

    cppOut << "    return 0;\n}\n";
    
    pyFile.close();
    cppOut.close();
    std::cout << "Conversion complete: " << cppFile << std::endl;
}

int main() {
    std::string pythonFile, cppFile;
    std::cout << "Enter Python file path: ";
    std::cin >> pythonFile;
    std::cout << "Enter C++ file output path: ";
    std::cin >> cppFile;

    convertPythonToCpp(pythonFile, cppFile);

    return 0;
}

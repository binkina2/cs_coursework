#include "functions.hpp"
// Your function definitions should go in this source file.
bool Lowercase(std::string& input) {
    for (size_t i = 0; i < input.length(); ++i) {
        input[i] = tolower(input[i]); // indivual lowercase characters 

        switch(input[i]) {
            case 'a': break;
            case 'e': break;
            case 'i' : break;
            case 'o' : break;
            case 'u' : break;
            case 'p' : break;
            case 'k' : break;
            case 'h' : break;
            case 'l' : break;
            case 'm' : break;
            case 'n' : break;
            case 'w' : break;
            case ' ' : break;
            case '\'' : break;
            default: return false;
        }
    }
    return true;
}
std::string Convert(std::string input) {
    std::string output;
    
    if (!Lowercase(input)) {
        return "contains a character not a part of the Hawaiian language.";
    }
      for (size_t i = 0; i < input.length(); ++i) {
        bool add_dash = false;
        if (input.compare(i,2, "ai") == 0) { output += "eye"; ++i; add_dash = true;}
        else if (input[i] == 'a' && input[i+1] == 'e') { output += "eye"; ++i; add_dash = true;}
        else if (input[i] == 'a' && input[i+1] == 'o') { output += "ow"; ++i; add_dash = true;}
        else if (input[i] == 'a' && input[i+1] == 'u') { output += "ow"; ++i; add_dash = true;}
        else if (input[i] == 'e' && input[i+1] == 'i') { output += "ay"; ++i; add_dash = true;}
        else if (input[i] == 'e' && input[i+1] == 'u') { output += "eh-oo"; ++i; add_dash = true;}
        else if (input[i] == 'i' && input[i+1] == 'u') { output += "ew"; ++i; add_dash = true;}
        else if (input[i] == 'o' && input[i+1] == 'i') { output += "oy"; ++i; add_dash = true;}
        else if (input[i] == 'o' && input[i+1] == 'u') { output += "ow"; ++i; add_dash = true;}
        else if (input[i] == 'u' && input[i+1] == 'i') { output += "ooey"; ++i; add_dash = true;}
        else if (input[i] == 'a')  {output += "ah"; add_dash = true;}
        else if (input[i] == 'e') { output += "eh"; add_dash = true;}
        else if (input[i] == 'i') { output += "ee";add_dash = true;}
        else if (input[i] == 'o') { output += "oh"; add_dash = true;}
        else if (input[i] == 'u') { output += "oo"; add_dash = true;}
        else if (input[i] == 'w') {
            if (i == 0) { output += "w";} 
            else if (input[i-1] == 'a') {output += "w";}
            else if (input[i-1] == 'i' || input[i-1] == 'e') {output += "v";}
            else if (input[i-1] == 'u' || input[i-1] == 'o') {output += "w";}   
        }
        else {output += input[i];}
        if (add_dash && i != input.length()-1 && isalpha(input[i+1]) != 0) {output += '-';}
    }
    return output;
}
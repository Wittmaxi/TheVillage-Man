#include <webcpp/webcpp.hpp>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <regex>

using namespace WCP;

std::string exec(std::string cmd_) {
    const char* cmd = cmd_.c_str();
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

void printMan () {
    if (ENV::GET("s") != "") {
        std::string queryString = ENV::GET("s");
        std::transform(queryString.begin(), queryString.end(), queryString.begin(), tolower);
        queryString = std::regex_replace (queryString, std::regex("([^a-z])+"), "");
        std::string stor = exec ("man \"" + queryString + "\"");
        if (stor == "") {
            std::cout << ConvenientText("We are sorry, but there was no manpage entry to " + queryString);
        } else {
            std::cout << ConvenientText(stor);
        }
    }
}

int main () {
    ENV::initializeENV();
    HTTPHeader a;
    a.print();
std::cout << Document {
    Head {
        Include {"../style.css", "text/css", "stylesheet"}
    },
    Container {ClassAttribute{"topbar"},
        Container {ClassAttribute{"topbar-content"},
            ConvenientText{"TheVillage Man"}    
        }
    },
    Form {
        Label {Attribute{"for=s"}, Text {"Search the Manpages!"}},
        Input {InputName {"s"}},
        Input {InputType{"submit"}}
    },
    Container {ClassAttribute {"shell"},
        Function {printMan} 
    }, 
    ConvenientText {
        "Powered by WebCPP.\n"
        "\t\tWritten by Maximilian Wittmer\n"
        "Source Code: "
    },
    HyperLink {HyperReference{"https://github.com/Wittmaxi/TheVillage-Man"},
        ConvenientText{"https://github.com/Wittmaxi/TheVillage-Man"}
    }
};
}
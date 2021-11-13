#include <iostream>
#include <map>
#include <string>
#include <vector> 
#include <sstream>

using namespace std;

extern bool running = true;
extern const string system_prefix = "system >> ";

void sysout(string msg) {
    cout << system_prefix + msg << endl;
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

class command {
public:
    command() {}
    virtual void onCommand(vector<string> args) {}
};

class helpCommand : public command {
public:
    helpCommand() {}
    void onCommand(vector<string> args) override {
        cout << "====================\n - exit\n====================" << endl;
    }
};

class exitCommand : public command {
public:
    exitCommand() {}
    void onCommand(vector<string> args) override {
        sysout("exiting . . .");
        running = false;
    }
};

class printCommand : public command {
public:
    printCommand() {}
    void onCommand(vector<string> args) override {

        if (!is_number(args[2])) {
            sysout("incorrect args");
            return;
        }

        int iterations = stoi(args[2]);

        string message = args[1];

        for (int i = 0; i < iterations; i++)
            sysout(message);
    }
};

class testCommand : public command {
public:
    testCommand() {}
    void onCommand(vector<string> args) override {
        for (size_t i = 0; i < args.size(); i++)
            sysout(args[i]);
    }
};

vector<string> split(string args, char seperator) {
    vector<string> vec;
    string word;

    args += " ";

    for (size_t i = 0; i < args.length(); i++) {
        if (args[i] == seperator) {
            vec.push_back(word);
            word = "";
        }
        else
        {
            word += args[i];
        }
    }

    return vec;
}

int main()
{
    const string version = "Build 0 Alpha";
    const string program_name = "CommandSystemCPP";

    cout << "===================================" << endl;
    cout << program_name + " " + version + ", By Nort721\n";
    cout << "===================================" << endl;

    map<string, command*> commands;

    commands.insert(make_pair("help", new helpCommand()));
    commands.insert(make_pair("exit", new exitCommand()));
    commands.insert(make_pair("test", new testCommand()));
    commands.insert(make_pair("print", new printCommand()));

    string input = " ";

    while (running) {

        cout << ">> ";
        getline(cin, input);

        if (input.size() > 0) {

            // get command name
            string commandName = "";

            // gets the first word in a string
            for (size_t i = 0; i < input.size(); i++) {
                if (input[i] == ' ') {
                    break;
                }
                else {
                    commandName += input[i];
                }
            }

            // if the name is in the map keys, get and execute the command
            if (commands.count(commandName)) {
                commands[commandName]->onCommand(split(input, ' '));
            }
            else
            {
                cout << system_prefix + "Unknown command. Type help for help." << endl;
            }
        }

    }

    return 0;
}
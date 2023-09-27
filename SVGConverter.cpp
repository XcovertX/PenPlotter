#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// SVG path commands class
class SvgCommand {
public:
    char type;       // Command type (M, L, C, etc.)
    vector<double> params; // Parameters associated with the command

    SvgCommand(char t) : type(t) {}

    void addParam(double param) {
        params.push_back(param);
    }
};

// Function to parse an SVG path and extract commands
vector<SvgCommand> parseSvgPath(const string& pathData) {
    vector<SvgCommand> commands;
    istringstream iss(pathData);
    char cmd;
    while (iss >> cmd) {
        SvgCommand command(cmd);
        while (iss.peek() == ' ' || iss.peek() == ',') {
            iss.ignore();
        }
        double param;
        while (iss >> param) {
            command.addParam(param);
            while (iss.peek() == ' ' || iss.peek() == ',') {
                iss.ignore();
            }
        }
        commands.push_back(command);
    }
    return commands;
}

// Function to generate G-code from SVG commands
string svgToGcode(const vector<SvgCommand>& svgCommands) {
    // parsed commands
    string gcode;
    for (const SvgCommand& cmd : svgCommands) {
        gcode += "G1 "; // Replace with the appropriate G-code command
        for (double param : cmd.params) {
            gcode += to_string(param) + " ";
        }
        gcode += "\n";
    }
    return gcode;
}

int main() {
    // Read an SVG path data from a file or any source.
    string svgPathData = "M100,100 L200,200 C100,200 100,300 200,300";

    // Parse the SVG path into commands
    vector<SvgCommand> svgCommands = parseSvgPath(svgPathData);

    // Convert SVG commands to G-code
    string gcode = svgToGcode(svgCommands);

    // Print the generated G-code
    cout << gcode;

    return 0;
}
#include "CommandParser.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

//with no artguments the constructor assumes one wants to add commands later
CommandNode::CommandNode() {
	hasSubcommands = true;
}

CommandNode::CommandNode(void(*func)(vector<string>* args)) {
	//if given a function pointer as an argument set hasSubcommands to false
	hasSubcommands = false;
	this->func = func;
}

CommandNode::CommandNode(map<string, CommandNode*> subcommands) {
	//if given a map of subcommands as an argument set has Subcommands to true
	hasSubcommands = true;
	this->subcommands = subcommands;
}

CommandNode::~CommandNode() {
	//iterate through subcommands and free them
	if (hasSubcommands) {
		for (auto iter : subcommands) {
			delete iter.second;
		}
	}
}

//adds a subcommand to the subcommands map
void CommandNode::AddSubcommand(string name, CommandNode* node) {
	if (hasSubcommands) {
		subcommands[name] = node;
	}
}

//gets possible subcommands
std::vector<string>* CommandNode::getPossibleCommands() {
	if (hasSubcommands) {
		vector<string>* keyz = new vector<string>();
		for (auto iter : subcommands) {
			keyz->push_back(iter.first);
		}
		return keyz;
	}
	return NULL;
}

//checks if a command is contained in the subcommands map
bool CommandNode::containsSubcommand(string scmd) {
	vector<string>* keys = getPossibleCommands();
	std::vector<string>::iterator it = find(keys->begin(), keys->end(), scmd);
	return it != keys->end();
}

//splits the lowercases the command string, splits it at ' ' and then calls _walk
void CommandNode::walk(string cmd) {
	vector<string>* splittedCmd = new vector<string>();
	for (char c : cmd) {
		c = tolower(c);
	}
	istringstream iss(cmd);

	do
	{
		string sub;
		iss >> sub;
		if (!sub.empty()) {
			splittedCmd->push_back(sub);
		}
	} while (iss);

	_walk(splittedCmd);
}

//really walks the tree
void CommandNode::_walk(vector<string>* cmd) {
	
	if (hasSubcommands) {
		if (cmd->size() < 1) {
			return;
		}
		if (!containsSubcommand(cmd->at(0))) {
			return;
		}
		//remove first element from commands
		string current_cmd = cmd->at(0);
		//erase currently processed part from string
		cmd->erase(cmd->begin());
		//walk next node
		subcommands[current_cmd]->_walk(cmd);
		return;
	}
	else  {
		//call associated function
		func(cmd);
		delete cmd;
	}
}
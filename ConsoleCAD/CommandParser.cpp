#include "CommandParser.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

CommandNode::CommandNode() {
	hasSubcommands = true;
}

CommandNode::CommandNode(void(*func)(vector<string>* args)) {
	hasSubcommands = false;
	this->func = func;
}

CommandNode::CommandNode(map<string, CommandNode*> subcommands) {
	hasSubcommands = true;
	this->subcommands = subcommands;
}

CommandNode::~CommandNode() {
	if (hasSubcommands) {
		for (auto iter : subcommands) {
			delete iter.second;
		}
	}
}

void CommandNode::AddSubcommand(string name, CommandNode* node) {
	if (hasSubcommands) {
		subcommands[name] = node;
	}
}

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

bool CommandNode::containsSubcommand(string scmd) {
	vector<string>* keys = getPossibleCommands();
	std::vector<string>::iterator it = find(keys->begin(), keys->end(), scmd);
	return it != keys->end();
}

void CommandNode::_walk(vector<string>* cmd) {
	//if (cmd->size() < 1) {
	//	return;
	//}
	if (hasSubcommands) {
		if (!containsSubcommand(cmd->at(0))) {
			return;
		}
		//remove first element from command
		string current_cmd = cmd->at(0);
		cmd->erase(cmd->begin());
		subcommands[current_cmd]->_walk(cmd);
		return;
	}
	else  {
		func(cmd);
		delete cmd;
	}
}
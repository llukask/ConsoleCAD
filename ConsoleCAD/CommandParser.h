#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <map>
#include <vector>

//Node for a tree of commands either contains a tree of CommandNodes (subcommands) 
//or a c-function pointer with the walk function one can walk the tree
class CommandNode {
private:
	bool hasSubcommands;
	void(*func)(std::vector<std::string>* args);
	std::map<std::string, CommandNode*> subcommands;
public:
	CommandNode(void(*func)(std::vector<std::string>* args));
	CommandNode(std::map<std::string, CommandNode*> subcommands);
	CommandNode();
	~CommandNode();
	void AddSubcommand(std::string name, CommandNode* node);
	std::vector<std::string>* getPossibleCommands();
	bool containsSubcommand(std::string scmd);
	void walk(std::string cmd);
	void _walk(std::vector<std::string>* cmd);
};

#endif /* COMMANDPARSER_H */
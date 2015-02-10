#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <map>
#include <vector>

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
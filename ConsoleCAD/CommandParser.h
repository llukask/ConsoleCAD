#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <map>
#include <functional>
#include <vector>

class CommandNode {
private:
	std::map<std::string, CommandNode*> subcommands;
public:
	void walk(std::string cmd);
};

class CommandParser {
	
};

#endif /* COMMANDPARSER_H */
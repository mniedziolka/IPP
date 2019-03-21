#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

bool readGarbage();
bool checkChar(char c);
int32_t getCommand(uint32_t n, char *line, char *command[5]);
uint64_t getHistoryLength(char *line);
uint64_t getEnergy(char *line);

#endif //PARSER_H

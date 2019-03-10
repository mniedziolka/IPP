#ifndef PARSER_H
#define PARSER_H

void callError();
uint8_t readGarbage();
uint8_t checkChar(char c);
int32_t getCommand(uint32_t n, char *line, char *command[5]);
char *getHistory(char *line);
uint64_t getEnergy(char *line);

#endif //PARSER_H
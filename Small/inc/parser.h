#ifndef PARSER_H
#define PARSER_H

uint8_t readGarbage();
uint8_t checkChar(char c);
int32_t getCommand(uint32_t n, char *line, char *command[5]);
int64_t getHistoryLength(char *line);
uint64_t getEnergy(char *line);

#endif //PARSER_H

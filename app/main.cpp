
#include <iostream>
#include "Queue.hpp"
#include <vector>
#include <iomanip>

std::vector<Queue<int>> makeLines(int numOfRegs);
int shortLine(const std::vector<Queue<int>>& regs, int maxLineLen);
int insertCust(std::vector<Queue<int>>& regs, int numOfRegs,int customerCount, int timer, int maxLineLen);
void makeRegTime(int regTime[][2], int numOfRegs);
void enterReg(std::vector<Queue<int>>& regs, int timer, int regTime[][2], int i);
void multiLine(int& totalLost, int& totalEntered, int& totalWait, int& exitedLine,
               int& exitedReg, int regTime[][2], int& LefInLine,int simLen, int numOfRegs, int maxLineLen);
void singleLine(int& totalLost, int& totalEntered, int& totalWait, int& exitedLine,
               int& exitedReg, int regTimeArr[][2], int& LefInLine,int simLen, int numOfRegs, int maxLineLen);

int main()
{
    int simLen, numOfRegs, maxLineLen;
    char lineForm;
    int totalLost = 0;
    int totalEntered = 0;
    int totalWait = 0;
    int exitedLine = 0;
    int exitedReg = 0;
    int leftInLine = 0;
    std::cin >> simLen >> numOfRegs >> maxLineLen >> lineForm;
    simLen *= 60;
    int regTime[numOfRegs][2];
    makeRegTime(regTime, numOfRegs);

    std::cout << "LOG" << std::endl;
    std::cout << "0 start" << std::endl;

    if(lineForm == 'M')
    {
        multiLine(totalLost, totalEntered, totalWait, exitedLine, exitedReg,regTime,
                  leftInLine, simLen, numOfRegs, maxLineLen);
    }

    else if(lineForm == 'S')
    {
        singleLine(totalLost, totalEntered, totalWait, exitedLine, exitedReg,regTime,
                  leftInLine, simLen, numOfRegs, maxLineLen);
    }


    int leftInReg = 0;
    for (int i = 0; i < numOfRegs; i++){
        if (regTime[i][0] > 0){
            leftInReg++;
        }
    }

    std::cout << std::endl << "STATS" << std::endl;
    std::cout << "Entered Line    : " << totalEntered << std::endl;
    std::cout << "Exited Line     : " << exitedLine << std::endl;
    std::cout << "Exited Register : " << exitedReg << std::endl;
    std::cout << "Avg Wait Time   : " << std::setprecision(2)<<std::fixed
              << totalWait/(float)exitedLine << std::endl;
    std::cout << "Left In Line    : " << leftInLine << std::endl;
    std::cout << "Left In Register: " << leftInReg << std::endl;
    std::cout << "Lost            : " << totalLost << std::endl;

    return 0;
}

// Runs the simulation with a single line to the registers
void singleLine(int& totalLost, int& totalEntered, int& totalWait, int& exitedLine,
               int& exitedReg, int regTime[][2], int& leftInLine, int simLen, int numOfRegs, int maxLineLen)
{
    Queue<int> line;
    int timer = 0;
    int customerCount, customerTime;
    std::cin >> customerCount >> customerTime;

    while (timer < simLen) {
        if (customerTime == timer) {
            for (int i = 0; i < customerCount; i++) {
                if (line.size() < maxLineLen) {
                    line.enqueue(timer);
                    std::cout << timer << " entered line length " << line.size() << std::endl;
                    totalEntered++;
                }
                else{
                    std::cout << timer << " lost" << std::endl;
                    totalLost++;
                }
            }
            std::cin >> customerCount >> customerTime;
        }

        for (int i = 0; i < numOfRegs; i++){
            if (regTime[i][0] == regTime[i][1]){
                std::cout << timer << " exited register " << i+1 <<std::endl;
                regTime[i][0] = 0;
                exitedReg++;
            }

            if (regTime[i][0] == 0 && line.size() > 0){
                totalWait += timer - line.front();
                std::cout << timer << " exited line length " << line.size()-1;
                std::cout << " wait time " << timer-line.front() << std::endl;
                std::cout << timer << " entered register " << i+1 << std::endl;
                line.dequeue();
                regTime[i][0] = 5;
                exitedLine++;
            }
            else if (regTime[i][0] > 0){
                regTime[i][0] += 5;
            }

        }

        timer += 5;
    }
    std::cout << simLen << " end" << std::endl;
    leftInLine = line.size();
}

// Runs the simulation with multiple lines, one for each register
void multiLine(int& totalLost, int& totalEntered, int& totalWait, int& exitedLine, int& exitedReg,
               int regTime[][2], int& leftInLine, int simLen, int numOfRegs, int maxLineLen)
{
    std::vector<Queue<int>> regs = makeLines(numOfRegs);
    int timer = 0;
    int customerCount, customerTime;
    std::cin >> customerCount >> customerTime;

    while (timer < simLen){
        if (customerTime == timer){
            int lostInLine = insertCust(regs, numOfRegs, customerCount, timer, maxLineLen);
            totalLost += lostInLine;
            totalEntered += customerCount - lostInLine;
            std::cin >> customerCount >> customerTime;
        }

        for (int i = 0; i < numOfRegs; i++){
            if (regTime[i][0] == regTime[i][1]){
                std::cout << timer << " exited register " << i+1 <<std::endl;
                regTime[i][0] = 0;
                exitedReg++;
            }

            if (regTime[i][0] == 0 && regs[i].size() > 0){
                totalWait += timer - regs[i].front();
                enterReg(regs, timer, regTime, i);
                exitedLine++;
            }
            else if (regTime[i][0] > 0){
                regTime[i][0] += 5;
            }
        }
        timer += 5;
    }

    std::cout << simLen << " end" << std::endl;

    for (int i = 0; i < numOfRegs; i++){
        leftInLine += regs[i].size();
    }
}

// Moves a customer from the line and into the register
void enterReg(std::vector<Queue<int>>& regs, int timer, int regTime[][2], int i)
{
    std::cout << timer << " exited line " << i+1 << " length " << regs[i].size()-1;
    std::cout << " wait time " << timer-regs[i].front() << std::endl;
    std::cout << timer << " entered register " << i+1 << std::endl;
    regs[i].dequeue();
    regTime[i][0] = 5;
}

// creates a vector that holds all the queues, representing lines
std::vector<Queue<int>> makeLines(int numOfRegs)
{
    std::vector<Queue<int>> regs;
    for (int i = 0; i < numOfRegs; i++){
        regs.push_back(Queue<int>());
    }
    return regs;
}

// Creates a two dimensional array with:
// (1) how long customer is in register
// (2) how long is the process time for the register
void makeRegTime(int regTime[][2], int numOfRegs)
{
    for (int i = 0; i < numOfRegs; i++){
        regTime[i][0] = 0;
        std::cin >> regTime[i][1];
    }
}

// Determine the shortest line
// If all the max size then return number of registers
// Otherwise return the shortest line
int shortLine(const std::vector<Queue<int>>& regs, int maxLineLen)
{
    int lineSize = maxLineLen;
    int shortLine;
    for (int i = 0; i < regs.size(); i++){
        if (regs[i].size() < lineSize){
            lineSize = regs[i].size();
            shortLine = i;
        }
    }
    if (lineSize == maxLineLen)
        return regs.size();
    else
        return shortLine;
}

// Insert each of the new customers into the shortest line
// If all lines are full then inform about a lost customer
int insertCust(std::vector<Queue<int>>& regs, int numOfRegs,int customerCount, int timer, int maxLineLen){
    int lost = 0;
    for (int i = 0; i < customerCount; i++){
        int line = shortLine(regs, maxLineLen);
        if (line == numOfRegs){
            std::cout << timer << " lost" << std::endl;
            lost++;
        }
        else{
            regs[line].enqueue(timer);
            std::cout << timer << " entered line " << line+1 << " length " << regs[line].size() << std::endl;
        }
    }
    return lost;
}

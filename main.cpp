#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <vector>
#include <string>
#include <cctype>
#include <mutex>
#include <queue>
#include <conio.h>

// headers
#include "ascii.h"
#include "display.h"
#include "logic.h"

std::atomic<bool> isRunning(true);

std::queue<std::string> commandQueue;
std::mutex queueMutex;

std::string marqueeText;

std::atomic<bool> marqueeActive(false);

int refreshRate = 50;
void keyboardHandler()
{
    std::string command;
    while (isRunning)
    {
        std::getline(std::cin, command);
        if (!command.empty())
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            commandQueue.push(command);
            lock.unlock();
        }
    }
}

void marqueeLogic(int display_width)
{
    while (isRunning)
    {

        while (marqueeActive)
        {
            // Shift the string left by 1 character
            char firstChar = marqueeText[0];
            marqueeText.erase(0, 1);
            marqueeText.push_back(firstChar);

            // Print the marquee
            printLetters(marqueeText);
            fetchDisplay();
            std::cout << "\nCommand> " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(refreshRate));
            system("CLS");
        }
    }
}

void displayHandler()
{
    while (isRunning)
    {

        std::this_thread::sleep_for(std::chrono::milliseconds(refreshRate));
    }
}

int main()
{
    // these threads are already running
    std::thread keyboard_handler_thread(keyboardHandler);
    std::thread marquee_logic_thread(marqueeLogic, 50);
    std::thread display_handler_thread(displayHandler);

    fetchDisplay();
    while (isRunning)
    {
        std::string command;
        std::vector<std::string> tokens;

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (!commandQueue.empty())
            {
                command = commandQueue.front();
                tokens = tokenizeInput(command);
                commandQueue.pop();
            }
        }

        if (!command.empty())
        {
            if (tokens[0] == "exit")
            {
                std::cout << "Terminating interpreter..." << std::endl;
                isRunning = false;
            }
            else if (tokens[0] == "help")
            {
                printLetters("help");
                fetchHelpDisplay();
            }
            else if (tokens[0] == "neofetch")
            {
                printLetters("opesy");
                fetchDisplay();
            }
            else if (tokens[0] == "set_text")
            {
                auto i = 1u;
                marqueeText.clear();
                while (i < tokens.size())
                {
                    marqueeText += tokens[i] + " ";
                    i++;
                }

                if (!marqueeText.empty())
                {
                    marqueeText.pop_back();
                }
                marqueeText += "     ";
                printLetters(marqueeText);
            }
            else if (tokens[0] == "start_marquee")
            {
                marqueeActive = true;
            }
            else if (tokens[0] == "stop_marquee")
            {
                marqueeActive = false;
                system("CLS");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                printLetters(marqueeText);
                fetchDisplay();
            }
            else if (tokens[0] == "set_speed")
            {
                refreshRate = std::stoi(tokens[1]);
            }
            if (isRunning)
            {
                std::cout << "\nCommand> " << std::flush;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}

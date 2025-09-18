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

// headers
#include "ascii.h"
#include "display.h"
#include "logic.h"

std::atomic<bool> isRunning(true);

std::queue<std::string> commandQueue;
std::mutex queueMutex;

std::string marqueeText;

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
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void displayHandler()
{
    const int refreshRate = 50;
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

    bool running = true;
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
                int i = 1;
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
                printLetters(marqueeText);
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

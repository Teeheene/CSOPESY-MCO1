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
std::mutex displayMutex;
std::mutex bufferMutex;

std::string marqueeText;
std::string stringBuffer = "";
std::atomic<bool> marqueeActive(false);

int refreshRate = 50;
void keyboardHandler()
{
    std::string command;
    while (isRunning)
    {
        while (!marqueeActive)
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

            {
                std::lock_guard<std::mutex> lock(displayMutex);
                system("CLS");
                // Print the marquee
                printLetters(marqueeText);
                fetchDisplay();
                {
                    std::lock_guard<std::mutex> lock(bufferMutex);
                    std::cout << "\nCommand> " << stringBuffer << std::flush;
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / (refreshRate + 1)));
        }
    }
}

void displayHandler()
{
    while (isRunning)
    {
        while (marqueeActive)
        {
            if (_kbhit())
            {
                char ch = _getch();
                {
                    std::lock_guard<std::mutex> lock(bufferMutex);
                    if (ch == '\r')
                    {
                        if (!stringBuffer.empty())
                        {
                            std::unique_lock<std::mutex> lock(queueMutex);
                            commandQueue.push(stringBuffer);
                            lock.unlock();
                            stringBuffer = "";
                        }
                    }
                    else if (ch == '\b')
                    {
                        if (!stringBuffer.empty())
                            stringBuffer.pop_back();
                    }
                    else
                    {
                        stringBuffer.push_back(ch);
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
    }
}

int main()
{
    // these threads are already running
    std::thread keyboard_handler_thread(keyboardHandler);
    std::thread marquee_logic_thread(marqueeLogic, 1);
    std::thread display_handler_thread(displayHandler);

    fetchDisplay();
    std::cout << "\nCommand> " << stringBuffer << std::flush;
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
                if (tokens.size() == 1)
                {
                    std::cout << "No text set." << std::endl;
                }
                else
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
            }
            else if (tokens[0] == "start_marquee")
            {
                if (!marqueeText.empty())
                {
                    marqueeActive = true;
                }
                else
                {
                    std::cout << "No text set." << std::endl;
                }
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

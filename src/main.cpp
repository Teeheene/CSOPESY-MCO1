// libraries
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

// global
std::atomic<bool> isRunning(true);
std::atomic<bool> marqueeActive(false);

std::queue<std::string> commandQueue;
std::string marqueeText;
std::string stringBuffer = "";

std::mutex queueMutex;
std::mutex bufferMutex;
std::mutex marqueeMutex;

int refreshRate = 50;

// headers
#include "headers/ascii.h"
#include "headers/display.h"
#include "headers/logic.h"
#include "threads/marqueeHandler.cpp"
#include "threads/keyboardHandler.cpp"

// main
int main()
{
    std::thread display_handler_thread(keyboardHandler);
    std::thread marquee_logic_thread(marqueeHandler);

    fetchDisplay();
    std::cout << "\nCommand> " << std::flush;
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
            	marqueeActive = false;
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
                    std::cout << "WARNING: No text set." << std::endl;
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
                    std::cout << "ERROR: No text set." << std::endl;
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
            	try 
				{
                	refreshRate = std::stoi(tokens[1]);
                	std::cout << "Speed set to " << refreshRate << std::endl;
				} catch (const std::invalid_argument&)
				{
					std::cout << "ERROR: Invalid input. Please enter a number." << std::endl;
				} catch (const std::out_of_range&) 
				{
					std::cout << "ERROR: Number is too large. Please input another number." << std::endl;
				}
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

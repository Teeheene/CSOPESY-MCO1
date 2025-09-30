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
std::mutex marqueeMutex;

std::string marqueeText;
std::string stringBuffer = "";
std::atomic<bool> marqueeActive(false);

int refreshRate = 50;

void keyboardHandler()
{
    while (isRunning)
    {
		if (_kbhit())
		{
			char ch = _getch();
                
			if (ch == '\r')
			{
				std::string localStringBuffer;
				{
					std::lock_guard<std::mutex> lock(bufferMutex);
					localStringBuffer = stringBuffer;
					std::cout << std::endl;
					stringBuffer.clear();
				}
				
				if (!localStringBuffer.empty())
				{
					std::lock_guard<std::mutex> lock(queueMutex);
					commandQueue.push(localStringBuffer);
                }
				    
				{
					std::lock_guard<std::mutex> lock(bufferMutex);
                   	//std::cout << "Command> " << std::flush;
				}
			}
			else if (ch == '\b')
			{
				std::lock_guard<std::mutex> lock(bufferMutex);
				if (!stringBuffer.empty())
				{
					stringBuffer.pop_back();
					std::cout << "\b \b" << std::flush;
				}
            }
			else
			{
				std::lock_guard<std::mutex> lock(bufferMutex);
				stringBuffer.push_back(ch);
				std::cout << ch << std::flush;
			}
        }
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
void marqueeLogic()
{
    while (isRunning)
    {
        while (marqueeActive)
        {
            {
                std::lock_guard<std::mutex> mlock(marqueeMutex);
                if (!marqueeText.empty())
                {
                    // Shift the string left by 1 character (safe because marqueeMutex locked)
                    char firstChar = marqueeText[0];
                    marqueeText.erase(0, 1);
                    marqueeText.push_back(firstChar);
                }
            }
            {
                std::lock_guard<std::mutex> lock(bufferMutex);
                system("CLS");
                // Print the marquee
                printLetters(marqueeText);
                fetchDisplay();
                std::cout << "\nCommand> " << stringBuffer << std::flush;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / (refreshRate + 1)));
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
int main()
{
    // these threads are already running
    std::thread display_handler_thread(keyboardHandler);
    std::thread marquee_logic_thread(marqueeLogic);

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
                	if(refreshRate > 0)
						std::cout << "Speed set to " << refreshRate << std::endl;
					else 
						std::cout << "WARNING: Speed must be greater than 0." << std::endl;
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

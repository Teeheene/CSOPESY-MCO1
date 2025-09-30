void marqueeHandler()
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
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
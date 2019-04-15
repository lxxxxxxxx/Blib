#include "PipeClient.h"

#define PIPE_NAME  "\\\\.\\pipe\\test-pipe_adsfjafas1d6fasd5f5"


int main()
{
	CpipeParma pipePrama{
		PIPE_NAME,   // pipe name 
		 GENERIC_READ |  // read and write access 
		 GENERIC_WRITE,
		 0,              // no sharing 
		 NULL,           // default security attributes
		 OPEN_EXISTING,  // opens existing pipe 
		 FILE_FLAG_OVERLAPPED,              // default attributes 
		 NULL
	};

	PipeClient client(pipePrama);
	if (client.Connect())
	{
		client.Recv();
		client.Dispose();
		std::string msg;
		while (1)
		{
			std::cout << "-----input msg:";
			std::cin >> msg;
			if (msg == "quit")
			{
				return 0;
			}
			std::cout << "-----send msg:" << msg << std::endl;
			client.Send({ const_cast<char*>(msg.c_str()),msg.size() });
		}
	}
	



	return 0;
}
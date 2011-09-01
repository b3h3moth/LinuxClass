#ifndef LINUX_H
#define LINUX_H
#include <vector>
#include <string>
using namespace std;

class Linux
{
	public:
		void setSystemInformation();
		void setUserInformation();
		void setSystemMemory();
		void print();

	private:
		vector<string> systemInfo;
		vector<string> userLogin;
		vector<int> sysMemory;
};

#endif

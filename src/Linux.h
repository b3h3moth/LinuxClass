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
		void setUserPw();

		// System information obtained through ustname struct
		string getSysSysname();
		string getSysNodename();
		string getSysRelease();
		string getSysVersion();
		string getSysMachine();

		// User information obtained through getlogin(), getuid(), getgid()
		string getUserLogin();
		string getUserUid();
		string getUserGid();

		// System information obtained through sysinfo struct
		int getSysTotalram();
		int getSysFreeram();
		int getSysTotalswap();
		int getSysFreeswap();
		
		// User information obtained through passwd struct
		string getUserPwname();
		string getUserPwdir();
		string getUserPwshell();
		
		void print();

	private:
		vector<string> systemInfo;
		vector<string> userInfo;
		vector<int> sysMemory;
		vector<string> userPw;
		// Utility functions: Type conversions
		int convStrToInt(string str);
};

#endif

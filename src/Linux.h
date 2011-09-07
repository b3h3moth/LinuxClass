#ifndef LINUX_H
#define LINUX_H
#include <vector>
#include <string>
using namespace std;

class Linux
{
	public:
		Linux();
		void setSystemInformation();
		void setUserInformation();
		void setSystemMemory();
		void setUserPw();
		void setFileSystemInfo();

		// System information obtained through ustname struct
		string getSysSysname();
		string getSysNodename();
		string getSysRelease();
		string getSysVersion();
		string getSysMachine();

		// User information obtained through getlogin(), getuid(), etc...
		string getUserLogin();
		string getRealUid();
		string getEffectiveUid();
		string getRealGid();
		string getEffectiveGid();

		// System information obtained through sysinfo struct
		int getSysTotalram();
		int getSysFreeram();
		int getSysTotalswap();
		int getSysFreeswap();
		
		// User information obtained through passwd struct
		string getUserPwname();
		string getUserPwdir();
		string getUserPwshell();

		// File system Information through statvfs() System Call
		unsigned long getFsDiskSize();
		unsigned long getFsDiskFree();
		unsigned long getFsDiskUsed();
		
		void print();

	private:
		vector<string> systemInfo;
		vector<string> userInfo;
		vector<int> sysMemory;
		vector<string> userPw;
		vector<unsigned long> fsInfo;

		// Utility functions: Type conversions
		int convStrToInt(string str);
		string convIntToStr(int val);
};

#endif

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

		// System information inside utsname structure
		void getSysSysname();
		void getSysNodename();
		void getSysRelease();
		void getSysVersion();
		void getSysMachine();

		// User information to get login, uid and gid
		void getUserLogin();
		void getUserUid();
		void getUserGid();

		// System information inside sysinfo structure
		void getSysTotalram();
		void getSysFreeram();
		void getSysTotalswap();
		void getSysFreeswap();
		
		void print();

	private:
		vector<string> systemInfo;
		vector<string> userInfo;
		vector<int> sysMemory;
};

#endif

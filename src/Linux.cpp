#include <iostream>
#include <sstream>
using namespace std;
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <pwd.h>
#include "Linux.h"


Linux::Linux()
{
	setSystemInformation();
	setUserInformation();
	setSystemMemory();
	setUserPw();
}

void Linux::setSystemInformation()
{
	struct utsname uts;
	
	if (uname (&uts) == 0)
	{
		systemInfo.push_back (uts.sysname);
		systemInfo.push_back (uts.nodename);
		systemInfo.push_back (uts.release);
		systemInfo.push_back (uts.version);
		systemInfo.push_back (uts.machine);
	}
}

void Linux::setUserInformation()
{
	// These SysCall are always successful.
	uid_t realUid = getuid();	// Real User ID
	uid_t effUid = geteuid();	// Effective User ID
	gid_t realGid = getgid();	// Real Group ID
	gid_t effGid = getegid();	// Effective Group ID
	
	userInfo.push_back(getlogin());
	userInfo.push_back(convIntToStr(realUid));
	userInfo.push_back(convIntToStr(effUid));
	userInfo.push_back(convIntToStr(realGid));
	userInfo.push_back(convIntToStr(effGid));
}

void Linux::setSystemMemory()
{
	struct sysinfo info;
	
	if (sysinfo (&info) == 0)
	{
		sysMemory.push_back(info.totalram / (1024 * 1024));
		sysMemory.push_back(info.freeram / (1024 * 1024));
		sysMemory.push_back(info.totalswap / (1024 * 1024));
		sysMemory.push_back(info.freeswap / (1024 * 1024));
	}
}

void Linux::setUserPw()
{
	struct passwd *pd;

	if ((pd = getpwuid(convStrToInt(getRealUid()))) != NULL)
	{
		userPw.push_back(pd->pw_name);
		userPw.push_back(pd->pw_dir);
		userPw.push_back(pd->pw_shell);
	}
}

string Linux::getSysSysname()
{
	return systemInfo[0];
}

string Linux::getSysNodename()
{
	return systemInfo[1];
}

string Linux::getSysRelease()
{
	return systemInfo[2];
}

string Linux::getSysVersion()
{
	return systemInfo[3];
}

string Linux::getSysMachine()
{
	return systemInfo[4];
}

string Linux::getUserLogin()
{
	return userInfo[0];
}

string Linux::getRealUid()
{
	return userInfo[1];
}

string Linux::getEffectiveUid()
{
	return userInfo[2];
}

string Linux::getRealGid()
{
	return userInfo[3];
}

string Linux::getEffectiveGid()
{
	return userInfo[4];
}

int Linux::getSysTotalram()
{
	return sysMemory[0];
}

int Linux::getSysFreeram()
{
	return sysMemory[1];
}

int Linux::getSysTotalswap()
{
	return sysMemory[2];
}

int Linux::getSysFreeswap()
{
	return sysMemory[3];
}

string Linux::getUserPwname()
{
	return userPw[0];
}

string Linux::getUserPwdir()
{
	return userPw[1];
}

string Linux::getUserPwshell()
{
	return userPw[2];
}

void Linux::print()
{
  //for (int i=0; i<systemInfo.size(); i++)
  //      cout << systemInfo[i] << endl;
  cout << "INFO ABOUT KERNEL" << endl;
  cout << "Operating System: \"" << getSysSysname() << "\", "
  	   << "Hostname (nodename): \"" << getSysNodename() << "\",\n"
	   << "Release: \"" << getSysRelease() << "\", "
	   << "Version: \"" << getSysVersion() << "\",\n"
       << "Hardware type: \"" << getSysMachine() << "\"\n\n";
  cout << "Login, UID, GID" << endl;
  cout << "User Login: \"" << getUserLogin() << "\", "
       << "Real UID: \"" << getRealUid() << "\", "
       << "Effective UID: \"" << getEffectiveUid() << "\"\n"
       << "Real GID: \"" << getRealGid() << "\", "
       << "Effective GID: \"" << getEffectiveGid() << "\"\n\n";
  cout << "INFO ABOUT MEMORY" << endl;
  cout << "Total Memory: \"" << getSysTotalram() << " MB\", "
       << "Free Memory: \"" << getSysFreeram() << " MB\",\n"
       << "Total Swap: \"" << getSysTotalswap() << " MB\", "
       << "Free Swap: \"" << getSysFreeswap() << " MB\"\n\n";
  cout << "INFO FROM /etc/passwd" << endl;
  cout << "User name: \"" << getUserPwname() << "\", "
  	   << "Initial directory: \"" << getUserPwdir() << "\",\n"
	   << "Default shell: \"" << getUserPwshell() << "\"\n";
  	   
}

// Utility functions; they aren't member functions
// Convert string to int
int Linux::convStrToInt(string str)
{
	int intNumber;
	stringstream s(str);
	s >> intNumber;

	return intNumber;
}

// Convert int to string
string Linux::convIntToStr(int val)
{
	stringstream s;
	s << val;

	return s.str();
}

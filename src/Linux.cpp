#include <iostream>
#include <sstream>
using namespace std;
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <pwd.h>
#include "Linux.h"


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
	uid_t uid = getuid();
	gid_t gid = getgid();
	
	stringstream uidConv;
	stringstream gidConv;
	uidConv << uid;
	gidConv << gid;
	
	userInfo.push_back(getlogin());
	userInfo.push_back(uidConv.str());
	userInfo.push_back(gidConv.str());
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
	
	pd = getpwuid(1001);
	userPw.push_back(pd->pw_name);
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

string Linux::getUserUid()
{
	return userInfo[1];
}

string Linux::getUserGid()
{
	return userInfo[2];
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

void Linux::print()
{
  //for (int i=0; i<systemInfo.size(); i++)
  //      cout << systemInfo[i] << endl;
  cout << "Operating System: \"" << getSysSysname() << "\", "
  	   << "Hostname (nodename): \"" << getSysNodename() << "\",\n"
	   << "Release: \"" << getSysRelease() << "\", "
       << "Version: \"" << getSysVersion() << "\",\n"
       << "Hardware type: \"" << getSysMachine() << "\"\n";
  cout << "User Login: \"" << getUserLogin() << "\", "
       << "UID: \"" << getUserUid() << "\", "
       << "GID: \"" << getUserGid() << "\"\n";
  cout << "Total Memory: \"" << getSysTotalram() << " MB\", "
       << "Free Memory: \"" << getSysFreeram() << " MB\",\n"
       << "Total Swap: \"" << getSysTotalswap() << " MB\", "
       << "Free Swap: \"" << getSysFreeswap() << " MB\"\n";
  cout << "/etc/passwd User name: \"" << getUserPwname() << "\", ";
}

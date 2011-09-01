#include <iostream>
#include <sstream>
using namespace std;
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
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
	
	userLogin.push_back (getlogin());
	userLogin.push_back (uidConv.str());
	userLogin.push_back (gidConv.str());
}

void Linux::setSystemMemory()
{
	struct sysinfo info;
	
	if (sysinfo (&info) == 0)
	{
		sysMemory.push_back (info.totalram / (1024 * 1024));
		sysMemory.push_back (info.freeram / (1024 * 1024));
		sysMemory.push_back (info.totalswap / (1024 * 1024));
		sysMemory.push_back (info.freeswap / (1024 * 1024));
	}
}

void Linux::getSysSysname()
{
	return systemInfo[0];
}

void Linux::getSysNodename()
{
	return systemInfo[1];
}

void Linux::getSysRelease()
{
	return systemInfo[2];
}

void Linux::getSysVersion()
{
	return systemInfo[3];
}

void Linux::getSysMachine()
{
	return systemInfo[4];
}

void Linux::getUserLogin()
{
	return userInfo[0];
}

void Linux::getUserUid();
{
	return userInfo[1];
}

void Linux::getUserGid()
{
	return userInfo[2];
}

void Linux::getSysTotalram()
{
	return sysMemory[0];
}

void Linux::getSysFreeram()
{
	return sysMemory[1];
}

void Linux::getSysTotalswap()
{
	return sysMemory[2];
}

void Linux::getSysFreeswap()
{
	return sysMemory[3];
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
}

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

void Linux::print()
{
  //for (int i=0; i<systemInfo.size(); i++)
  //      cout << systemInfo[i] << endl;
  cout << "Operating System: \"" << systemInfo[0] << "\", "
  	   << "Hostname (nodename): \"" << systemInfo[1] << "\",\n"
	   << "Release: \"" << systemInfo[2] << "\", "
       << "Version: \"" << systemInfo[3] << "\",\n"
       << "Hardware type: \"" << systemInfo[4] << "\"\n";
  cout << "User Login: \"" << userLogin[0] << "\", "
       << "UID: \"" << userLogin[1] << "\", "
       << "GID: \"" << userLogin[2] << "\"\n";
  cout << "Total Memory: \"" << sysMemory[0] << " MB\", "
       << "Free Memory: \"" << sysMemory[1] << " MB\",\n"
       << "Total Swap: \"" << sysMemory[2] << " MB\", "
       << "Free Swap: \"" << sysMemory[3] << " MB\"\n";
}

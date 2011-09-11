#include <iostream>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <pwd.h>

#include "Linux.h"


Linux::Linux()
{
	setSystemInformation();
	setUserInformation();
	setSystemMemory();
	setUserPw();
	setFileSystemInfo();
}

void Linux::setSystemInformation()
{
	struct utsname uts;
	
	if (uname (&uts) < 0)
		exit(EXIT_FAILURE);
	else {
		systemInfo.push_back(uts.sysname);
		systemInfo.push_back(uts.nodename);
		systemInfo.push_back(uts.release);
		systemInfo.push_back(uts.version);
		systemInfo.push_back(uts.machine);
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
	
	if (sysinfo (&info) < 0)
		exit(EXIT_FAILURE);
	else {
		sysMemory.push_back(info.totalram / (1024 * 1024));
		sysMemory.push_back(info.freeram / (1024 * 1024));
		sysMemory.push_back(info.totalswap / (1024 * 1024));
		sysMemory.push_back(info.freeswap / (1024 * 1024));
	}
}

void Linux::setUserPw()
{
	struct passwd *pd;

	if ((pd = getpwuid(convStrToInt(getRealUid()))) == NULL)
		exit(EXIT_FAILURE);
	else {
		userPw.push_back(pd->pw_name);
		userPw.push_back(pd->pw_dir);
		userPw.push_back(pd->pw_shell);
	}
}

void Linux::setFileSystemInfo()
{
	struct statvfs hdd;
	unsigned long long block_size, blocks, blocks_free; 
	double disk_size, disk_used, disk_free;

	if (statvfs( getUserPwdir().c_str(), &hdd) < 0)
		exit(EXIT_FAILURE);
	else {
		block_size = hdd.f_bsize;
		blocks = hdd.f_blocks;
		blocks_free = hdd.f_bfree;

		disk_size = (double)(blocks * block_size)/(1024*1024);
		disk_free = (double)(blocks_free * block_size)/(1024*1024);
		disk_used = (double)(disk_size - disk_free);

		fsInfo.push_back(disk_size);
		fsInfo.push_back(disk_used);
		fsInfo.push_back(disk_free);
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

double Linux::getFsDiskSize()
{
	return fsInfo[0];
}

double Linux::getFsDiskFree()
{
	return fsInfo[1];
}

double Linux::getFsDiskUsed()
{
	return fsInfo[2];
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
	   << "Default shell: \"" << getUserPwshell() << "\"\n\n";
  cout << "FILE SYSTEM " << getUserPwdir() << "\"" << endl;
  cout << "Disk size: \"" << getFsDiskSize() << "\" MB\n"
  	   << "Disk free: \"" << getFsDiskFree() << "\" MB\n"
  	   << "Disk used: \"" << getFsDiskUsed() << "\" MB\n";
  	   
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

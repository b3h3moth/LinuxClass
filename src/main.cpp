using namespace std;
#include <iostream>

#include "Linux.h"

int main() {
	Linux ogg;
	
	cout << "INFO ABOUT KERNEL" << endl;
	cout << "Operating System: \"" << ogg.getSysSysname() << "\", "
  	   << "Hostname (nodename): \"" << ogg.getSysNodename() << "\",\n"
	   << "Release: \"" << ogg.getSysRelease() << "\", "
	   << "Version: \"" << ogg.getSysVersion() << "\",\n"
	   << "Hardware type: \"" << ogg.getSysMachine() << "\"\n\n";
	
	cout << "Login, UID, GID" << endl;
	cout << "User Login: \"" << ogg.getUserLogin() << "\", "
	   << "Real UID: \"" << ogg.getRealUid() << "\", "
           << "Effective UID: \"" << ogg.getEffectiveUid() << "\"\n"
           << "Real GID: \"" << ogg.getRealGid() << "\", "
           << "Effective GID: \"" << ogg.getEffectiveGid() << "\"\n\n";
        cout << "INFO ABOUT MEMORY" << endl;
        cout << "Total Memory: \"" << ogg.getSysTotalram() << " MB\", "
           << "Free Memory: \"" << ogg.getSysFreeram() << " MB\",\n"
           << "Total Swap: \"" << ogg.getSysTotalswap() << " MB\", "
           << "Free Swap: \"" << ogg.getSysFreeswap() << " MB\"\n\n";
        cout << "INFO FROM /etc/passwd" << endl;
        cout << "User name: \"" << ogg.getUserPwname() << "\", "
  	   << "Initial directory: \"" << ogg.getUserPwdir() << "\",\n"
	   << "Default shell: \"" << ogg.getUserPwshell() << "\"\n\n";
        cout << "FILE SYSTEM " << ogg.getUserPwdir() << "\"" << endl;
        cout << "Disk size: \"" << ogg.getFsDiskSize() << "\" MB\n"
  	   << "Disk free: \"" << ogg.getFsDiskFree() << "\" MB\n"
  	   << "Disk used: \"" << ogg.getFsDiskUsed() << "\" MB\n";
  	   

	return(0);
}

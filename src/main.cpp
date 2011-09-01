#include "Linux.h"

int main() {
	Linux ogg;
	ogg.setSystemInformation();
	ogg.setUserInformation();
	ogg.setSystemMemory();
	ogg.setUserPw();
	ogg.print();

	return(0);
}


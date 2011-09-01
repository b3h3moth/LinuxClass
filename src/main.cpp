#include "Linux.h"

int main() {
	Linux ogg;
	ogg.setSystemInformation();
	ogg.setUserInformation();
	ogg.setSystemMemory();
	ogg.print();

	return(0);
}


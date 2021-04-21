#include "top.h"

int main()
{
	AlgorithmBC algorithmBC;
	algorithmBC.PackCtrl.SendPackage(Subaddrs::SDT);
	algorithmBC.StartMovement();
	
	while(true){
		algorithmBC.ProcessIvents();
	}
}

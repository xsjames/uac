//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  main
//
//=============================================================================
#include <iostream>
#include "engine.h"
#include "main/maindefines.h"



void main(int argc, char* argv[])
{
	int r;

	r = InitEngine();
	if(r == RETURN_CONTINUE)
	{
		StartEngine();
	}
	ClearEngine();


#ifdef _DEBUG
	int i;
	std::cin >> i;
#endif
}

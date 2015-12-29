//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  UAC logging system
//
//=============================================================================

#include <stdarg.h>
/*
#include <stdio.h>
#include <string.h>
*/
#include "debug/out.h"

//TEMP
#include <iostream>


#define STD_BUFFER_SIZE 3000


namespace UAC
{
namespace Common
{

namespace Out
{
	/*
    struct OutputTargetSlot
    {
    public:
        IOutputTarget   *DelegateObject;
        // target-specific verbosity setting
        OutputVerbosity Verbosity;
        // TODO: use safer technique instead of remembering that ptr is shared
        bool            IsShared;
        bool            IsSuppressed;

        OutputTargetSlot(IOutputTarget *output_target, OutputVerbosity verbosity, bool shared_object)
        {
            DelegateObject  = output_target;
            Verbosity       = verbosity;
            IsShared        = shared_object;
            IsSuppressed    = false;
        }

        ~OutputTargetSlot()
        {
            if (!IsShared) {
                delete DelegateObject;
            }
        }
    };
	*/
	struct InternalData
	{
	public:
		// general verbosity setting
		OutputVerbosity     Verbosity;
		//OutputTargetSlot    *Targets[MAX_TARGETS];

		InternalData()
		{
			Verbosity = ovALWAYS;
			//memset(Targets, 0, sizeof(Targets));
		}
	};

	InternalData IData;


	/*
	// Internal va_list version of Out()
    void VOut  (OutputVerbosity reason, const char *sz_msg, va_list argptr);
	

    // Check verbosity settings to check if it is permitted to
    // print a message for given reason
    inline bool GetOutputPermission (OutputVerbosity verbosity, OutputVerbosity reason = kVerbose_Always);
	*/

	/*

//-----------------------------------------------------------------------------
// System management
//-----------------------------------------------------------------------------
void Out::Init (int cmdarg_count, char **cmdargs)
{
    // TODO: check cmdargs to set up the settings
    //
    //
    IData.Verbosity = kVerbose_Always; //play.debug_mode != 0 ? kVerbose_Always : 0;

    //-------------------------------------------
    //
}

void Out::AddOutputTarget(int target_id, Out::IOutputTarget *output_target, OutputVerbosity verbosity, bool shared_object)
{
    // TODO: use array class instead
    if (target_id < 0 || target_id >= MAX_TARGETS) {
        Out::Warn("Output system: unable to add target output, because id %d is out of range", target_id);
        return;
    }

    delete IData.Targets[target_id];
    IData.Targets[target_id] = new OutputTargetSlot(output_target, verbosity, shared_object);
}

void Out::RemoveOutputTarget(int target_id)
{
    if (target_id >= 0 && target_id < MAX_TARGETS)
    {
        delete IData.Targets[target_id];
        IData.Targets[target_id] = NULL;
    }
}

void Out::Shutdown ()
{
    // release any memory, resources etc here

    for (int i = 0; i < MAX_TARGETS; ++i)
    {
        delete IData.Targets[i];
        IData.Targets[i] = NULL;
    }
}
*/

//-----------------------------------------------------------------------------
// Verbosity setting
//-----------------------------------------------------------------------------
inline bool GetOutputPermission(OutputVerbosity verbosity, OutputVerbosity reason)
{
	// verbosity is tested against kVerbose_DoLog separately,
	// since reason is not required to has that bit set
	return (verbosity & ovDOLOG) != 0 && (verbosity & reason) != 0;
}


//-----------------------------------------------------------------------------
// Do actual print
//----------------------------------------------------------------------------
void Print(OutputVerbosity reason, const char *sz_msg)
{
	if(reason & ovINFO)
		std::cout << "[INFO]    - " << sz_msg << "\n";
	else if(reason & ovDEBUG)
		std::cout << "[DEBUG]   - " << sz_msg << "\n";
	else if(reason & ovWARN)
		std::cout << "[WARNING] - " << sz_msg << "\n";
	else if(reason & ovERROR)
		std::cout << "[ERROR]   - " << sz_msg << "\n";
	else if(reason & ovFATAL)
		std::cout << "[FATAL]   - " << sz_msg << "\n";

	/*
	for (int i = 0; i < MAX_TARGETS; ++i)
	{
	OutputTargetSlot *target = IData.Targets[i];
	if (!target || !target->DelegateObject)
	{
		continue;
	}

	if (target->IsSuppressed)
	{
		continue;
	}
	if (!GetOutputPermission(target->Verbosity, reason))
	{
		continue;
	}

	// We suppress current target here  so that if it makes a call
	// to output system itself, message would not print to the
	// same target
	target->IsSuppressed = true;
	target->DelegateObject->Out(sz_msg);
	target->IsSuppressed = false;
	}
	*/
}


//-----------------------------------------------------------------------------
// Internal va_list wrapper over print()
//-----------------------------------------------------------------------------
void VPrint(OutputVerbosity reason, const char *sz_msg, va_list argptr)
{
	// Make a formatted string
	char buffer[STD_BUFFER_SIZE];
	vsprintf(buffer, sz_msg, argptr);

	// TODO: Optionally add information here (room index, etc) (?)
	//

	// Send final message to Targets
	Print(reason, buffer);
}


//-----------------------------------------------------------------------------
// Make an output with regard to verbosity settings
//-----------------------------------------------------------------------------
void Out(OutputVerbosity reason, const char *sz_msg, ...)
{
	if(!GetOutputPermission(IData.Verbosity, reason))
	{
		return;
	}

	va_list argptr;
	va_start(argptr, sz_msg);
	Out::VPrint(reason, sz_msg, argptr);
	va_end(argptr);
}


//-----------------------------------------------------------------------------
// Force print: make an output regardless of verbosity settings
//-----------------------------------------------------------------------------
void FPrint(const char *sz_msg, ...)
{
	va_list argptr;
	va_start(argptr, sz_msg);
	Out::VPrint(ovALWAYS, sz_msg, argptr);
	va_end(argptr);
}


}   // namespace Out

}   // namespace Common
}   // namespace AGS

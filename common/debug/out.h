//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  Logging system
//
//=============================================================================
#ifndef __UAC__OUT_H
#define __UAC__OUT_H


// Convenience functions, with regard to verbosity settings
#ifdef  NDEBUG
#define LOG_DEBUG(...) ((void)0)
#else
#define LOG_DEBUG(...) UAC::Common::Out::Out(UAC::Common::Out::ovDEBUG, __VA_ARGS__);
#endif  // NDEBUG

#define LOG_INFO(...) UAC::Common::Out::Out(UAC::Common::Out::ovINFO, __VA_ARGS__);
#define LOG_WARN(...) UAC::Common::Out::Out(UAC::Common::Out::ovWARN, __VA_ARGS__);
#define LOG_ERROR(...) UAC::Common::Out::Out(UAC::Common::Out::ovERROR, __VA_ARGS__);
#define LOG_FATAL(...) UAC::Common::Out::Out(UAC::Common::Out::ovFATAL, __VA_ARGS__);

#define LOG(LEVEL) LOG_##LEVEL


namespace UAC
{
namespace Common
{

namespace Out
{
	// Verbosity
	enum OutputVerbosity
	{
		ovNEVER  = 0,
		ovDOLOG  = 0x0001, // do log (otherwise do not, C.O.)

		// DEBUG reason is for random information about current game state,
		// like outputting object values, or telling that execution has
		// passed certain point in the function
		ovDEBUG  = 0x0002,
		// INFOs are made when the program is passing important
		// checkpoints, like initializing or shutting engine down, or
		// when program decides to make a workaround to solve some problem
		ovINFO   = 0x0004,
		// WARNings are made when unexpected or generally strange behavior
		// is detected in program, which does not necessarily mean error,
		// but still may be a symptom of a bigger problem
		ovWARN   = 0x0008,
		// ERRORs are ones that were 'fixed' by the program on run;
		// There's high chance that program will continue running as normal,
		// but message should be maid to bring user or dev's attention
		ovERROR  = 0x0010,
		// FATAL errors are errors that program was not able to fix;
		// program abort immediately
		ovFATAL  = 0x0020,
		/*
		// Convenience aliases
		ovNODEBUG        = 0x007D,
		ovWARNERRORS     = 0x0079,
		*/
		// Just print out the damned message!
		ovALWAYS = 0x00FF
	};

	/*
	// System management
	void Init (int cmdarg_count, char **cmdargs);
	// TODO: use safer technique like shared ptrs or reference counted objects
	// instead of telling that ptr is shared
	void AddOutputTarget(int target_id, IOutputTarget *output_target, OutputVerbosity verbosity, bool shared_object);
	void RemoveOutputTarget(int target_id);
	void Shutdown ();
	*/

	// Make an output with regard to verbosity settings
	void Out(OutputVerbosity reason, const char *sz_msg, ...);


	// Force print: output message regardless of verbosity settings
	// This will make an output even if kVerbose_DoLog is not set
	void FPrint(const char *sz_msg, ...);

}   // namespace Out

}   // namespace Common
}   // namespace AGS

#endif // __UAC__OUT_H

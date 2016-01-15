//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface
//
//=============================================================================

#ifdef USE_ASLIB

#include <assert.h>  // assert()
#include "script/script_as.h"
#include "script/scriptstdstring/scriptstdstring.h" // script std::string
#include "script/scriptbuilder/scriptbuilder.h"
#include "script/script_as_global.h"
#include "script/script_as_color.h"
#include "script/script_as_scene.h"
#include "script/script_as_camera.h"
#include "script/script_as_light.h"
#include "script/script_as_mesh.h"
#include "debug/out.h"


namespace UAC
{

using namespace Common;

namespace Engine
{

// Implement a simple message callback function
void MessageCallback(const asSMessageInfo *msg, void *param)
{
	char real_message[256];
	sprintf_s(real_message, 256, "%s (%d, %d) : %s\n", msg->section, msg->row, msg->col, msg->message);

	if(msg->type == asMSGTYPE_WARNING)
	{
		LOG(WARN)("AngelScript: %s", real_message);
	}
	else if(msg->type == asMSGTYPE_INFORMATION)
	{
		LOG(INFO)("AngelScript: %s", real_message);
	}
	else
	{
		LOG(ERROR)("AngelScript: %s", real_message);
	}
}


bool ScriptAS::Init()
{
	int r;

	// Create the script engine
	_engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	if(!_engine) return false;

	// Set the message callback to receive information on errors in human readable form.
	r = _engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
	if(r < 0) return false; // an error has occurred

	RegisterGameInterface();


	_ctx = _engine->CreateContext();
	if (_ctx == 0)
	{
		LOG(ERROR)("Failed to create the context.");
		return false;
	}


	r = LoadScript();
	if(r < 0) return false; // an error has occurred

	return true;
}


void ScriptAS::Shutdown()
{
	if(_ctx)
	{
		_ctx->Release();
		_ctx = 0;
	}

	if(_engine)
	{
		_engine->ShutDownAndRelease();
		_engine = 0;
	}
}


void ScriptAS::RegisterGameInterface()
{
	// Register the script string type (STD String)
	RegisterStdString(_engine);
	
	// Register the engine global functions
	RegisterGlobalFunctions(_engine);

	// Register the engine objects
	RegisterColor(_engine);
	RegisterScene(_engine);
	RegisterCamera(_engine);
	RegisterLight(_engine);
	RegisterMesh(_engine);
}


int ScriptAS::LoadScript()
{
	int r;

	// The CScriptBuilder helper is an add-on that loads the file,
	// performs a pre-processing pass if necessary, and then tells
	// the engine to build a script module.
	CScriptBuilder builder;
	r = builder.StartNewModule(_engine, "BasicModule"); 
	if(r < 0)
	{
		// If the code fails here it is usually because there
		// is no more memory to allocate the module
		LOG(ERROR)("Unrecoverable error while starting a new module.");
		return r;
	}
	r = builder.AddSectionFromFile("script.as");
	if(r < 0)
	{
		// The builder wasn't able to load the file. Maybe the file
		// has been removed, or the wrong name was given, or some
		// preprocessing commands are incorrectly written.
		LOG(ERROR)("Please correct the errors in the script and try again.");
		return r;
	}
	r = builder.BuildModule();
	if(r < 0)
	{
		// An error occurred. Instruct the script writer to fix the 
		// compilation errors that were listed in the output stream.
		LOG(ERROR)("Please correct the errors in the script and try again.");
		return r;
	}

	// Find the function that is to be called. 
	asIScriptModule* mod = _engine->GetModule("BasicModule");

	_script_functions[Global_GameStart] = mod->GetFunctionByDecl("void GameStart()");
	if(_script_functions[Global_GameStart] == 0)
	{
		LOG(ERROR)("The script must have the function 'void GameStart()'. Please add it and try again.");
		return -1;
	}

	_script_functions[Global_RepeatedlyExecute] = mod->GetFunctionByDecl("void RepeatedlyExecute()");
	if(_script_functions[Global_RepeatedlyExecute] == 0)
	{
		LOG(ERROR)("The script must have the function 'void RepeatedlyExecute()'. Please add it and try again.");
		return -1;
	}

	return r;
}


void ScriptAS::Execute_GlobalFunction(ScriptGlobalFunctionIDs func_id)
{
	if(_ctx)
	{
		_ctx->Prepare(_script_functions[func_id]);
		int r = _ctx->Execute();
		if(r != asEXECUTION_FINISHED)
		{
			// The execution didn't complete as expected. Determine what happened.
			if(r == asEXECUTION_EXCEPTION)
			{
				// An exception occurred, let the script writer know what happened so it can be corrected.
				LOG(ERROR)("An exception occurred: %s", _ctx->GetExceptionString());
			}
		}
	}
}


void ScriptAS::Execute_SceneFunction(ScriptSceneFunctionIDs func_id)
{
}


} // namespace Engine
} // namespace UAC

#endif // USE_ASLIB

//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  UAC Engine
//
//=============================================================================
#include "main/engine.h"
#include "main/maindefines.h"
#include "main/version.h"
#include "scene/scene_helper.h"
#include "debug/debug.h"
#include "debug/out.h"
#include "device/device_helper.h"
#include "script/script_helper.h"


using namespace UAC::Common;
using namespace UAC::Engine;


//-----------------------------------------------------------------------------
// Global vars
//----------------------------------------------------------------------------
IDevice* g_pDevice = 0;
ISceneManager* g_pSceneManager = 0;
IScript* g_pScripting = 0;



bool engine_init_gfx()
{
	if(g_pDevice)
	{
		DisplayMode dm;
		dm.Width = 640;
		dm.Height = 480;
		dm.ColorDepth = 16;
		dm.Windowed = true;

		if(g_pDevice->InitGFX(dm))
			return true;
	}
	return false;
}


int engine_run_game()
{
	LOG(INFO)("Run game");

	//TEMP
	while(g_pDevice->Run())
	{
		g_pScripting->Execute_GlobalFunction(Global_RepeatedlyExecute);

		g_pSceneManager->Update();
		g_pSceneManager->Render();
	}

	/*
	while(device->run())
    {
        if (device->isWindowActive())
        {
            // draw everything here
        }
        else
            device->yield();
    }

	/*
	int state = 0;

	state = LoadFirstScene();

	while(state != GAME_STATE_ABORT)
	{
		state = UpdateCurrentScene();

		if(state == GAME_STATE_CHANGE_SCENE)
		{
			state = LoadNextScene(next_scene);
			continue;
		}

		CheckFPS();
	}
	*/
	return RETURN_CONTINUE;
}



int InitEngine()
{
	LOG(INFO)("UAC Engine v%.2f", UAC_ENGINE_VERSION);

	// init debug system
	InitDebugSubsystem();


	LOG(INFO)("Create device");
	if(!CreateDevice(&g_pDevice))
	{
		LOG(ERROR)("Unable to create device");
		return EXIT_NORMAL;
	}


	LOG(INFO)("Create scene manager");
	if(!CreateSceneManager(&g_pSceneManager))
	{
		LOG(ERROR)("Unable to create scene manager");
		return EXIT_NORMAL;
	}

	
	LOG(INFO)("Create scripting system");
	if(!CreateScriptingSystem(&g_pScripting))
	{
		LOG(ERROR)("Unable to create scripting system");
		return EXIT_NORMAL;
	}

	/*
	LOG(INFO)("Create asset manager");
	AssetManager::CreateInstance();
	AssetManager::SetSearchPriority(kAssetPriorityDir);
	*/
	return RETURN_CONTINUE;
}


void ClearEngine()
{
	LOG(INFO)("Clean-up Engine");
	

	LOG(INFO)("Shutdown scripting system");
	DestroyScriptingSystem(&g_pScripting);


	LOG(INFO)("Shutdown scene manager");
	DestroySceneManager(&g_pSceneManager);


	LOG(INFO)("Shutdown device");
	DestroyDevice(&g_pDevice);

	/*
	LOG(INFO)("Shutdown asset manager");
	AssetManager::DestroyInstance();
	*/

	// shutdown debug system
	ShutdownDebugSubsystem();
}


int StartEngine()
{
	int res = 0;
	LOG(INFO)("*** ENGINE STARTUP ***");


	LOG(INFO)("Init device... gfx... scene manager... ");
	g_pDevice->Init();
	// init graphics mode based on game resolution
	res = engine_init_gfx();
	if(res != RETURN_CONTINUE)
	{
		LOG(ERROR)("Unable to init GFX");
		return res;
	}
	//
	g_pSceneManager->Init(g_pDevice);

	//TEMP g_pSceneManager->LoadScenesFromFile();

	//TEMP
	LOG(INFO)("Init scripting system");
	if(!g_pScripting->Init())
		return -1; //TEMP

	LOG(INFO)("Execute script: void GameStart()");
	g_pScripting->Execute_GlobalFunction(Global_GameStart);

	engine_run_game();

	return RETURN_CONTINUE;
}



/*
#define GAME_STATE_RUN				0
#define GAME_STATE_ABORT			-1
#define GAME_STATE_CHANGE_SCENE		1


bool abort = false;
std::vector<Scene*> scenes;
Scene* currentScene;


int LoadScene(int num)
{
	currentScene = scenes[num];
	return GAME_STATE_RUN;
}

void ClearScene(Scene* s)
{
	//"chiude" la scena ripulendo la memoria
}

int LoadFirstScene()
{
	return LoadScene(__first_scene);
}

int LoadNextScene(int next)
{
	ClearScene(currentScene);
	return LoadScene(next);
}


int UpdateCurrentScene()
{
	//aggiorna script
	//aggiorna posizione mouse
	//aggiorna eventi
	//render della scena
	return = GAME_STATE_RUN;
}

void CheckFPS()
{
	// limita FPS a valore scelto !! come fare???
}

void RunGame()
{
	int state = 0;

	state = LoadFirstScene();

	while(state != GAME_STATE_ABORT)
	{
		state = UpdateCurrentScene();

		if(state == GAME_STATE_CHANGE_SCENE)
		{
			state = LoadNextScene(next_scene);
			continue;
		}

		CheckFPS();
	}
}
*/

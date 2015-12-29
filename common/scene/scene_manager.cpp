//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  Scene manager interface
//
//=============================================================================
#include "scene/scene_manager.h"
#include "scene/node_camera.h"
#include "scene/node_light.h"
#include "scene/node_mesh.h"
#include "debug/out.h"


namespace UAC
{
namespace Common
{


ISceneManager::ISceneManager()
	: _current(0)
	, _next(0)
	, _device(0)
	, _gfxdriver(0)
	, _node_depth(0)
{
}

ISceneManager::~ISceneManager()
{
	// delete all scenes
	RemoveAll();
}


void ISceneManager::Init(IDevice* device)
{
	_device = device;
	_gfxdriver = _device->GetGFXDriver();
}


void ISceneManager::Add(INodeScene* scene)
{
	scene->SetSceneManager(this);
	_scenes.push_back(scene);
}

void ISceneManager::Remove(INodeScene* scene)
{
	scene->SetSceneManager(0);
	for (std::vector<INodeScene*>::iterator it = _scenes.begin(); it != _scenes.end(); ++it)
	{
		if(*it == scene)
		{
			_scenes.erase(it);
			break;
		}
	}
}

void ISceneManager::RemoveAll()
{
	for(std::vector<INodeScene*>::iterator it = _scenes.begin(); it != _scenes.end(); ++it)
		delete *it;

	_scenes.clear();
}


bool ISceneManager::LoadScenesFromFile()
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("cd3d.xml");

    LOG(DEBUG)("Load result: %s", result.description());
	
	
	for(pugi::xml_node cur = doc.first_child(); cur; cur = cur.next_sibling())
	{
		if(strcmp(XMLNT_SCENE, cur.name()) != 0)
		{
			LOG(ERROR)("Not a scene node: %s", cur.name());
			continue;
		}

		if(!_read_node(cur))
			continue;
	}

	return true;
}


bool ISceneManager::_read_node(pugi::xml_node& xmlnode, INode* parent)
{
	// add node
	INode* newnode = 0;
	//
	if(strcmp(XMLNT_SCENE, xmlnode.name()) == 0 && _node_depth == 0)
	{
		newnode = CreateSceneNode(0, "");
	}
	else if(strcmp(XMLNT_CAMERA, xmlnode.name()) == 0)
	{
		newnode = CreateCameraNode(parent, "");
	}
	else if(strcmp(XMLNT_LIGHT, xmlnode.name()) == 0)
	{
		newnode = CreateLightNode(parent, LT_DIRECTIONAL, "");
	}
	else if(strcmp(XMLNT_MESH, xmlnode.name()) == 0)
	{
		newnode = CreateMeshNode(parent, "", "");
	}
	else
	{
		LOG(ERROR)("Unexpected node: %s", xmlnode.name());
		return false;
	}
	//
	if(!newnode)
	{
		LOG(ERROR)("Unexpected ERROR");
		return false;
	}
	//
	newnode->DeserializeAttributes(xmlnode);


	// look for children
	_node_depth++;
	pugi::xml_node child = xmlnode.first_child();
	while(child)
	{
		_read_node(child, newnode);
		child = child.next_sibling();
	}
	_node_depth--;

	return true;
}


/*
INodeScene* ISceneManager::Find(const char* name)
{
    unsigned int name_hash = IwHashString(name);
    for (std::list<INode*>::iterator it = _scenes.begin(); it != _scenes.end(); ++it)
    {
        if ((*it)->GetNameHash() == name_hash)
            return *it;
    }

    return 0;
}

void ISceneManager::Update(float deltaTime)
{
	for (std::vector<INode*>::iterator it = _scenes.begin(); it != _scenes.end(); ++it)
		(*it)->Update(deltaTime);
}

void ISceneManager::Render()
{
	for (std::vector<INode*>::iterator it = _scenes.begin(); it != _scenes.end(); ++it)
		(*it)->Render();

	//TEMP
	if(_gfxdriver)
		_gfxdriver->Render();
}

//TEMP - rimuovere
int cc = 0;
bool ISceneManager::Run()
{
	return ++cc < 100;
}

bool ISceneManager::isWindowActive()
{
	//TEMP
	return true;
}

void ISceneManager::OnSwitchComplete(CTween* pTween)
{
	//g_pSceneManager->FinishSwitch();
}

void ISceneManager::FinishSwitch()
{
	_next->SetInputActive(true);
	_next->SetActive(true);
	_current->Update(0);           // Update one last time to ensure that last tweened values get set because on the next frame the scene will inactive
	_current->SetActive(false);
	_current = _next;
	_next = 0;
}

void ISceneManager::SwitchTo(INodeScene* scene)
{
	_next = scene;
	if (_current == 0)
	{
		_current = _next;
		//_current ->m_X = 0;
		_current->SetActive(true);
		_current->SetInputActive(true);
		_next = 0;
	}
	else
	{
		_current->SetInputActive(false);
		_next->SetActive(true);

		_next->m_X = -(float)IwGxGetScreenWidth();
		g_pTweener->Tween(0.5f,
						FLOAT, &_next->m_X, 0.0f,
						FLOAT, &_current->m_X, (float)IwGxGetScreenWidth(),
						EASING, Ease::sineIn,
						ONCOMPLETE, OnSwitchComplete,
						END);
	}
}
*/

} // namespace Common
} // namespace UAC

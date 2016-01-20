
// A class that implements the interface ISceneController
class MyClass : ISceneController
{
	MyClass(string name)
	{
		_name = name;
		Print(_name);
		Print(" - ctor\n");
	}
	~MyClass()
	{
		Print(_name);
		Print(" - dtor\n");
	}
	
	void Enter()
	{
		Print(_name);
		Print(" - Enter\n");
	}
	
	void Leave()
	{
		Print(_name);
		Print(" - Leave\n");
	}
	
	void RepeatedlyExecute()
	{
		Print(_name);
		Print(" - do something\n");
	}
	
	string _name;
}


Scene scene1("scene1");
Camera camera(scene1, "camera");
Light sun(scene1, LT_DIRECTIONAL, "sun");
Mesh tent(scene1, "media/tentacle.ms3d", "tent");
Mesh world(scene1, "media/world.ms3d", "world");

Scene scene2("scene2");
Camera camera2(scene2, "camera2");
Light sun2(scene2, LT_DIRECTIONAL, "sun2");
Mesh tent2(scene2, "media/tentacle.ms3d", "tent2");
Mesh world2(scene2, "media/world.ms3d", "world2");

uint time;
int state = 1;

void GameStart()
{
	/* Scene1 */
/*
	MyClass ctrl("[CONTROLLER]");
	scene1.SetController(ctrl);
*/
	tent.SetPosition(47,0,2);
	tent.SetScale(0.7,0.7,0.7);
	
	
	/* Scene2 */
	camera2.SetPosition(-15,30,-130);
	sun2.SetColor(Color(255,255,0));


	time = GetSystemTime();
}

void RepeatedlyExecute()
{
	if(GetSystemTime() - time > 2500)
	{
		if(state == 1)
		{
			state = 0;
			/*
			ISceneController @m = scene1.GetController();
			m.RepeatedlyExecute();
			*/
			SetActiveScene(scene2);
		}
		else
		{
			state = 1;
			
			SetActiveScene(scene1);
		}

		time = GetSystemTime();
	}
}

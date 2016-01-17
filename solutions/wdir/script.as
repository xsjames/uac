
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
Scene scene2("scene2");

Camera camera(scene1, "camera");
Light sun(scene1, LT_DIRECTIONAL, "sun");

Mesh world(scene1, "media/world.ms3d", "world");
Mesh tent(scene2, "media/tentacle.ms3d", "tent");

uint time;
int state = 1;

void GameStart()
{
	MyClass ctrl("[CONTROLLER]");
	scene1.SetController(ctrl);

	tent.SetPosition(47,0,2);
	tent.SetScale(0.7,0.7,0.7);
	
	scene2.SetPosition(-30,10,-10);

	time = GetSystemTime();
}

void RepeatedlyExecute()
{
	if(GetSystemTime() - time > 2500)
	{
		if(state == 1)
		{
			sun.SetColor(Color(255,0,0));
			state = 0;
			
			ISceneController @m = scene1.GetController();
			m.RepeatedlyExecute();
		}
		else
		{
			sun.SetColor(Color(255,255,255));
			state = 1;
		}

		time = GetSystemTime();
	}
}

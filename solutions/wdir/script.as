
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
	
	void metodo2()
	{
	}
	
	void DoSomething()
	{
		Print(_name);
		Print(" - do something\n");
	}
	
	string _name;
}



Scene root("one");
Scene root2("two");

Camera camera(root, "camera");
Light sun(root, LT_DIRECTIONAL, "sun");

Mesh world(root, "media/world.ms3d", "world");
Mesh tent(root2, "media/tentacle.ms3d", "tent");

uint time;
int state = 1;

void GameStart()
{
	MyClass ctrl("[CONTROLLER]");
	root.SetController(ctrl);

	tent.SetPosition(47,0,2);
	tent.SetScale(0.7,0.7,0.7);
	
	root2.SetPosition(-30,10,-10);

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
			
			ISceneController @m = root.GetController();
			m.DoSomething();
		}
		else
		{
			sun.SetColor(Color(255,255,255));
			state = 1;
		}

		time = GetSystemTime();
	}
}

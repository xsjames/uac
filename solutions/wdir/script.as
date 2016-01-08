
Scene root("one");
Scene root2("two");

Camera camera(root, "camera");
Light sun(root, LT_DIRECTIONAL, "sun");

Mesh world(root, "media/world.ms3d", "world");
Mesh tent(root2, "media/tentacle.ms3d", "tent");
//Mesh door(root, "media/door.ms3d", "door");
Mesh apples(root2, "media/apples.ms3d", "apples");
Mesh berries(root, "media/berries.ms3d", "berries");

uint time;
int state = 1;

void GameStart()
{
	tent.SetPosition(47,0,2);
	tent.SetScale(0.7,0.7,0.7);
	
	root2.SetPosition(-30,10,-10);
	/*
	door.SetPosition(42,0,-4);
	door.SetRotation(0,35,0);
	door.SetScale(1.4,1.4,0.4);
	*/
	
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
		}
		else
		{
			sun.SetColor(Color(255,255,255));
			state = 1;
		}

		time = GetSystemTime();
	}
}

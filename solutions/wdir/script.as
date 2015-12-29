
//Scene scene("one");

Camera camera("camera");
Light sun(LT_DIRECTIONAL, "sun");

Mesh world("media/world.ms3d", "world");
Mesh tent("media/tentacle.ms3d", "tent");
//Mesh door("media/door.ms3d", "door");
Mesh apples("media/apples.ms3d", "apples");
Mesh berries("media/berries.ms3d", "berries");

void InitApp()
{
	tent.SetPosition(47,0,2);
	tent.SetScale(0.7,0.7,0.7);
	
	/*
	door.SetPosition(42,0,-4);
	door.SetRotation(0,35,0);
	door.SetScale(1.4,1.4,0.4);
	*/
}
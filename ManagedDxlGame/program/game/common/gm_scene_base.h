#pragma once

class SceneBase {
public :
	virtual void update(float delta_time) {};
	virtual void draw() = 0;
};


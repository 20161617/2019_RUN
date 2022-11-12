#pragma once
#include "GameObject.h"


class SDLGameObject : public GameObject {
public:
	SDLGameObject(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}
	virtual ~SDLGameObject(){}
	Vector2D getPosition() const { return m_position; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	void changeBackgroundState() { checkBackground = true; } //2번째 배경화면 출력용
	static void speedUp() { speed++; }
	static void speedReset() { speed = START_SPEED; }
protected:
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	std::string m_textureID;
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	int m_numFrames; //스프라이트의 프레임 개수
	int scrolling; //스크롤에 사용되는 변수 
	static int speed; //스크롤 스피드 (적과 배경화면 플랫폼이 왼쪽으로 이동하는 속도)
private:
	bool checkBackground; //2번째 배경화면 출력용 false일시 첫번째 true일시 두번째 배경화면 출력
};

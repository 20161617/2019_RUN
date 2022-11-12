#include "PlayState.h"
#include "GameStateMachine.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "BackGround.h"
#include "Bullet.h"
#include "MenuState.h"
#include "Player.h"
#include "Enemy.h"

PlayState* PlayState::s_pInstance = NULL;

const std::string PlayState::s_playID = "PLAY";

int PlayState::score = START_SCORE; //점수 
int PlayState::digit = START_DIGIT; //자릿수

void PlayState::update() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->changeState(PauseState::Instance());
	}
	else
	{
		if (dynamic_cast<Player*>(m_gameObjects[PLAYER_INDEX])->getPosition().getY() < 0 || //플레이어가 창의 맨위나 맨 아래에 닿았을 때
			dynamic_cast<Player*>(m_gameObjects[PLAYER_INDEX])->getPosition().getY() >
			TheGame::Instance()->getWindowSize("height") - dynamic_cast<Player*>(m_gameObjects[2])->getHeight())
		{ 
			TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance()); //게임오버
		}
		if (m_gamePlatforms.size() > 1) //플랫폼과 플레이어 충돌
		{
			for (int i = 0; i < m_gamePlatforms.size(); i++) {
				if (checkCollision(dynamic_cast<SDLGameObject*>(m_gamePlatforms[i]), 
					dynamic_cast<SDLGameObject*>(m_gameObjects[PLAYER_INDEX])))
				{
					//플랫폼과 플레이어가 충돌 할 시 체크하는 함수로 넘어감
					dynamic_cast<Player*>(m_gameObjects[PLAYER_INDEX])->setCollisionPos(dynamic_cast<SDLGameObject*>(m_gamePlatforms[i])); 
					break;
				}
				else { dynamic_cast<Player*>(m_gameObjects[PLAYER_INDEX])->setIsGroundFalse(); } //충돌하고있지 않다면 isground값 false로 변경
			}
		}
		if (m_gamePlatforms.size() > 1)
		{
			for (int i = 0; i < m_gamePlatforms.size(); i++) //모든 플랫폼 검사
			{
				if (dynamic_cast<SDLGameObject*>(m_gamePlatforms[i])->getPosition().getX() < //플랫폼의 X값이 화면의 '0'값에서 플랫폼의 길이만큼 이동했다면 
					POS_ZERO - dynamic_cast<SDLGameObject*>(m_gamePlatforms[i])->getWidth())
				{
					deletePlatform(i); //플랫폼 삭제
				}
			}
		}
		if (m_gameBullets.size() > 0) //플랫폼과 총알의 충돌 충돌시 총알 삭제
		{
			for (int i = 0; i < m_gameBullets.size(); i++)
			{
				for (int j = 0; j < m_gamePlatforms.size(); j++)
				{
					if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameBullets[i]), //모든 총알과 모든 플랫폼 검사
						dynamic_cast<SDLGameObject*>(m_gamePlatforms[j])))
					{
						deleteBullet(i); //해당 총알 삭제
						break; //for문을 빠져나감
					}
				}
			}
		}
		if (m_gameBullets.size() > 0) //총알과 적의 충돌체크
		{
			for (int i = 0; i < m_gameBullets.size(); i++)
			{
				for (int j = 0; j < m_gameEnemys.size(); j++)
				{
					if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameBullets[i]), //모든 총알과 모든 적 검사
						dynamic_cast<SDLGameObject*>(m_gameEnemys[j])))
					{
						TheSoundManager::Instance()->playChunk(SOUND_2ND_CHANNEL, "Hit", SOUND_PLAY_ONCE);
						deleteBullet(i); // 해당 총알 삭제
						deleteEnemy(j); // 해당 적을 삭제
						upScore("Enemy"); //점수 10점 추가
						break; //for문을 빠져나감
					}
				}
			}
		}
		if (m_gameEnemys.size() > 0) //적과 플레이어 충돌
		{
			for (int i = 0; i < m_gameEnemys.size(); i++)
			{
				if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[PLAYER_INDEX]), //플레이어와 모든 적 검사
					dynamic_cast<SDLGameObject*>(m_gameEnemys[i])))
				{
					TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance()); //게임오버
				}
			}
		}

		if (isLevelUp == false && score >= devideScore) //점수가 제한점수를 넘어갈 경우
		{
			devideScore += devideScore; //다음 레벨업까지 필요한 점수 2배
			enemyLimit++; //적 1마리 더 생성
			isLevelUp = true; //점수가 바뀔 때 까지 레벨 업 불가능 (업데이트가 계속 이루어 짐으로 한번만 하기 위하여)
			SDLGameObject::speedUp(); //스크롤 속도 증가
		}
		else if (score < devideScore && score != 0) //점수가 0점이 아니고 제한 점수보다 낮으면 레벨 업 가능 상태
		{
			isLevelUp = false;
		}

		if (m_gameEnemys.size() < enemyLimit) //적 최대 마리보다 적으면 생성
		{
			createEnemy();
		}

		if (m_gamePlatforms.size() != 0 && m_gamePlatforms.size() < PLATFORM_LIMIT) //최대 플랫폼 개수보다 적으면 생성
		{
			createPlatform();
		}

		for (int i = 0; i < m_gameBullets.size(); i++) {
			m_gameBullets[i]->update();
		}
		for (checkNum = 0; checkNum < m_gamePlatforms.size(); checkNum++) {
			m_gamePlatforms[checkNum]->update();
		}
		for (int i = 0; i < m_gameEnemys.size(); i++) {
			m_gameEnemys[i]->update();
		}
		GameState::update();
	}
}

void PlayState::render() {
	dynamic_cast<SDLGameObject*>(m_gameObjects[1])->changeBackgroundState(); //뒷 배경 변수값 변경
	GameState::render();
	//나머지 오브젝트와 텍스트 렌더링
	for (int i = 0; i < m_gameBullets.size(); i++) {
		m_gameBullets[i]->draw();
	}
	for (int i = 0; i < m_gamePlatforms.size(); i++) {
		m_gamePlatforms[i]->draw();
	}
	for (int i = 0; i < m_gameEnemys.size(); i++) {
		m_gameEnemys[i]->draw();
	}
	TheTextManager::Instance()->drawText("Text", (TheGame::Instance()->getWindowSize("width") / 2) - TEXT_POSX,
		POS_ZERO, TEXT_WIDTH, TEXT_HEIGHT, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);
	TheTextManager::Instance()->drawText("Score", ((TheGame::Instance()->getWindowSize("width") / 2) + SCORE_POSX),
		POS_ZERO, (SCORE_WIDTH * digit), SCORE_HEIGHT, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);
}

bool PlayState::onEnter() {
	if (!TheTextureManager::Instance()->load("assets/PlayerCharacterRun.png", "Player", //플레이어 스프라이트
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/playBackground.png", "Background", //플레이 상태 배경화면
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/bullet.png", "Bullet", //총알 스프라이트
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/platform.png", "Platform", //플랫폼 스프라이트
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/groundEnemy.png", "Enemy", //적 스프라이트
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheSoundManager::Instance()->loadSound("Assets/shoot.mp3", "Shoot", "chunk")) //총 발사 mp3
	{
		return false;
	}
	if (!TheSoundManager::Instance()->loadSound("Assets/hit.mp3", "Hit", "chunk")) //총 발사 mp3
	{
		return false;
	}
	if (!TheSoundManager::Instance()->loadSound("Assets/jump.mp3", "Jump", "chunk")) //플레이어 점프 mp3
	{
		return false;
	}
	if (!TheSoundManager::Instance()->loadSound("Assets/clickbutton.mp3", "Click", "chunk")) //플레이 버튼 누를시 나오는 효과음 mp3
	{
		return false;
	}

	GameObject* background1 = new BackGround(new LoaderParams(POS_ZERO, POS_ZERO, TheGame::Instance()->getWindowSize("width"), //배경화면 생성
		TheGame::Instance()->getWindowSize("height"), "Background"));
	GameObject* background2 = new BackGround(new LoaderParams(TheGame::Instance()->getWindowSize("width"), POS_ZERO, //배경화면 생성
		TheGame::Instance()->getWindowSize("width"), TheGame::Instance()->getWindowSize("height"), "Background"));
	GameObject* player = new Player(new LoaderParams(PLAYER_START_POSX, (TheGame::Instance()->getWindowSize("height") / 2) - PLAYER_START_POSY, //플레이어 생성
		PLAYER_WIDTH, PLAYER_HEIGHT, "Player"));
	GameObject* plat = new BackGround(new LoaderParams(POS_ZERO, (TheGame::Instance()->getWindowSize("height") / 2), //플레이어가 밟고 있을 플랫폼 생성
		PLATFORM_WIDTH, PLATFORM_HEIGHT, "Platform"));
	m_gameObjects.push_back(background1);
	m_gameObjects.push_back(background2);
	m_gameObjects.push_back(player);
	m_gamePlatforms.push_back(plat);

	reset(); //점수, 레벨조정점수, 적 제한 초기화
	TheTextManager::Instance()->loadText("Text", "Score : ", { BLACK, BLACK, BLACK }, TheGame::Instance()->getRenderer());
	TheTextManager::Instance()->loadText("Score", "0", { BLACK, BLACK, BLACK }, TheGame::Instance()->getRenderer());
	TheSoundManager::Instance()->playChunk(SOUND_4TH_CHANNEL, "Click", SOUND_PLAY_ONCE); //플레이 버튼 누를 때 사운드 재생
	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit() 
{
	TheTextureManager::Instance()->clearFromTextureMap("Background");
	TheTextureManager::Instance()->clearFromTextureMap("Player");
	TheTextureManager::Instance()->clearFromTextureMap("Bullet");
	TheTextureManager::Instance()->clearFromTextureMap("Platform");
	TheTextureManager::Instance()->clearFromTextureMap("Enemy");
	TheTextManager::Instance()->clearFromTextMap("Text");
	TheTextManager::Instance()->clearFromTextMap("Score");
	TheSoundManager::Instance()->freeChunk("Shoot");
	TheSoundManager::Instance()->freeChunk("Jump");
	TheSoundManager::Instance()->freeChunk("Click");
	TheSoundManager::Instance()->freeChunk("Hit");

	for (int i = 0; i < m_gameBullets.size(); i++) // 총알 초기화
	{
		m_gameBullets[i]->clean();
	}
	m_gameBullets.clear();

	for (int i = 0; i < m_gamePlatforms.size(); i++) //플랫폼 초기화
	{
		m_gamePlatforms[i]->clean();
	}
	m_gamePlatforms.clear();

	for (int i = 0; i < m_gameEnemys.size(); i++) //적 초기화
	{
		m_gameEnemys[i]->clean();
	}
	m_gameEnemys.clear();
	
	std::cout << "exiting PlayState\n";
	return GameState::onExit();
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	
	int leftA, leftB, rightA, rightB;
	int topA, topB, bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	if (bottomA <= topB) return false;
	if (topA >= bottomB) return false;
	if (rightA <= leftB) return false;
	if (leftA >= rightB) return false;

	return true;
}

void PlayState::createBullet(int x, int y)
{
	//플레이어의 X, Y좌표값을 가져와 조정 후 생성
	GameObject* bullet = new Bullet(new LoaderParams(x + GUN_FIRE_POS, y + GUN_FIRE_POS, BULLET_RECT, BULLET_RECT, "Bullet")); //플레이어 총구에서 나가도록 위치 조정
	m_gameBullets.push_back(bullet);
	//총 발사 사운드 플레이
	TheSoundManager::Instance()->playChunk(SOUND_1ST_CHANNEL,"Shoot", SOUND_PLAY_ONCE);
}

void PlayState::deleteBullet(int i)
{
	//창 밖으로 나가면 맨 첫번째 총알 삭제, 플랫폼에 닿았다면 그 순서의 총알 삭제
	delete m_gameBullets[i];
	m_gameBullets.erase(m_gameBullets.begin() + i);
}

void PlayState::createPlatform()
{
	//바로 앞의 플랫폼의 정보를 사용하여 플랫폼 생성 플랫폼의 Y위치와 넓이 모두 랜덤
		GameObject* platform1 = new BackGround(new LoaderParams(dynamic_cast<SDLGameObject*>(m_gamePlatforms[m_gamePlatforms.size() - 1])->getPosition().getX()
			+ dynamic_cast<SDLGameObject*>(m_gamePlatforms[m_gamePlatforms.size() - 1])->getWidth() + ((rand() % RANDOM_WIDTH) + RANDOM_WIDTH),
			(rand() % RANDOM_MIN_Y) + PLUS_1ST_Y, // Y 150 ~ 200 안에서만 생성
			(rand() % RANDOM_WIDTH) + MINIMUM_PLATFORM_WIDTH, PLATFORM_HEIGHT, "Platform"));
		m_gamePlatforms.push_back(platform1);
		GameObject* platform2 = new BackGround(new LoaderParams(dynamic_cast<SDLGameObject*>(m_gamePlatforms[m_gamePlatforms.size() - 2])->getPosition().getX()
			+ dynamic_cast<SDLGameObject*>(m_gamePlatforms[m_gamePlatforms.size() - 1])->getWidth() + ((rand() % RANDOM_MINIMUM_WIDTH) + RANDOM_MINIMUM_WIDTH),
			(rand() % RANDOM_MIN_Y) + PLUS_2ND_Y, // Y 390 ~ 440 안에서만 생성
			(rand() % RANDOM_WIDTH) + MINIMUM_PLATFORM_WIDTH, PLATFORM_HEIGHT, "Platform"));
		m_gamePlatforms.push_back(platform2);
		GameObject* platform3 = new BackGround(new LoaderParams(dynamic_cast<SDLGameObject*>(m_gamePlatforms[m_gamePlatforms.size() - 3])->getPosition().getX() 
			+ dynamic_cast<SDLGameObject*>(m_gamePlatforms[m_gamePlatforms.size() - 1])->getWidth() + ((rand() % RANDOM_WIDTH) + RANDOM_WIDTH),
			(rand() % RANDOM_MIN_Y) + PLUS_3RD_Y, // Y 630 ~ 680 안에서만 생성
			(rand() % RANDOM_WIDTH) + MINIMUM_PLATFORM_WIDTH, PLATFORM_HEIGHT, "Platform"));
		m_gamePlatforms.push_back(platform3);

}

void PlayState::deletePlatform(int i) //플랫폼 삭제
{
	//먼저 나간 플랫폼부터 삭제
	delete m_gamePlatforms[i];
	m_gamePlatforms.erase(m_gamePlatforms.begin() + i);
	checkNum--; //삭제시 자동으로 벡터가 1칸씩 당겨지므로 다시 그자리를 검사할 수 있게 값 변경
	upScore("Platform"); //점수 1점 추가
}

void PlayState::upScore(std::string reason)
{
	digit = START_DIGIT; //점수오를시 자릿값 계산을 위해 초기화
	if (reason == "Platform") //플랫폼이 하나 사라지면 1점 추가
	{
		score += PLATFORM_SCORE;
	}
	else if (reason == "Enemy") //적이 총에 맞아 죽으면 10점 추가
	{
		score += ENEMY_SCORE;
	}
	for (int i = score; i > 9; i /= DEVIDE_DIGIT) //점수의 자릿수에 따라 대상상자의 크기값이 변함
	{
		digit++;
	}
	readScore.str(""); //점수 입력값 초기화
	readScore.clear();
	readScore << score; //점수 입력
	TheTextManager::Instance()->loadText("Score", readScore.str(), { BLACK, BLACK, BLACK }, TheGame::Instance()->getRenderer()); //검정색으로 로드 
}

void PlayState::createEnemy()
{
	randomPosY = (rand() % (TheGame::Instance()->getWindowSize("height") - (ENEMY_RECT * 2))) + ENEMY_RECT; // Y 16 ~ 704 사이에서만 값이 정해짐 
	
	for (checkNum = 0; checkNum < m_gamePlatforms.size(); checkNum++) { //적이 나올 위치인 Y값이 플랫폼의 Y값과 겹쳐있는 상태라면 생성하지 않음
		if (randomPosY  >= dynamic_cast<SDLGameObject*>(m_gamePlatforms[checkNum])->getPosition().getY() - ENEMY_RECT &&
			randomPosY <= dynamic_cast<SDLGameObject*>(m_gamePlatforms[checkNum])->getPosition().getY() +
			dynamic_cast<SDLGameObject*>(m_gamePlatforms[checkNum])->getHeight())
		{
			break;
		}
	}
	if (checkNum == m_gamePlatforms.size()) //끝까지 확인했는데 겹치는 값이 없을 경우 생성
	{
		GameObject* enemy = new Enemy(new LoaderParams(TheGame::Instance()->getWindowSize("width"),
			randomPosY, ENEMY_RECT, ENEMY_RECT, "Enemy"));
		m_gameEnemys.push_back(enemy);
	}
	
}

void PlayState::deleteEnemy(int i)  //적 삭제
{
	delete m_gameEnemys[i];
	m_gameEnemys.erase(m_gameEnemys.begin() + i);
}

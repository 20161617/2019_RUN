#pragma once

enum GAME_INFO //게임관련 상수들 관련있는 것 끼리 뭉쳐놓음
{
	//윈도우 창
	WINDOW_WIDTH = 1280,
	WINDOW_HEIGHT = 720,

	FIRST = 0,

	//초기화
	STANDARD = 0, //기존 값 ex) 속도, 가속도
	RESET = 0, //값 초기화
	POS_ZERO = 0,//위치 값 X, Y
	START_DIGIT = 1, //점수 자릿수 값
	DEVIDE_DIGIT = 10, //자릿수 구할 때 사용하는 변수

	//배경화면
	BACKGROUND_FRAME = 1,

	//텍스트 관련
	BLACK = 0, //RGB값 검정색
	WHITE = 255, //RGB값 흰색
	HELP1_TEXT_WIDTH = 140, //윗 도움말 텍스트 넓이
	HELP2_TEXT_WIDTH = 200, //아랫 도움말 텍스트 넓이
	HELP_TEXT_HEIGHT = 50, //도움말 텍스트 높이
	HELP1_TEXT_POSY = -30, //윗 도움말 Y좌표값 (윈도우 중앙에서 더함)
	HELP2_TEXT_POSY = 10, //아랫 도움말 Y좌표값 (윈도우 중앙에서 더함)
	TEXT_POSX = 100, //Text 텍스쳐 X좌표값 (윈도우 중앙값에서 빼야함)
	TEXT_WIDTH = 140, //Text 텍스쳐 넓이
	TEXT_HEIGHT = 50, //Text 텍스쳐 높이
	SCORE_POSX = 40, //Score 텍스쳐 X좌표값 (윈도우 중앙값에서 더해야함)
	SCORE_WIDTH = 30, //Score 텍스쳐 넓이
	SCORE_HEIGHT = 50, //Score 텍스쳐 높이

	//점수 관련
	PLATFORM_SCORE = 1,
	ENEMY_SCORE = 10,

	//사운드
	NONSTOP = -1, //노래 무한 재생
	SOUND_PLAY_ONCE = 0, //한번만 사운드 재생

	SOUND_1ST_CHANNEL = 0, //효과음 재생 채널
	SOUND_2ND_CHANNEL = 1, //효과음 재생 채널
	SOUND_3RD_CHANNEL = 2, //효과음 재생 채널
	SOUND_4TH_CHANNEL = 3, //효과음 재생 채널

	//플레이어 점프 정보
	JUMP_LIMIT = 3, //점프 제한
	PLAYER_JUMP_POWER = -8, //플레이어 점프시 작용하는 힘

	//플레이어 프레임
	RUN_ROW = 0, //플레이어 달리는 스프라이트 
	STOP_FRAME = 1, //플레이어가 공중에 있을 시 멈추는 프레임
	ENEMY_FRAME = 2, //적 스프라이트 전체 프레임
	RUN_AND_DIE_FRAME = 8, //플레이어가 달리거나, 게임오버 됐을 때의 프레임 개수

	PLAYER_DIE_ANIMATION_SPEED = 5, // 게임오버 창에서 나오는 애니메이션 속도
	PLAYER_RUN_ANIMATION_SPEED = 10, // 일시정지 창에서 나오는 애니메이션 속도

	//버튼 정보
	BUTTON_WIDTH = 200, //버튼 넓이
	BUTTON_HEIGHT = 80, //버튼 높이
	UPSIDE_BUTTON_POSY = 80, //윗 버튼 Y좌표값 (창의 중간 값에서 더함)
	DOWNSIDE_BUTTON_POSY = 180, //아랫 버튼 Y좌표값 (창의 중간 값에서 더함)

	//시작 관련 초기 정보
	START_SCORE = 0, //시작 점수
	START_NUM = 0, //for문에 사용하는 플랫폼 관련 변수 초기화
	START_ENEMY = 2, //처음 적 최대 생성 개수
	START_SPEED = 4, //처음 스크롤 스피드
	START_DEVIDE_SCORE = 100, //처음 레벨 제한 점수

	//플레이어 텍스쳐 크기 및 위치
	DIE_PLAYER_WIDTH = 32, //게임오버 상태 플레이어 한 프레임 넓이
	DIE_PLAYER_HEIGHT = 50, //게임오버 상태 플레이어 한 프레임 높이
	DIE_PLAYER_POSY = 80, //게임오버 상태 플레이어 Y좌표값 (창의 높이 절반값에서 뺌)
	PAUSE_PLAYER_POSY = 80, //일시정지 상태 플레이어 Y좌표값 (창의 높이 절반값에서 뺌)
	PLAYER_INDEX = 2, //m_gameObject에서의 플레이어가 존재하는 인덱스 값
	PLAYER_START_POSX = 100, // 플레이어 시작 X좌표 값
	PLAYER_START_POSY = 52, // 플레이어 시작 Y좌표 값 (창의 높이 절반값에서 뺌)
	PLAYER_WIDTH = 37, //플레이 상태일 때의 플레이어 넓이 값
	PLAYER_HEIGHT = 52, //플레이 상태일 때의 플레이어 높이 값

	//플랫폼 위치 및 크기
	PLATFORM_HEIGHT = 40, //플랫폼의 높이
	PLATFORM_LIMIT = 11, //플랫폼 최대 갯수 제한
	PLATFORM_WIDTH = 300, //플랫폼의 원래 넓이
	MINIMUM_PLATFORM_WIDTH = 100, //플랫폼의 최소 넓이

	//총 발사 위치 및 총알 크기
	GUN_FIRE_POS = 30, //총알이 나가는 위치 조정 값 (플레이어 각 POS값에 더하면 됨)
	BULLET_SPEED = 12, //총알이 앞으로 나가는 속도
	BULLET_RECT = 16, //총알의 넓이와 높이

	//적 크기 관련
	ENEMY_RECT = 16, //적의 넓이와 높이

	//게임 이름 스프라이트
	GAME_NAME_WIDTH = 860, //메뉴 상태에서 나오는 게임이름 스프라이트 넓이
	GAME_NAME_HEIGHT = 162, //메뉴 상태에서 나오는 게임이름 스프라이트 높이
	GAME_NAME_POSY = 231, //메뉴 상태에서 나오는 게임이름 Y_POS값 (창의 높이 절반값에서 뺌)

	//퍼즈 상태 스프라이트
	PAUSE_WIDTH = 660, //일시정지 상태에서 나오는 일시정지 스프라이트 넓이
	PAUSE_HEIGHT = 170, //일시정지 상태에서 나오는 일시정지 스프라이트 높이
	PAUSE_POSY = 300, //일시정지 상태에서 나오는 일시정지 Y_POS값 (창의 높이 절반값에서 뺌)

	//게임오버상태 스프라이트
	GAMEOVER_WIDTH = 1070, //게임오버 상태에서 나오는 게임오버 스프라이트 넓이
	GAMEOVER_HEIGHT = 154, //게임오버 상태에서 나오는 게임오버 스프라이트 높이
	GAMEOVER_POSY = 300, //게임오버 상태에서 나오는 게임오버 Y_POS값 (창의 높이 절반값에서 뺌)

	//플랫폼 생성관련 상수
	RANDOM_MIN_Y = 50, //플랫폼 생성시 랜덤함수에 적용되는 값
	PLUS_1ST_Y = 150, // 화면 윗부분에서 나오는 플랫폼 관련 변수 (랜덤함수뒤에 더함)
	PLUS_2ND_Y = 390, // 화면 중앙부분에서 나오는 플랫폼 관련 변수 (랜덤함수뒤에 더함)
	PLUS_3RD_Y = 630, // 화면 아래부분에서 나오는 플랫폼 관련 변수 (랜덤함수뒤에 더함)

	RANDOM_MINIMUM_WIDTH = 100, //플랫폼 최소 넓이
	RANDOM_WIDTH = 200 //플랫폼 보통 넓이
};
#pragma once

class ModelClip
{
	// 모델의 프레임별 메시를 모아서 구성한 "움직임"
	// -> 움직이는 대상과도 같이 명령을 주고 받아야 하므로

private: // 필요하면 public으로 풀어도 되지만, 애니메이터 말고는 굳이 쓸 필요가 없음
	friend class ModelAnimator;

	ModelClip() = default; // 기본 생성자로만 쓰겠다
	~ModelClip();

	KeyFrame* GetKeyFrame(string boneName);

private:
	string name; // 이 움직임의 이름
	UINT frameCount; // 이 움직임을 구성할 프레임의 개수
	float tickPerSecond; // 이 움직임을 재생할 기본 속도 (1초에 몇 번 모델을 교체하는가?)
	float duration; // 지속 시간

	float playTime = 0; // 재생 시간 (0으로 초기화)

	unordered_map<string, KeyFrame*> keyFrames; // 프레임의 맵
};


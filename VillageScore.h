#pragma once
class VillageScore {
public:
	VillageScore();
	int* getScore();
	void CalculateScore(VGMaps& someMap);
private:
	int score;
};
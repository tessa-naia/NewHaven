#include "VGMaps.h"
#include "VillageScore.h"



VillageScore::VillageScore()
{
	score = 0;
}

int* VillageScore::getScore()
{
	return &score;
}

void VillageScore::CalculateScore(VGMaps& someMap)
{
	int countR1 = 0;
	int countR2 = 0;
	int countR3 = 0;
	int countR4 = 0;
	int countR5 = 0;
	int countR6 = 0;
	int countC1 = 0;
	int countC2 = 0;
	int countC3 = 0;
	int countC4 = 0;
	int countC5 = 0;

	bool allFaceUpRow1 = true;
	bool allFaceUpRow2 = true;
	bool allFaceUpRow3 = true;
	bool allFaceUpRow4 = true;
	bool allFaceUpRow5 = true;
	bool allFaceUpRow6 = true;

	bool allFaceUpColumn1 = true;
	bool allFaceUpColumn2 = true;
	bool allFaceUpColumn3 = true;
	bool allFaceUpColumn4 = true;
	bool allFaceUpColumn5 = true;

	//checking the score by row
	for (auto node : someMap.map) {
		bool faceUp = node.getFacingUp();
		int value = node.getValue();
		bool built = node.isBuilding(node);

		if (value == 1 && built) {
			int addScore = 0;
			if (faceUp)
			{
				countR1++;
				if ((countR1 == 5) && allFaceUpRow1) {
					addScore = 1 * 2;
					score += addScore;
				}
				else if ((countR1 == 5) && !allFaceUpRow1)
				{
					addScore = 1;
					score += addScore;
				}
			}
			if (!faceUp)
			{
				allFaceUpRow1 = false;
				countR1++;
				if (countR1 == 5)
				{
					addScore = 1;
					score += addScore;
				}
			}
		}


		if (value == 2 && built) {
			int addScore = 0;
			if (faceUp)
			{
				countR2++;
				if ((countR2 == 5) && allFaceUpRow2) {
					addScore = 2 * 2;
					score += addScore;
				}
				else if ((countR2 == 5) && !allFaceUpRow2)
				{
					addScore = 2;
					score += addScore;
				}
			}
			if (!faceUp)
			{
				allFaceUpRow2 = false;
				countR2++;
				if (countR2 == 5)
				{
					addScore = 2;
					score += addScore;
				}
			}
		}

		if (value == 3 && built) {
			int addScore = 0;
			if (faceUp)
			{
				countR3++;
				if ((countR3 == 5) && allFaceUpRow3) {
					addScore = 3 * 2;
					score += addScore;
				}
				else if ((countR3 == 5) && !allFaceUpRow3)
				{
					addScore = 3;
					score += addScore;
				}
			}
			if (!faceUp)
			{
				allFaceUpRow3 = false;
				countR3++;
				if (countR3 == 5)
				{
					addScore = 3;
					score += addScore;
				}
			}
		}

		if (value == 4 && built) {
			int addScore = 0;
			if (faceUp)
			{
				countR4++;
				if ((countR4 == 5) && allFaceUpRow4) {
					addScore = 4 * 2;
					score += addScore;
				}
				else if ((countR4 == 5) && !allFaceUpRow4)
				{
					addScore = 4;
					score += addScore;
				}
			}
			if (!faceUp)
			{
				allFaceUpRow4 = false;
				countR4++;
				if (countR4 == 5)
				{
					addScore = 4;
					score += addScore;
				}
			}
		}

		if (value == 5 && built) {
			int addScore = 0;
			if (faceUp)
			{
				countR5++;
				if ((countR5 == 5) && allFaceUpRow5) {
					addScore = 5 * 2;
					score += addScore;
				}
				else if ((countR5 == 5) && !allFaceUpRow5)
				{
					addScore = 5;
					score += addScore;
				}
			}
			if (!faceUp)
			{
				allFaceUpRow5 = false;
				countR5++;
				if (countR5 == 5)
				{
					addScore = 5;
					score += addScore;
				}
			}
		}

		if (value == 6 && built) {
			int addScore = 0;
			if (faceUp)
			{
				countR6++;
				if ((countR6 == 5) && allFaceUpRow6) {
					addScore = 6 * 2;
					score += addScore;
				}
				else if ((countR6 == 5) && !allFaceUpRow6)
				{
					addScore = 6;
					score += addScore;
				}
			}
			if (!faceUp)
			{
				allFaceUpRow6 = false;
				countR6++;
				if (countR6 == 5)
				{
					addScore = 6;
					score += addScore;
				}
			}
		}
	}
		////checking score by column, assuming all faceup 1st column
		for (int i = 0; i < someMap.map.size(); i += 5) {

			if (someMap.map[i].getValue() == 1 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC1++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn1 = false;
				}

			}

			if (someMap.map[i].getValue() == 2 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC1++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn1 = false;
				}
			}

			if (someMap.map[i].getValue() == 3 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC1++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn1 = false;
				}
			}

			if (someMap.map[i].getValue() == 4 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC1++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn1 = false;
				}
			}

			if (someMap.map[i].getValue() == 5 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC1++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn1 = false;
				}
			}

			if (someMap.map[i].getValue() == 6 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC1++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn1 = false;
				}
				
			}
		
			
		}
		
		if (countC1 == 6) {
			if (!allFaceUpColumn1)
			{
				int addScore = 5;
				score += addScore;
				countC1 = 0;
			}
			else
			{
				int addScore = 5 * 2;
				score += addScore;
				countC1 = 0;
			}
		}
		

		for (int i = 1; i < someMap.map.size(); i += 5) {

			if (someMap.map[i].getValue() == 1 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC2++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn2 = false;
				}

			}

			if (someMap.map[i].getValue() == 2 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC2++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn2 = false;
				}
			}

			if (someMap.map[i].getValue() == 3 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC2++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn2 = false;
				}
			}

			if (someMap.map[i].getValue() == 4 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC2++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn2 = false;
				}
			}

			if (someMap.map[i].getValue() == 5 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC2++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn2 = false;
				}
			}

			if (someMap.map[i].getValue() == 6 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC2++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn2 = false;
				}
			}

		}
		if (countC2 == 6) {
			if (!allFaceUpColumn2)
			{
				int addScore = 4;
				score += addScore;
				countC2 = 0;
			}
			else
			{
				int addScore = 4 * 2;
				score += addScore;
				countC2 = 0;
			}
		}
	
		for (int i = 2; i < someMap.map.size(); i += 5) {

			if (someMap.map[i].getValue() == 1 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC3++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn3 = false;
				}

			}

			if (someMap.map[i].getValue() == 2 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC3++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn3 = false;
				}
			}

			if (someMap.map[i].getValue() == 3 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC3++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn3 = false;
				}
			}

			if (someMap.map[i].getValue() == 4 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC3++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn3 = false;
				}
			}

			if (someMap.map[i].getValue() == 5 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC3++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn3 = false;
				}
			}

			if (someMap.map[i].getValue() == 6 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC3++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn3 = false;
				}
			}

		}
		if (countC3 == 6) {
			if (!allFaceUpColumn3)
			{
				int addScore = 3;
				score += addScore;
				countC3 = 0;
			}
			else
			{
				int addScore = 3 * 2;
				score += addScore;
				countC3 = 0;
			}
		}

		for (int i = 3; i < someMap.map.size(); i += 5) {

			if (someMap.map[i].getValue() == 1 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC4++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn4 = false;
				}

			}

			if (someMap.map[i].getValue() == 2 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC4++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn4 = false;
				}
			}

			if (someMap.map[i].getValue() == 3 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC4++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn4 = false;
				}
			}

			if (someMap.map[i].getValue() == 4 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC4++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn4 = false;
				}
			}

			if (someMap.map[i].getValue() == 5 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC4++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn4 = false;
				}
			}

			if (someMap.map[i].getValue() == 6 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC4++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn4 = false;
				}
			}

		}
		if (countC4 == 6) {
			if (!allFaceUpColumn4)
			{
				int addScore = 4;
				score += addScore;
				countC4 = 0;
			}
			else
			{
				int addScore = 4 * 2;
				score += addScore;
				countC4 = 0;
			}
		}

		for (int i = 4; i < someMap.map.size(); i += 5) {

			if (someMap.map[i].getValue() == 1 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC5++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn5 = false;
				}

			}

			if (someMap.map[i].getValue() == 2 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC5++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn5 = false;
				}
			}

			if (someMap.map[i].getValue() == 3 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC5++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn5 = false;
				}
			}

			if (someMap.map[i].getValue() == 4 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC5++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn5 = false;
				}
			}

			if (someMap.map[i].getValue() == 5 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC5++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn5 = false;
				}
			}

			if (someMap.map[i].getValue() == 6 && someMap.map[i].isBuilding(someMap.map[i])) {
				countC5++;
				if (!(someMap.map[i].getFacingUp()))
				{
					allFaceUpColumn5 = false;
				}
			}

		}
		if (countC5 == 6) {
			if (!allFaceUpColumn5)
			{
				int addScore = 5;
				score += addScore;
				countC5 = 0;
			}
			else
			{
				int addScore = 5 * 2;
				score += addScore;
				countC5 = 0;
			}
		}
		

	}


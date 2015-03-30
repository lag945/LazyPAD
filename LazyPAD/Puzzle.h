#pragma once

namespace PUZZLE
{
	class CMap
	{
	public:
		//0:¤ß 1:¤õ 2:¤ô 3:¤ì 4:¥ú 5:·t
		BYTE Element[6][5];
		CMap();
		virtual ~CMap();

		int CalCombo(int& h, int& f, int& w, int& t, int& s, int& d);
		int GetMaxCombo(int& h, int& f, int& w, int& t, int& s, int& d);
	};

	COLORREF GetColor(BYTE Element);
	int CalCombo(BYTE Element[6][5],int& h, int& f, int& w, int& t, int& s, int& d);
	int CheckCombo(BYTE Element[6][5], BYTE Mask[6][5], int a_X, int a_Y);
	void RunPath(BYTE Element[6][5], int MaxStep, int NeedCombo);
	void NextStep(BYTE Element[6][5], int CurrentX, int CurrentY, int MaxStep, int CurrentStep, int NeedCombo, CString msg);

}


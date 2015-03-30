#include "stdafx.h"
#include "Puzzle.h"

namespace PUZZLE
{
	CMap::CMap()
	{
		ZeroMemory(Element, 30);
	}


	CMap::~CMap()
	{
	}

	int CMap::GetMaxCombo(int& h, int& f, int& w, int& t, int& s, int& d)
	{
		int Ret = 0;
		h = 0, f = 0, w = 0, t = 0, s = 0, d = 0;

		BYTE sum[6];
		ZeroMemory(sum, 6);

		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 6; x++)
			{
				sum[Element[x][y]]++;
			}
		}

		h = sum[0] / 3;
		f = sum[1] / 3;
		w = sum[2] / 3;
		t = sum[3] / 3;
		s = sum[4] / 3;
		d = sum[5] / 3;

		Ret = h + f + w + t + s + d;

		return Ret;
	}

	int CMap::CalCombo(int& h, int& f, int& w, int& t, int& s, int& d)
	{
		return PUZZLE::CalCombo(Element, h, f, w, t, s, d);
	}

	COLORREF GetColor(BYTE Element)
	{
		COLORREF Ret = 0;

		switch (Element)
		{
		case 0:
			Ret = RGB(241, 129, 214);
			break;
		case 1:
			Ret = RGB(255, 0, 0);
			break;
		case 2:
			Ret = RGB(0, 0, 211);
			break;
		case 3:
			Ret = RGB(34, 235, 108);
			break;
		case 4:
			Ret = RGB(244, 227, 79);
			break;
		case 5:
			Ret = RGB(134, 49, 162);
			break;
		default:
			break;
		}

		return Ret;
	}

	int CalCombo(BYTE Element[6][5], int& h, int& f, int& w, int& t, int& s, int& d)
	{
		int Ret = 0;
		h = 0, f = 0, w = 0, t = 0, s = 0, d = 0;

		BYTE Mask[6][5];
		ZeroMemory(Mask, 30);

		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 6; x++)
			{
				int _Ret = CheckCombo(Element, Mask, x, y);
				switch (_Ret)
				{
				case 0:
					h++;
					break;
				case 1:
					f++;
					break;
				case 2:
					w++;
					break;
				case 3:
					t++;
					break;
				case 4:
					s++;
					break;
				case 5:
					d++;
					break;
				default:
					break;
				}
			}
		}

		Ret = h + f + w + t + s + d;

		return Ret;
	}

	int CheckCombo(BYTE Element[6][5], BYTE Mask[6][5], int a_X, int a_Y)
	{
		int Ret = -1;

		for (int y = 4; y >= 0; y--)
		{
			TRACE("%ld %ld %ld %ld %ld %ld\n", Mask[0][y], Mask[1][y], Mask[2][y], Mask[3][y], Mask[4][y], Mask[5][y]);
		}
		TRACE("\n");

		if (Mask[a_X][a_Y] == 1)
		{
			return Ret; 
		}

		bool iscombo = false;

		if (a_X - 1 >= 0 && a_X + 1 <= 5)
		{
			//if (Mask[a_X - 1][a_Y] == 0 && Mask[a_X + 1][a_Y] == 0)
			{
				if (Element[a_X - 1][a_Y] == Element[a_X][a_Y] && Element[a_X][a_Y] == Element[a_X + 1][a_Y])
				{
					iscombo = true;
					Mask[a_X][a_Y] = 1;
					CheckCombo(Element, Mask, a_X - 1, a_Y);
					CheckCombo(Element, Mask, a_X + 1, a_Y);
					//Mask[a_X -1][a_Y] = 1;
					//Mask[a_X +1][a_Y] = 1;
				}
			}
		}

		if (a_Y - 1 >= 0 && a_Y + 1 <= 4)
		{
			if (!iscombo)
			{
				//if (Mask[a_X][a_Y - 1] == 0 && Mask[a_X][a_Y + 1] == 0)
				{
					if (Element[a_X][a_Y - 1] == Element[a_X][a_Y] && Element[a_X][a_Y] == Element[a_X][a_Y + 1])
					{
						iscombo = true;
						Mask[a_X][a_Y] = 1;
						CheckCombo(Element, Mask, a_X, a_Y - 1);
						CheckCombo(Element, Mask, a_X, a_Y + 1);
						//Mask[a_X][a_Y - 1] = 1;
						//Mask[a_X][a_Y + 1] = 1;
					}
				}
			}
		}

		return Element[a_X][a_Y];
	}

	void RunPath(BYTE Element[6][5], int MaxStep, int NeedCombo)
	{
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 6; x++)
			{
				CString msg;
				msg.Format(L"癬﹍翴(%ld,%ld):", x, y);
				NextStep(Element, x, y, MaxStep, 0, NeedCombo, msg);
			}
		}
	}
	
	void NextStep(BYTE Element[6][5], int CurrentX, int CurrentY, int MaxStep, int CurrentStep, int NeedCombo, CString msg)
	{
		if (CurrentStep >= MaxStep) return;

		int x = CurrentX;
		int y = CurrentY;
		BYTE tmp = Element[x][y];
		int combo = 0;
		int h, f, w, t, s, d;
		CString str;
		//┕よǐ
		if (x + 1 < 6 && msg.Right(1)!=L"オ")
		{
			//称map
			BYTE _Element[6][5];
			memcpy(_Element, Element, 30);
			_Element[x][y] = _Element[x + 1][y];
			_Element[x + 1][y] = tmp;

			combo = CalCombo(_Element, h, f, w, t, s, d);
			CString _msg;
			_msg.Format(L"%s", msg);

			if (combo >= NeedCombo)
			{
				str.Format(L"%s,COMBO计 %ld: み%ld %ld %ld れ%ld %ld 穞%ld\n", _msg, combo, h, f, w, t, s, d);
				TRACE(str);
			}
			NextStep(_Element, x + 1, y, MaxStep, ++CurrentStep, NeedCombo, _msg);
		}
		if (x - 1 >= 0 && msg.Right(1) != L"")
		{
			//称map
			BYTE _Element[6][5];
			memcpy(_Element, Element, 30);
			_Element[x][y] = _Element[x - 1][y];
			_Element[x - 1][y] = tmp;

			combo = PUZZLE::CalCombo(_Element, h, f, w, t, s, d);
			CString _msg;
			_msg.Format(L"%sオ", msg);

			if (combo >= NeedCombo)
			{
				str.Format(L"%s,COMBO计 %ld: み%ld %ld %ld れ%ld %ld 穞%ld\n", _msg, combo, h, f, w, t, s, d);
				TRACE(str);
			}
			NextStep(_Element, x - 1, y, MaxStep, ++CurrentStep, NeedCombo, _msg);
		}
		if (y + 1 < 5 && msg.Right(1) != L"")
		{
			//称map
			BYTE _Element[6][5];
			memcpy(_Element, Element, 30);
			_Element[x][y] = _Element[x][y + 1];
			_Element[x][y + 1] = tmp;

			combo = PUZZLE::CalCombo(_Element, h, f, w, t, s, d);
			CString _msg;
			_msg.Format(L"%s", msg);

			if (combo >= NeedCombo)
			{
				str.Format(L"%s,COMBO计 %ld: み%ld %ld %ld れ%ld %ld 穞%ld\n", _msg, combo, h, f, w, t, s, d);
				TRACE(str);
			}
			NextStep(_Element, x, y + 1, MaxStep, ++CurrentStep, NeedCombo, _msg);
		}
		if (y - 1 >= 0 && msg.Right(1) != L"")
		{
			//称map
			BYTE _Element[6][5];
			memcpy(_Element, Element, 30);
			_Element[x][y] = _Element[x][y - 1];
			_Element[x][y - 1] = tmp;

			combo = PUZZLE::CalCombo(_Element, h, f, w, t, s, d);
			CString _msg;
			_msg.Format(L"%s", msg);

			if (combo >= NeedCombo)
			{
				str.Format(L"%s,COMBO计 %ld: み%ld %ld %ld れ%ld %ld 穞%ld\n", _msg, combo, h, f, w, t, s, d);
				TRACE(str);
			}
			NextStep(_Element, x, y - 1, MaxStep, ++CurrentStep, NeedCombo, _msg);
		}
	}
}

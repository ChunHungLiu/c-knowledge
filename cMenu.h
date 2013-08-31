#pragma once
typedef struct{
	int x, y, w, h;
}MyRect;

typedef struct{
	char* Label;
	bool Active;
}Option;

class Tab{
public:
	char* Label;
	bool Active;
	int NumberOfOptions;
	
	Option Options[10];
	
	Tab(int NumberOfOptions);

	void AddOption(int Index, char* Label, bool Active);
};

class cMenu
{
private:
	MyRect Position;
	int NumberOftabs;

public:
	Tab* Tabs;
	bool MenuActive;
	bool WhiteListActive;
	cMenu(int NumberOfTabs);
	void AddTab(int Index, char* Label, bool Active);

	MyRect GetPosition(){ return Position; }
	void SetPosition(MyRect Pos){ Position = Pos; }
	void DrawMenu();
	bool IsMouseOverTab(int Tab);
	bool IsMouseOverOption(int Tab, int Option);
	bool IsOptionActive(int tab, char* Option);
	void WhiteList(bool Enabled);
};

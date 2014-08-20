#pragma once

class CEntity
{
private:
	int pos_x;
	int pos_y;
public:
	CEntity(void);
	~CEntity(void);

	int GetX(void);
	int GetY(void);

	void SetPos(const int pos_x, const int pos_y);

	virtual void update() = 0;
	virtual void render() = 0;
};


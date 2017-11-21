#ifndef GROUND_H_IS_INCLUDED
#define GROUND_H_IS_INCLUDED

void set_texture(GLuint &texId, YsRawPngDecoder png);
inline void draw_sth(int x, int y, GLuint texId, int wid, int hei);
inline void Draw_quad(int a, int b);


class bkgd
{
public:
	void Draw_bgd(void);
};

class CharBitmap
{
protected:
	int wid, hei;
	char *dat;
public:
	CharBitmap();
	~CharBitmap();
	void CleanUp(void);

	CharBitmap(const CharBitmap &incoming);
	CharBitmap &operator=(const CharBitmap &incoming);

	int GetWidth(void) const;
	int GetHeight(void) const;
	void SetBitmap(int bmpWid, int bmpHei, char bmp[]);
	void SetPixel(int x, int y, char c) const;
	char GetPixel(int x, int y) const;

	// Draw functions
	void Draw_ground(int bias1, int bias2);
	void Draw_cloud(int bias1, int bias2);
	void Draw_grass(int bias1, int bias2);
	void Draw_mountain(int bias1, int bias2);
};

class grd
{
public:
	void Initialize(void);

};

#endif

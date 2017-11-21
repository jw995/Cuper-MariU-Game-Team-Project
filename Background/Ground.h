#ifndef GROUND_H_IS_INCLUDED
#define GROUND_H_IS_INCLUDED

inline void Draw_quad(int a, int b);

class CharBitmap
{
protected:
	int wid, hei;
	char *dat;
	int gap[7] = { 69,70,86,87,88,153,154 };
	int cloud_x[20], cloud_y[20];

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
	void Draw_bgd(void);
	void Draw_ground(int bias1, int bias2);
	void Draw_cloud(int bias1, int bias2);
	void Draw_grass(int bias1, int bias2);
	void Draw_mountain(int bias1, int bias2);
	void init(void);
	void Draw_everything(int camera_x);
};



class Texture
{
protected:;
	GLuint texId[11];
	YsRawPngDecoder png[11];
	
public:
	void set_texture(GLuint &texId, YsRawPngDecoder png);
	inline void draw_sth(int x, int y, GLuint texId, int wid, int hei);
	void init(void);
	void set(void);
	void Draw_texture(int camera_x);
	
};

#endif

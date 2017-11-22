#ifndef HELPER_FUNCTINOS_ARE_INCLUDED
#define HELPER_FUNCTINOS_ARE_INCLUDED
void DrawRect(int x1,int y1,int x2,int y2,int fill);
int CheckCollision(int tx,int ty,int tw,int th,int x,int y);
int CheckContact(int tx,int ty,int tw,int th,int x,int y);
#endif

#ifndef COINS_H_IS_INCLUDED
#define COINS_H_IS_INCLUDED

class SteadyObjects
{
    protected:
        int wid, hei;
        char * dat;
    public:
        int x, y;
        const int pixelperbit = 3;

};


class Tubes : public SteadyObjects
{
    public:
        Tubes();
        Tubes(const Tubes &incoming);
        ~Tubes();
        void CleanUp();

        Tubes &operator=(const Tubes &incoming);

        int w, h;
        int layers;
        //void SetPixel(const int x,const int y,const char c);

        //void Print(void) const;
        /*
         * Draw will call DrawUpper and DrawLower
         * DrawLower should take x0, y0 as origin of drawing
         */
        void UpdateHeight();
        void Draw(int cameraX) const;
        void DrawUpper(int cameraX) const;
        void DrawLower(int x0, int y0, int cameraX) const;
        //char GetPixel(int x,int y) const;
};



class Bricks : public SteadyObjects
{
    public:
        Bricks();
        Bricks(const Bricks &incoming);
        ~Bricks();
        void CleanUp();

        Bricks &operator=(const Bricks &incoming);

        //void SetPixel(const int x,const int y,const char c);

        int w, h;
        int shift, y_peak, y_original, reachpeak;
        //void Print(void) const;
        void Draw(int cameraX) const;
        void MarioContact(int mx, int my, int mw, int mh);
        void ShiftUp();
        //char GetPixel(int x,int y) const;
};

class Mushrooms
{
    protected:
        int wid, hei;
        char *dat;
    public:
        Mushrooms();
        Mushrooms(const Mushrooms &incoming);
        ~Mushrooms();
        void CleanUp();

        Mushrooms &operator=(const Mushrooms &incoming);

        double x, y, vx, vy;
        int w, h;
        int alive;
        void Draw(int cameraX) const;
        void Move(Tubes tube[], int nTubes, Bricks brick[], int nBricks, double dt);
        int Contact(Tubes * tube) const;
        int Contact(Bricks * brick) const;
        void MarioContact(int mx, int my, int mw, int mh);
};

class Coins : public SteadyObjects
{
    public:
        Coins();
        Coins(const Coins &incoming);
        ~Coins();
        void CleanUp();

        Coins &operator=(const Coins &incoming);

        int w, h;
        int exist;

        //int GetWidth(void) const;
        //int GetHeight(void) const;
        //void SetPixel(const int x,const int y,const char c);

        //void Print(void) const;
        void Draw(int cameraX) const;
        //char GetPixel(int x,int y) const;
        void MarioContact(int mx, int my, int mw, int mh);
};

class Objects
{
    public:
        //const int nCoins = 5;
        const int nBricks = 29;
        const int nTubes = 6;
        //Coins coin[5];
        Bricks brick[29];
        Tubes tube[6];

        Mushrooms mushroom;

        void Init(void);
        void Contact(int marioX, int marioY, int marioW, int marioH);
        void MushroomMove(int marioX, int marioY, int marioW, int marioH, double dt);
        void Draw(int cameraX);
};

#endif

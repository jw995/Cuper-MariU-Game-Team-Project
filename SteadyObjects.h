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
        ~Tubes();
        void CleanUp();


        int w, h;
        int layers;

        /*
         * Draw will call DrawUpper and DrawLower
         * DrawLower should take x0, y0 as origin of drawing
         */
        void UpdateHeight();
        void Draw(int cameraX) const;
        void DrawUpper(int cameraX) const;
        void DrawLower(int x0, int y0, int cameraX) const;
};

class Coins : public SteadyObjects
{
    public:
        Coins();
        ~Coins();
        void CleanUp();

        int w, h;
        int y_peak;
        int exist;


        void Draw(int cameraX);
        void CoinFly(int x, int y);
        void ShiftUp(void);
        //void MarioContact(int mx, int my, int mw, int mh);
};

class BrokenBricks : public SteadyObjects
{
    protected:
        int wid, hei;
        char * dat;
    public:
        int originalX;
        int x, y;
        int vx, vy;
        int diffy;
        int fly;

        BrokenBricks();
        ~BrokenBricks();
        void CleanUp();

        void Draw(int cameraX) const;
        void Move(double dt);
};

class Bricks : public SteadyObjects
{
    public:
        Bricks();
        ~Bricks();
        void CleanUp();

        int w, h;
        int shift, y_peak, y_original, reachpeak;
        int broken, flycount;
        BrokenBricks brokenbrick;
        int HaveNCoins;
        void Draw(int cameraX) const;
        int MarioContact(int mx, int my, int mw, int mh, std::string ms,
                          Coins * coin, BrokenBricks * brokenbrick);
        void ShiftUp();
        void Break(double dt);
};

class StairBricks : public SteadyObjects
{
    public:
        StairBricks();
        ~StairBricks();
        void CleanUp();

        int w, h;
        void Draw(int cameraX) const;
};

class QBricks : public Bricks
{
    public:
        QBricks();
        ~QBricks();
        void CleanUp();

        int w, h;
        int fixed, patternchanged;
        int shift, y_peak, y_original, reachpeak;
        void Draw(int cameraX) const;
        int MarioContact(int mx, int my, int mw, int mh);
        void ShiftUp(void);
        void ChangePattern(void);
};

class Mushrooms
{
    protected:
        int wid, hei;
        char *dat;
    public:
        Mushrooms();
        ~Mushrooms();
        void CleanUp();

        double x, y, vx, vy;
        int w, h;
        int alive;
        int generated;
        void Draw(int cameraX) const;
        void Move(Tubes tube[], int nTubes,
                  Bricks brick[], int nBricks,
                  QBricks qbrick[], int nQBricks,
                  double dt);
        int Contact(Tubes * tube) const;
        int Contact(Bricks * brick) const;
        void MarioContact(int mx, int my, int mw, int mh);
};


class Objects
{
    public:
        const int nCoins = 1;
        const int nBricks = 30;
        const int nStairBricks = 44;
        const int nTubes = 6;
        const int nQBricks = 12;
        Coins coin[1];
        Bricks brick[30];
        BrokenBricks brokenbrick;
        StairBricks stairbrick[44];
        Tubes tube[6];
        QBricks qbrick[12];

        Mushrooms mushroom;

        void Init(void);
        int Contact(int marioX, int marioY, int marioW, int marioH,
                    std::string marioState);
        void MushroomMove(int marioX, int marioY, int marioW, int marioH,
                          double dt);
        void Draw(int cameraX);
};

#endif

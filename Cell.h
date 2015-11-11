
#define WALL '0'
#define CORRIDOR ' '
#define FOOD '1'
#define PACMAN '2'
#define GHOSTBLUE '3'
#define GHOSTGREEN '4'
#define GHOSTRED '5'
#define GHOSTYELLOW '6'

class Cell{
    private:
        char value;
        int id;
        bool food;
    public:
        Cell();
        Cell(char value);
        void setId(int id);
        int getId();
        void setValue(char value);
        char getValue();
        bool isCorridor();
        bool isWall();
        void setCorridor();
        void setWall();
        void setFood();
        bool hasFood();
        bool isPacman();
        void setPacman();
        void eatFood();

        bool isBlueGhost();
        bool isGreenGhost();
        bool isYellowGhost();
        bool isRedGhost();

        void setBlueGhost();
        void setGreenGhost();
        void setYellowGhost();
        void setRedGhost();

        bool isGhost();
};
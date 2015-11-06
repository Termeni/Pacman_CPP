
#define WALL '0'
#define CORRIDOR ' '
#define FOOD '1'
#define PACMAN '2'
#define GHOST '3'

class Cell{
    private:
        char value;
        int id;
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
};
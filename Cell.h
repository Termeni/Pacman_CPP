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
};
#ifndef COORDS_H
#define COORDS_H

class Coords {
    protected:
        double x;
        double y;

    public:
        Coords(double xx, double yy) : x(xx), y(yy) {}
        Coords(const Coords& c)=default;
        virtual Coords operator=(const Coords& c) const { return Coords(c); };
        virtual ~Coords()=default;

        virtual bool operator==(const Coords& c) const { return ( x==c.x && y==c.y ); }
        virtual bool operator!=(const Coords& c) const { return ( x!=c.x || y!=c.y ); }
        virtual Coords operator+(const Coords& c) const { return Coords(x+c.x, y+c.y); }

        double getX() const { return x; }
        double getY() const { return y; }
        void changeX(double xx) { x=xx; }
        void changeY(double yy) { y=yy; }
        void changeXY(double xx, double yy) { changeX(xx); changeY(yy); }
        void changeXY(const Coords& c) { changeXY(c.getX(), c.getY()); }
};

#endif
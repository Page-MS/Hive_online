#ifndef COORDS_H
#define COORDS_H
#include <ostream>

class Coords {
    protected:
        double x;
        double y;

    public:
        Coords(double xx, double yy) : x(xx), y(yy) {}
        Coords(const Coords& c)=default;
        virtual Coords& operator=(const Coords& c) { x=c.getX(); y=c.getY(); return *this; };
        virtual ~Coords()=default;

        virtual bool operator==(const Coords& c) const { return ( x==c.x && y==c.y ); }
        virtual bool operator!=(const Coords& c) const { return ( x!=c.x || y!=c.y ); }
        virtual Coords operator+(const Coords& c) const { return Coords(x+c.x, y+c.y); }

        double getX() const { return x; }
        double getY() const { return y; }
        void setX(double xx) { x=xx; }
        void setY(double yy) { y=yy; }
        void addX(double xx) { x+=xx; }
        void addY(double yy) { y+=yy; }
};

std::ostream& operator<<(std::ostream& flux, const Coords& c);

#endif
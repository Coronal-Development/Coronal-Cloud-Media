#ifndef MERI_COORDINATE_H_
#define MERI_COORDINATE_H_
namespace meri
{
    class Coordinate
    {
    public:
        Coordinate(int x = 0, int y = 0) :x_(x), y_(y) {}
        int x_, y_;

    };
} // !namespace meri

#endif // !MERI_COORDINATE_H_

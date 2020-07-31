#ifndef MERI_COMMON_H_
#define MERI_COMMON_H_
namespace meri
{
    class MeriRect
    {
    public:
        MeriRect() = default;
        MeriRect(int x, int y, int width, int height, int linesize = 0, int size = 0)
            :x_(x), y_(y), width_(width), height_(height), linesize_(linesize), size_(size) {}
        int x_, y_;
        int width_, height_;
        int linesize_;
        int size_;
    };
}
#endif // !MERI_COMMON_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stack>

int W = 10;
int H = 10;

class Pixel
{
public:
  int red, green, blue;
  Pixel(int r = 0, int g = 0, int b = 0) : red(r), green(g), blue(b) { }
  void print(void)
  {
    //std::cout << '|' << red << ' ' << green << ' ' << blue << '|';
    std::cout << ' ' << red + green + blue << ' ';
  }
  bool operator== (Pixel const& p)
  {
    bool result = false;
    if (p.red == red && p.green == green && p.blue == blue)
    {
      result = true;
    }
    return result;
  }
};

class Canvas
{
private:
  std::vector < std::vector <Pixel> > pixels;
public:
  Canvas(void)
  {
    pixels.resize(W, std::vector <Pixel>(H));
  }
  void display(void) {
    for (size_t r = 0; r < pixels.size(); r++)
    {
      for (size_t c = 0; c < pixels[0].size(); c++)
      {
        pixels[r][c].print();
      }
      std::cout << '\n';
    }
    std::cout << "____________" << '\n';
  }
  void setColor(int y, int x, Pixel const& c)
  {
    pixels[y][x] = c;
  }
  void fill(int y, int x, int r, int g, int b)
  {
    Pixel need(r, g, b);
    Pixel base(pixels[y][x]);

    struct Coordinates
    {
      int y;
      int x;
      Coordinates(int yc, int xc) : y(yc), x(xc) {}
    };

    Coordinates currentPosition(y, x);

    std::stack <Coordinates> stackCoordinates;
    stackCoordinates.push(currentPosition);
    while (!stackCoordinates.empty())
    {
      currentPosition = stackCoordinates.top();
      stackCoordinates.pop();

      pixels[currentPosition.y][currentPosition.x] = need;
      display();

      Coordinates up(currentPosition.y - 1, currentPosition.x);
      Coordinates down(currentPosition.y + 1, currentPosition.x);
      Coordinates left(currentPosition.y, currentPosition.x - 1);
      Coordinates right(currentPosition.y, currentPosition.x + 1);

      if (up.y >= 0)
      {
        if (pixels[up.y][up.x] == base) { stackCoordinates.push(up); }
      }
      if (down.y < H)
      {
        if (pixels[down.y][down.x] == base) { stackCoordinates.push(down); }
      }
      if (left.x >= 0)
      {
        if (pixels[left.y][left.x] == base) { stackCoordinates.push(left); }
      }
      if (right.x < W)
      {
        if (pixels[right.y][right.x] == base) { stackCoordinates.push(right); }
      }

    }
  }
};

int main(void)
{
  Canvas canvas;
  canvas.display();

  int y; int x;
  int red; int green; int blue;
  while (1)
  {
    std::cin >> y;
    std::cin >> x;
    std::cin >> red;
    std::cin >> green;
    std::cin >> blue;
    //canvas.setColor(y, x, Pixel(red, green, blue));
    canvas.fill(y, x, red, green, blue);
    canvas.display();

  }

  return 0;
}

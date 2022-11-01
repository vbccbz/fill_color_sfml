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
};

class Canvas
{
private:
  std::vector < std::vector <Pixel> > buffer;
public:
  Canvas(void)
  {
    buffer.resize(W, std::vector <Pixel>(H));
  }
  void display(void) {
    for (size_t red = 0; red < buffer.size(); red++)
    {
      for (size_t c = 0; c < buffer[0].size(); c++)
      {
        buffer[red][c].print();
      }
      std::cout << '\n';
    }
  }
  void setColor(int x, int y, Pixel const & c)
  {
    buffer[y][x] = c;

  }
};

int main(void)
{
  Canvas canvas;
  canvas.display();

  int x; int y;
  int red; int green; int blue;
  while (1)
  {
    std::cin >> x;
    std::cin >> y;
    std::cin >> red;
    std::cin >> green;
    std::cin >> blue;
    canvas.setColor(x, y, Pixel(red,green,blue) );
    canvas.display();

  }

  return 0;
}

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
public:
  std::vector < std::vector <Pixel> > pixels;
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
    if (!(need == base))// ??????????????????????
    {
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

        //display();

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
  }
};

int main(void)
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "FILL");

  Canvas canvas;

  canvas.setColor(5, 5, Pixel(255, 255, 0));
  canvas.setColor(5 + 1, 5, Pixel(255, 0, 0));
  canvas.setColor(5 - 1, 5, Pixel(255, 0, 0));
  canvas.setColor(5, 5 + 1, Pixel(255, 0, 0));
  canvas.setColor(5, 5 - 1, Pixel(255, 0, 0));
  canvas.setColor(0, 0, Pixel(255, 0, 0));

  canvas.display();

  //int y; int x;
  //int red; int green; int blue;

  sf::RectangleShape rect;
  rect.setSize(sf::Vector2f(10.f, 10.f));
  rect.setFillColor(sf::Color::Red);

  while (window.isOpen())
    //while (1)
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Escape)
        {
          window.close();
        }
        if (event.key.code == sf::Keyboard::G)
        {
          canvas.fill(1, 1, 0, 0, 255);
          canvas.display();
        }
        if (event.key.code == sf::Keyboard::H)
        {
          canvas.fill(1, 2, 0, 255, 0);
          canvas.display();
        }
      }
    }

    //std::cin >> y;
    //std::cin >> x;
    //std::cin >> red;
    //std::cin >> green;
    //std::cin >> blue;
    //canvas.fill(y, x, red, green, blue);

    //canvas.fill(1, 1, 7, 0, 0);
    //canvas.fill(1, 2, 6, 0, 0);

    //canvas.display();

    window.clear();

    //canvas.pixels[0][0].red;
    //canvas.pixels[0][0].green;
    //canvas.pixels[0][0].blue;

    for (size_t r = 0; r < 10; r++)
    {
      for (size_t c = 0; c < 10; c++)
      {
        //rect.setFillColor(sf::Color::Red);
        rect.setFillColor(sf::Color(canvas.pixels[r][c].red, canvas.pixels[r][c].green, canvas.pixels[r][c].blue));
        rect.setPosition(r * 10, c * 10);
        window.draw(rect);
      }
    }
    //rect.setPosition(0, 0);
    //window.draw(rect);

    window.display();
  }
  return 0;
}

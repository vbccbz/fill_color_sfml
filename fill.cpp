#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stack>

int const pixelsWidth = 400;
int const pixelsHigh = 400;
int const pixelSize = 20;

class Canvas
{
public:

  class Color
  {
  private:

  public:
    int red, green, blue;
    Color(int r = 0, int g = 0, int b = 0) : red(r), green(g), blue(b) { }
    Color(Color const& cr) : red(cr.red), green(cr.green), blue(cr.blue) { }
    //void print(void)
    //{
    //  //std::cout << '|' << red << ' ' << green << ' ' << blue << '|';
    //  std::cout << red << '.' << green << '.' << blue << '|';
    //}
    bool operator== (Color const& p)
    {
      bool result = false;
      if (p.red == red && p.green == green && p.blue == blue)
      {
        result = true;
      }
      return result;
    }
  };

  struct Coordinates
  {
    int x;
    int y;
    Coordinates(int xc, int yc) : x(xc), y(yc) {}
  };

  int height;
  int width;
public:

  std::vector < std::vector <Color> > pixels;
  Canvas(int w, int h) : width(w), height(h)
  {
    pixels.resize(h, std::vector <Color>(w));
  }

  //void display(void)
  //{
  //  for (size_t r = 0; r < pixels.size(); r++)
  //  {
  //    for (size_t c = 0; c < pixels[0].size(); c++)
  //    {
  //      pixels[r][c].print();
  //    }
  //    std::cout << '\n';
  //  }
  //  std::cout << "____________" << '\n';
  //}

  void setColor(int x, int y, int r, int g, int b)
  {
    if ((x >= 0) && (y >= 0) && (x < width) && (y < height))
    {
      pixels[y][x].red = r;
      pixels[y][x].green = g;
      pixels[y][x].blue = b;
    }
  }

  Color& at(int x, int y)
  {
    return pixels[y][x];
  }

  void fill(int x, int y, int r, int g, int b)
  {
    Color requestedColor(r, g, b);
    Color previousColor(at(x, y));

    // here a condition is needed to prevent infinite adding pixels with requested color in stack  
    if (!(requestedColor == previousColor))
    {

      Coordinates currentPosition(x, y);
      std::stack <Coordinates> stackCoordinates;
      stackCoordinates.push(currentPosition);

      while (!stackCoordinates.empty())
      {

        currentPosition = stackCoordinates.top();
        stackCoordinates.pop();
        // change color of first pixel
        at(currentPosition.x, currentPosition.y) = requestedColor;

        //display();

        Coordinates up(currentPosition.x, currentPosition.y - 1);
        Coordinates down(currentPosition.x, currentPosition.y + 1);
        Coordinates left(currentPosition.x - 1, currentPosition.y);
        Coordinates right(currentPosition.x + 1, currentPosition.y);

        if (up.y >= 0)
        {
          if (at(up.x, up.y) == previousColor)
          {
            stackCoordinates.push(up);
          }
        }
        if (down.y < width )
        {
          if (at(down.x, down.y) == previousColor)
          {
            stackCoordinates.push(down);
          }
        }
        if (left.x >= 0)
        {
          if (at(left.x, left.y) == previousColor)
          {
            stackCoordinates.push(left);
          }
        }
        if (right.x < height )
        {
          if (at(right.x, right.y) == previousColor)
          {
            stackCoordinates.push(right);
          }
        }

      }// end of while
    }
  }
};

int main(void)
{
  sf::RenderWindow window(sf::VideoMode(pixelsWidth, pixelsHigh), "FILL");

  Canvas canvas(pixelsWidth / pixelSize, pixelsHigh / pixelSize);

  canvas.setColor(0, 0, 255, 0, 255);
  canvas.setColor(pixelsWidth / pixelSize - 1, 0, 255, 0, 255);
  canvas.setColor(0, pixelsHigh / pixelSize - 1, 255, 0, 255);
  canvas.setColor(pixelsWidth / pixelSize - 1, pixelsHigh / pixelSize - 1, 255, 0, 255);

  canvas.setColor(5 + 1, 5, 255, 0, 0);
  canvas.setColor(5 - 1, 5, 255, 0, 0);
  canvas.setColor(5, 5 + 1, 255, 0, 0);
  canvas.setColor(5, 5 - 1, 255, 0, 0);

  //canvas.display();

  sf::RectangleShape rect;
  rect.setSize(sf::Vector2f(pixelSize, pixelSize));
  rect.setFillColor(sf::Color::Red);
  rect.setFillColor(sf::Color(255, 0, 0));

  //canvas.fill(1, 1, 255, 255, 255);
  canvas.fill(1, 1, 0, 255, 255);

    int mx = 0;
    int my = 0;
  while (window.isOpen())
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
        if (event.key.code == sf::Keyboard::Q)
        {
          canvas.fill(1, 1, 255, 255, 255);
          //canvas.display();
        }
        if (event.key.code == sf::Keyboard::W)
        {
          canvas.fill(1, 2, 128, 0, 128);
          //canvas.display();
        }
      }
      if (event.type == sf::Event::MouseMoved)
      {
        //std::cout << event.mouseMove.x << ' ' << event.mouseMove.y << std::endl;
        mx = event.mouseMove.x;
        my = event.mouseMove.y;
        std::cout << mx << ' ' << my << std::endl;
      }

      if (event.type == sf::Event::MouseButtonPressed)
      {
        //if (event.mouseButton.button == sf::Mouse::Left)
        //{
        //  mx = event.mouseButton.x;
        //  my = event.mouseButton.y;
        //  std::cout << mx << ' ' << my << std::endl;


        //  //canvas.setColor((event.mouseButton.x) / pixelSize, (event.mouseButton.y) / pixelSize, 255, 255, 128);
        //  //std::cout << event.mouseButton.x << ' ' << event.mouseButton.y << std::endl;
        //}
        if (event.mouseButton.button == sf::Mouse::Right)
        {
          canvas.fill((event.mouseButton.x) / pixelSize, (event.mouseButton.y) / pixelSize, 128, 128, 128);
        }
      }

    }// while (window.pollEvent(event))

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      canvas.setColor( mx / pixelSize, my / pixelSize, 128, 255, 128);
      std::cout << mx << ' ' << my << std::endl;
    }

    //int y; int x;
    //int red; int green; int blue;
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

    for (size_t r = 0; r < pixelsHigh / pixelSize; r++)
    {
      for (size_t c = 0; c < pixelsWidth / pixelSize; c++)
      {
        Canvas::Color const& pr = canvas.at(r, c);
        rect.setFillColor(sf::Color(pr.red, pr.green, pr.blue));
        rect.setPosition(r * pixelSize, c * pixelSize);
        window.draw(rect);
      }
    }

    //window.draw(rect);

    window.display();

  }// while (window.isOpen())

  return 0;
}

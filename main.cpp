#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

std::vector<std::vector<int>>	createMountains(int size)
{
  std::srand(std::time(0));
  std::vector<std::vector<int>>	map;
  for (int i = 0; i < size; i++)
    {
      std::vector<int>	line;
      for (int j = 0; j < size; j++)
	{
	  line.push_back(std::rand() % 70);
	}
      map.push_back(line);
    }
  return map;
}

std::vector<std::vector<int>>	createMountains(int height, int width)
{
  std::srand(std::time(0));
  std::vector<std::vector<int>>	map;
  for (int i = 0; i < height; i++)
    {
      std::vector<int>	line;
      for (int j = 0; j < width; j++)
	{
	  line.push_back(std::rand() % 70);
	}
      map.push_back(line);
    }
  return map;
}

std::vector<std::vector<int>>	createMountains(const std::string &filename)
{
  std::ifstream	file(filename);
  std::vector<std::vector<int>>	map;
  std::string	strline;
  while (std::getline(file, strline))
    {
      std::vector<int>	line;
      std::stringstream	parser(strline);
      std::string	tmp;
      while (parser >> tmp)
	{
	  line.push_back(atoi(tmp.c_str()));
	}
      map.push_back(line);
    }
  return map;
}

sf::Vector2f	getIso(int x, int y, int nivel,
		       int xstart, int ystart, int sTile)
{
  while (nivel - 100 >= 100)
    nivel -= 100;
  while (nivel + 100 <= -100)
    nivel += 100;
  int x2 = ((x - y) * sTile) + xstart;
  int y2 = ((x + y) * (sTile / 2)) + ystart - nivel;
  sf::Vector2f	ret(x2, y2);
  return ret;
}

sf::Color	chooseFillColor(int nb)
{
  sf::Color	sea(18, 107, 150);
  sf::Color	land(51, 204, 51);

  if (nb >= 0)
    {
      while (nb >= 100)
	nb -= 100;
      if (nb <= 10)
       return (sf::Color(land.r, land.g + nb, land.b));
      else if (nb <= 90)
	return (sf::Color(land.r, land.g - nb, land.b));
      else
	return (sf::Color(255, 255, 255));
    }
  else
    {
      while (nb <= -100)
	nb += 100;
      if (nb >= -10)
       return (sf::Color(sea.r, sea.g, sea.b + nb));
      else if (nb >= -90)
	return (sf::Color(sea.r, sea.g, sea.b - nb));
      else
	return (sf::Color(10, 45, 90));
    }
}

void	drawMountains(std::vector<std::vector<int>> map,
		      sf::RenderWindow &window,
		      int height, int width)
{
  int	sTile = 40;
  int	xstart = 500;
  int	ystart = 200;

  for (int y = 0; y < height - 1; y++)
    {
      for (int x = 0; x < width - 1; x++)
	{
	  sf::ConvexShape	form;

	  form.setPointCount(4);

	  form.setPoint(0, getIso(x, y, map[y][x], xstart, ystart, sTile));
	  form.setPoint(1, getIso(x + 1, y, map[y][x + 1], xstart, ystart, sTile));
	  form.setPoint(2, getIso(x + 1, y + 1, map[y + 1][x + 1], xstart, ystart, sTile));
	  form.setPoint(3, getIso(x, y + 1, map[y + 1][x], xstart, ystart, sTile));
	  form.setFillColor(chooseFillColor(map[y][x]));
  	  // form.setOutlineColor(sf::Color(0, 0, 0));
	  // form.setOutlineThickness(-0.5);
	  window.draw(form);
	}
    }
}

void	handleEvents(sf::View &view, sf::Event event)
{
  switch (event.key.code)
  {
    case sf::Keyboard::Left:
      view.move(-100, 0);
      break;
    case sf::Keyboard::Right:
      view.move(100, 0);
      break;
    case sf::Keyboard::Up:
      view.move(0, -100);
      break;
    case sf::Keyboard::Down:
      view.move(0, 100);
      break;
    case sf::Keyboard::PageUp:
      view.zoom(0.5f);
      break;
    case sf::Keyboard::PageDown:
      view.zoom(1.5f);
      break;
  }
}

int	main(int argc, char **argv)
{
  std::vector<std::vector<int>>	map;
  if (argc == 2)
    map = createMountains(std::string(argv[1]));
  else if (argc == 3)
    map = createMountains(atoi(argv[1]), atoi(argv[2]));
  else
    {
      std::cout << "Usage : ./fdf1 [height][width]" << std::endl;
      return (0);
    }

  sf::RenderWindow	window(sf::VideoMode(1600, 900), "SFML works!");
  sf::View view(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080));
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
      {
	if (event.type == sf::Event::Closed
	    || event.key.code == sf::Keyboard::Escape)
	  window.close();
	if (event.type == sf::Event::KeyPressed)
	  handleEvents(view, event);
      }
      window.setView(view);
      window.clear();
      drawMountains(map, window, map.size(), map[0].size());
      window.display();
    }
  return 0;
}

#ifndef POINT_HPP
#define POINT_HPP

class Point {
public:
  Point(int x, int y) : m_x(x), m_y(y) {}
  int getX() const { return m_x; }
  int getY() const { return m_y; }
  void setX(int x) { m_x = x; }
  void setY(int y) { m_y = y; }
  // std::string toString();

private:
  int m_x;
  int m_y;
};
#endif
#ifndef TILE_HPP
#define TILE_HPP

class tile {
private:
  bool m_is_empty;
  int m_id;
  bool m_is_stackable;
  int m_stack_size;

public:
  tile(/* args */);
  ~tile();
};

tile::tile(/* args */) {}

tile::~tile() {
  m_is_empty = true;
  m_id = 0;
  m_is_stackable = false;
  m_stack_size = 0;
}

#endif /* TILE_HPP */
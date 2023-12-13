#ifndef CRAFT_HPP
#define CRAFT_HPP

#include "../item/block.hpp"
#include "../item/item.hpp"

#include "../utils/list.hpp"
#include <array>
#include <vector>

using namespace std;

/** @brief class who implement craft */
class Craft {
private:
  vector<LinkedList<Block> *> m_crafts; /** vector of linked List */
  bool m_isDay; /** Boolean who represent if it's day or night */

public:
  /** @brief default constructor*/
  Craft();

  /** @brief destructor */
  ~Craft();

  /** @brief update craft common to day and night
   * @param day boolean who represent if it's day or night
   */
  void update(bool day);

  /** @brief function who return who is a block have craft
   * @param id string who represent the id of the block in the blockMap
   */
  bool hasCraft(string id);

  /** @brief function who return a craft
   * @param id string who represent the id of the block in the blockMap
   */
  Block *getCraft(string id);
};

#endif /* CRAFT_HPP */
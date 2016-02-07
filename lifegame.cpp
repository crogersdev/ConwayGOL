#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const unsigned int BOARD_H     = 3;
const unsigned int BOARD_W     = 3;
const unsigned int MULTIPLIER  = 100000;
const double       PROBABILITY = .5;

/*************************************************************************/
class Cell {
public:
  Cell(const double prob = .25) : m_prob(prob), m_alive(false), m_nextState(false) {}
  ~Cell() {}

  // copy ctor?
  // copy assignment operator?

  void init()
  {
    double threshold = m_prob * MULTIPLIER;
    int p = rand() % MULTIPLIER;
    (p < threshold) ? m_alive = true : m_alive = false;
  }

  inline void draw() const { m_alive ? cout << "X" : cout << "."; }
  inline void kill() { m_nextState = false; }
  inline void quicken() { m_nextState = true; }
  inline void update() { m_alive = m_nextState; }
  inline bool alive() const { return m_alive; }

private:
  double m_prob;
  bool m_alive;
  bool m_nextState;
};

/*************************************************************************/
template<typename T>
class Board {
public:
  Board(unsigned int height, unsigned int width);
  class BadSize {};

  T& operator() (unsigned int i, unsigned int j);
  const T& operator() (unsigned int i, unsigned int j) const;
  class OutOfBounds {};

  unsigned int height() const;
  unsigned int width() const;

  void draw() const;
  bool inBounds(unsigned int, unsigned int) const;
private:
  vector< vector<T> > m_data;
};

template<typename T>
inline unsigned int Board<T>::height() const { return m_data.size(); }

template<typename T>
inline unsigned int Board<T>::width() const { return m_data[0].size(); }

template<typename T>
inline void Board<T>::draw() const
{
  for (auto hit = m_data.begin(); hit != m_data.end(); ++hit)
  {
    for (auto wit = hit->begin(); wit != hit->end(); ++wit)
      wit->draw();

    cout << endl;
  }
  cout << "\r";
}

template<typename T>
inline bool Board<T>::inBounds(unsigned int r, unsigned int c) const
{
  if (r < m_data.size() && r >= 0 &&
      c < m_data[0].size() && c >= 0)
    return true;
  else
    return false;
}

template<typename T>
inline T& Board<T>::operator()(unsigned int h, unsigned int w)
{
  if (h > height() || w > width()) throw OutOfBounds();
  return m_data[h][w];
}

template<typename T>
inline const T& Board<T>::operator()(unsigned int h, unsigned int w) const
{
  if (h > height() || w > width()) throw OutOfBounds();
  return m_data[h][w];
}

template<typename T>
Board<T>::Board(unsigned int h, unsigned int w) :
  m_data(h)
{
  if (h <= 0 || w <= 0) throw BadSize();
  for (unsigned int i = 0; i < h; ++i)
  {
    m_data[i].resize(w);
    for (auto it = m_data[i].begin(); it != m_data[i].end(); ++it)
      it->init();
  }
}

/*************************************************************************/

unsigned int getNeighbors(Board<Cell>& rBoard, unsigned int row, unsigned int col)
{
  unsigned int neighbors = 0;
  if (rBoard.inBounds(row - 1, col - 1) && rBoard(row - 1, col - 1).alive())
  {
    neighbors++;
  }
  if (rBoard.inBounds(row - 1, col)     && rBoard(row - 1, col).alive())
  {
    neighbors++;
  }
  if (rBoard.inBounds(row - 1, col + 1) && rBoard(row - 1, col + 1).alive())
  {
    neighbors++;
  }
  if (rBoard.inBounds(row, col - 1)     && rBoard(row, col - 1).alive())
  {
    neighbors++;
  }
  if (rBoard.inBounds(row, col + 1)     && rBoard(row, col + 1).alive())
  {
    neighbors++;
  }
  if (rBoard.inBounds(row + 1, col - 1) && rBoard(row + 1, col - 1).alive())
  {
    neighbors++;
  }
  if (rBoard.inBounds(row + 1, col)     && rBoard(row + 1, col).alive())
  {
    neighbors++;
  }
  if (rBoard.inBounds(row + 1, col + 1) && rBoard(row + 1, col + 1).alive())
  {
    neighbors++;
  }

  //cout << "Alive? " << rBoard(row, col).alive() << " Cell(" << row << ", " << col << ") has " << neighbors << " neighbors.\n";

  return neighbors;
}

void updateBoard(Board<Cell>& rBoard)
{
  for (unsigned int row = 0; row < rBoard.height(); ++row)
  {
    for (unsigned int col = 0; col < rBoard.width(); ++col)
    {
      unsigned int neighbors = 0;
        neighbors = getNeighbors(rBoard, row, col);

        if (neighbors < 2 && rBoard(row, col).alive())
          rBoard(row, col).kill();
        if (neighbors > 3 && rBoard(row, col).alive())
          rBoard(row, col).kill();
        if (neighbors == 3 && !rBoard(row, col).alive())
        {
          //cout << "cell(" << row << ", " << col << ") had " << neighbors << " neighbors.\n";
          rBoard(row, col).quicken();
        }

        neighbors = 0;
    }
  }

  for (unsigned int row = 0; row < rBoard.height(); ++row)
    for (unsigned int col = 0; col < rBoard.width(); ++col)
      rBoard(row, col).update();

}

int main(void)
{
  srand((unsigned int)time(NULL));
  Board<Cell> board(BOARD_H, BOARD_W);

  //board.draw();
  //updateBoard(board);
  //board.draw();

  cout << "hey there everyone" << endl << "what's up?\rhow are you?\n";
}

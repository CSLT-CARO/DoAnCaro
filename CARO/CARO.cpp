#include <iostream>
#include <string>
#include <queue>
struct Position
{
    int x, y;
};

void checkWinner(int cur_pos_x, int cur_pos_y, int type)
{
    char player;
    if(type == 0) player = 'o';
    else player = 'x';
    std::queue<Position> q; 
    q.push({cur_pos_x, cur_pos_y});
    for( int i = 1; i <= 4; i++)
    {
        if()
    }
}
int main()
{
    int n;
    std::cin >> n;
    std::cout << n << '\n';
    std::cout << "Hello World!\n";
    std::cout << "Nahh\n";
}
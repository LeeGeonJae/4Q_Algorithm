#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

using Node = tuple<int, int, int>;

enum class Direction
{
    Left,
    Right,
    Top,
    Bottom
};

bool IsMove(const Node& _node, const vector<vector<int>>& _maps, const vector<vector<bool>>& _visited)
{
    int x = get<0>(_node);
    int y = get<1>(_node);

    if (x < 0 || y < 0)
    {
        return false;
    }
    if (x >= _maps.size() || y >= _maps[x].size())
    {
        return false;
    }

    if (_maps[x][y] == 0)
    {
        return false;
    }

    if (_visited[x][y] == true)
    {
        return false;
    }

    return true;
}

int solution(vector<vector<int>> maps)
{
    int answer = -1;

    const int n = maps.size();  // 행
    const int m = maps[0].size();  // 열

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    // 튜플을 사용해 볼 것
    queue<Node> NodeQueue;

    NodeQueue.push(make_tuple(0,0,1));
    visited[0][0] = true;

    while (true)
    {
        // 더이상 큐에 아무것도 남아있지 않다면 종료
        if (NodeQueue.empty())
            break;

        Direction direction = Direction::Left;

        Node node = NodeQueue.front();
        // 도착했으면 종료
        if (n == get<0>(node) + 1 && m == get<1>(node) + 1)
        {
            answer = get<2>(node);
            break;
        }
        NodeQueue.pop();

        switch (direction)
        {
        case Direction::Left:
        {
            int x = get<0>(node) - 1;
            int y = get<1>(node);
            int distance = get<2>(node) + 1;

            Node tempNode = make_tuple(x, y, distance);
            
            if (IsMove(tempNode, maps, visited))
            {
                NodeQueue.push(tempNode);
                visited[x][y] = true;
            }
        }
        case Direction::Right:
        {
            int x = get<0>(node) + 1;
            int y = get<1>(node);
            int distance = get<2>(node) + 1;

            Node tempNode = make_tuple(x, y, distance);

            if (IsMove(tempNode, maps, visited))
            {
                NodeQueue.push(tempNode);
                visited[x][y] = true;
            }
        }
        case Direction::Top:
        {
            int x = get<0>(node);
            int y = get<1>(node) - 1;
            int distance = get<2>(node) + 1;

            Node tempNode = make_tuple(x, y, distance);

            if (IsMove(tempNode, maps, visited))
            {
                NodeQueue.push(tempNode);
                visited[x][y] = true;
            }
        }
        case Direction::Bottom:
        {
            int x = get<0>(node);
            int y = get<1>(node) + 1;
            int distance = get<2>(node) + 1;

            Node tempNode = make_tuple(x, y, distance);

            if (IsMove(tempNode, maps, visited))
            {
                NodeQueue.push(tempNode);
                visited[x][y] = true;
            }
        }
            break;
        }
    }

    for (int i = 0; i < visited.size(); i++)
    {
        for (int j = 0; j < visited[i].size(); j++)
        {
            if (visited[i][j] == true)
            {
                cout << "■";
            }
            else
            {
                cout << "□";
            }
        }
        cout << endl;
    }
    cout << "===========================" << endl;

    return answer;
}

int main()
{
    vector<vector<int>> maps = 
    { {1, 0, 1, 1, 1}
    , {1, 0, 1, 0, 1}
    , {1, 0, 1, 1, 1}
    , {1, 1, 1, 0, 1}
    , {0, 0, 0, 0, 1} };

    cout << solution(maps) << endl;

    return 0;
}
//利用BFS算法代替DFS算法完成关联图中竞争主客目标拓扑网络的寻找输出，使代码可读性更高
//20220505

struct HGlist
{
    vector<int> hosts;
    vector<int> guests;
};

vector<HGlist> getCompareGroup(const Eigen::MatrixXf& connectMatrix)
{   
    vector<HGlist> allGroups;

    int numHost = connectMatrix.rows();
    int numGuest = connectMatrix.cols();

    set<int> usedHost;
    set<int> usedGuest;
    for (int row = 0; row < numHost; ++row)
    {
        if (usedHost.find(row) != usedHost.end())
        {
            continue;
        }
        usedHost.insert(row);
        HGlist oneGroup;
        oneGroup.hosts.push_back(row);
        queue<int> que;
        que.push(row);
        while (!que.empty())
        {
            int index = que.front();
            int absIndex = abs(index);
            que.pop();
            bool isHost = absIndex == index;
            //host scan all guest
            if (isHost)
            {
                for (int col = 0; col < numGuest; ++col)
                {
                    if (connectMatrix(absIndex, col) == 1 && usedGuest.find(col) == usedGuest.end())
                    {
                        oneGroup.guests.push_back(col);
                        que.push(-col);
                        usedGuest.insert(col);
                    }
                }
            } 
            //guest scan all host
            else
            {
                for (int row = 0; row < numHost; ++row)
                {
                    if (connectMatrix(row, absIndex) == 1 && usedHost.find(row) == usedHost.end())
                    {
                        oneGroup.hosts.push_back(row);
                        que.push(row);
                        usedHost.insert(row);
                    }
                }
            }

        }
        allGroups.push_back(oneGroup);
    }
    
    return allGroups;
}

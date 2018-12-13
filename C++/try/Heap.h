

    cout << "Preparing ..." << endl;
    for (map<int, vector<int>>::iterator it = info.begin(); it != info.end(); ++it)
    {
        for (int j = 0; j < it->second.size(); ++j)
        {
            map<int, vector<int>>::iterator tmp = info.find(it->second[j]);
            bool flag = false;
            for (int k = 0; k < tmp->second.size(); ++k)
            {
                if (tmp->second[k] == it->first)
                {
                    // judgedata(it->first, tmp->first)
                    
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                it->second.erase(it->second.begin() + j);
                j--;
            }
        }
    }

    for (map<int, vector<int>>::iterator it = info.begin(); it != info.end(); ++it){
        for(int i = 0; i < it->second.size(); i++ )date_info[it->first].insert(it->second[i]);
    }

    cout << "Computing ..." << endl;
    int loop_time = 0;
    while (true)
    {
        int ans_size = -1;
        map<int, vector<int>> ans;
        for (map<int, vector<int>>::iterator it = info.begin(); it != info.end();)
        {
            if (it->second.size() == 0)
            {
                it = info.erase(it);
            }
            else
            {
                it++;
            }
        }
        while (true)
        {
            if (ans_size == ans.size())
                break;
            ans_size = ans.size();
            for (map<int, vector<int>>::iterator it = info.begin(); it != info.end(); ++it)
            {
                if (it->second.empty())
                    continue;
                if (ans.empty())
                {
                    for (int j = 0; j < it->second.size(); j++)
                    {
                        ans[it->first].push_back(it->second[j]);
                        ans[it->second[j]].push_back(it->first);
                        it->second.erase(it->second.begin());
                        auto tmp = info.find(it->second[j]);
                        for (int k = 0; k < tmp->second.size(); ++k)
                        {
                            if (tmp->second[k] == it->first)
                                tmp->second.erase(tmp->second.begin() + k);
                        }
                    }
                    continue;
                }
                if (ans.count(it->first))
                {
                    for (int j = 0; j < it->second.size(); j++)
                    {
                        bool flag = true;
                        for (auto tmp = ans.begin(); tmp != ans.end(); tmp++)
                        {
                            if (!judgedata(tmp->first, it->first))
                            {
                                flag = false;
                                break;
                            }
                        }
                        if (flag)
                        {
                            ans[it->first].push_back(it->second[j]);
                            ans[it->second[j]].push_back(it->first);
                            it->second.erase(it->second.begin());
                            auto tmp = info.find(it->second[j]);
                            for (int k = 0; k < tmp->second.size(); ++k)
                            {
                                if (tmp->second[k] == it->first)
                                    tmp->second.erase(tmp->second.begin() + k);
                            }
                        }
                    }
                }
            }
        }

        int t = 0;
        for (auto tmp = ans.begin(); tmp != ans.end(); tmp++)
        {
            t += tmp->second.size();
        }

        loop_time++;
        cout << "loop time:" << loop_time << endl;

        if (t >= 4)
        {
            cout << "size:\t" << s << endl;
            set<int> rec;
            int t = 0;
            for (auto tmp = ans.begin(); tmp != ans.end(); tmp++)
            {
                for (int i = 0; i < tmp->second.size(); i++)
                {
                    if (rec.count(tmp->second[i]) == 0)
                    {
                        rec.insert(tmp->second[i]);
                        cout << "(" << tmp->first << "," << tmp->second[i] << ")\t";
                        t++;
                        if (t % 5 == 0)
                            cout << endl;
                    }
                }
            }
            cout << endl;
        }
    }
//============================================================================
// Name        : 31485_LP1_PageReplacement.cpp
// Author      : Ashwin Taras
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define cache 3

class PageReplacement
{
	int fault;
	public : PageReplacement()
	{
		fault  = 0;
	}
	void fifo()
	{
		queue<int> pq;
		int n;
		while(true)
		{
			cout<<"Enter page to check or -1 to stop:"<<endl;
			cin >> n;
			int label = 0;
			if(n==-1)
			{
				break;
			}
			if(pq.size() < cache)
			{
				if(pq.empty())
				{
					fault++;
					pq.push(n);
				}
				else
				{
					queue<int> copy = pq;
					for(int i = 0;i<pq.size();i++)
					{
						if(copy.front()==n)
						{
							cout << "Page found!"<<endl;
							copy.pop();
							label = 1;
							break;
						}
						else
						{
							copy.pop();
						}
					}
					if(!label)
					{fault++;
					pq.push(n);}
				}
			}
			else if(pq.size()==cache)
			{
				queue<int> copy = pq;
				for(int i = 0;i<pq.size();i++)
				{
					if(copy.front()==n)
					{
						cout << "Page found!"<<endl;
						copy.pop();
						label = 1;
						break;
					}
					else
					{
						copy.pop();
					}
				}
				if(!label)
				{fault++;
				pq.pop();
				pq.push(n);
				}
			}
		}
		cout << "No of faults:"<<fault<<endl;
		fault = 0;
	}
	void optimal()
	{
		vector<int> v1;
		map<int,int> mp;
		int size = 4;
		vector<int> v2;
		int n,page;
		cout << "Enter number of pages to be checked:"<<endl;
		cin >> n;
		cout << "Enter the pages:"<<endl;
		for(int i = 0;i<n;i++)
		{
			cin >> page;
			v1.push_back(page);
			mp[page]++;
		}
		cout << "HIIII"<<endl;
		for(int i = 0;i<v1.size();i++)
		{
			cout << "Heyy1:"<<v2.size()<<endl;
			if(v2.empty())
			{
				cout << "Heyy100"<<endl;
				fault++;
				v2.push_back(v1[i]);
				continue;
			}
			else if(v2.size()<size)
			{
				cout << "Heyy2"<<endl;
				int label = 0;
				for(int j = 0;j<v2.size();j++)
				{
					if(v2[j]==v1[i])
					{
						label = 1;
						cout << "Page found!"<<endl;
						break;
					}
				}
				if(label == 0)
				{
					v2.push_back(v1[i]);
					fault++;
				}
				cout << "Heyy"<<endl;
			}
			else if(v2.size()==size)
			{
				int min = INT_MAX,minInd=-1;
				int label = 0;
				for(int j = 0; j<v2.size();j++)
				{
					if(v2[j]==v1[i])
					{
						label = 1;
						cout << "Page found!"<<endl;
						break;
					}
				}
				if(!label)
				{
					fault++;
					for (int j = 0; j < v2.size(); j++)
					{
						if (min > mp[v2[j]])
						{
							min = mp[v2[j]];
							minInd = j;
						}
					}
					v2[minInd] = v1[i];
				}
			}
		}
		cout << "No of faults:"<<fault;
	}

	void LRU()
	{
		vector<int> v1;
		v1.push_back(10);

	}

};




int main() {
	PageReplacement p1;
	p1.optimal();
	return 0;
}

//14
//7 0 1 2 0 3 0 4 2 3 0 3 2 3

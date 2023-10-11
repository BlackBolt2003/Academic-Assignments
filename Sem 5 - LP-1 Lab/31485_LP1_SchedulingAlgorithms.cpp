#include <bits/stdc++.h>
using namespace std;

class FCFS
{
    int n;
    int **arr;
    int **out;
    public:
    FCFS()
    {
        n = 5;
        arr = new int *[5];
        out = new int *[5];
        for(int i = 0;i<5;i++)
        {
        	arr[i] = new int[2];
        	out[i] = new int[3];
        }
    }
    FCFS(int n1)
    {
    	n = n1;
    	arr = new int *[n];
    	out = new int *[n];
    	for(int i = 0;i<n;i++)
		{
			arr[i] = new int[2];
			out[i] = new int[3];
		}
    }
    void input_at ()
    {
        for(int i=0; i<n; i++)
        {
            cout << "\nEnter ARRIVAL TIME of Process " << (i+1) << " - ";
            cin >> arr[i][0];
            cout << endl;
        }
        for(int i = 0;i<n;i++)
        {
        	for(int j=0;j<n-i-1;j++)
        	{
        		if(arr[j][0]>arr[j+1][0])
        		{
        			int temp = arr[j][0];
        			arr[j][0] = arr[j+1][0];
        			arr[j+1][0] = temp;
        		}
        	}
        }
        cout << "\nARRIVAL TIME Input Process Completed!" << endl;
    }

    void input_bt ()
    {
        for(int i=0; i<n; i++)
        {
            cout << "\nEnter BURST TIME of Process " << (i+1) << " - ";
            cin >> arr[i][1];
            cout << endl;
        }
        cout << "\nBURST TIME Input Process Completed!" << endl;
    }
    void calCompletion()
    {
    	int sum = 0;
    	for(int i = 0;i<n;i++)
    	{
//    		cout << "P" << i+1 << " " << arr[i][1] -
    		sum += arr[i][1];
    		out[i][0] = sum;
    	}
    }
    void calTAT()
	{
		for(int i = 0;i<n;i++)
		{
			out[i][1] = out[i][0] - arr[i][0];
		}
	}
    void calWaitTime()
	{
		for(int i = 0;i<n;i++)
		{
			out[i][2] = out[i][1] - arr[i][1];
		}
	}
    void displayOp()
    {
    	cout << "Arrival\tBurst\tCompln\tTAT\tWait Time"<<endl;
    	for(int i = 0;i<n;i++)
    	{
    		cout<<arr[i][0]<<"\t"<<arr[i][1]<<"\t"<<out[i][0]<<"\t"<<out[i][1]<<"\t"<<out[i][2]<<endl;
    	}
    	cout<<endl;
    }
};

class Process
{
	int id,at,bt,rt;
	bool comp;
	public : Process()
			{
				id = at = bt = rt = 0;
				comp = false;
			}
			Process(int i,int a,int b)
			{
				id = i;
				at = a;
				bt = b;
				rt = b;
				comp = false;
			}
			int getAt()
			{
				return at;
			}
			friend class SJF;
			friend class RoundRobin;

};
bool compareAt(Process &p1,Process &p2)
{
	return p1.getAt() < p2.getAt();
}


class SJF
{
	vector<Process> proc;
	int n;
	public : SJF()
	{
		//proc = NULL;
		n = 0;
	}
	void getData()
	{
		cout <<"Enter number of processes"<<endl;
		cin >> n;
		for(int i = 0;i<n;i++)
		{
			int id,a,b;
			cout << "Enter id,arrival time and burst time:"<<endl;
			cin >> id >> a >> b;
			Process p(id,a,b);
			proc.push_back(p);
		}
	}
	void schedule()
	{
		int currTime = 0;
		int remProcc = 0;
		sort(proc.begin(),proc.end(),compareAt);
		//cout << "Hello:"<<n;
		while(remProcc < n)
		{
			int remTime = INT_MAX;
			int shortInd = -1;
			//cout << "Hello:"<<proc[0].at;
			for(int i = 0;i<n;i++)
			{
				if(proc[i].at<=currTime && proc[i].rt>0)
				{
					if(proc[i].rt < remTime)
					{
						remTime = proc[i].rt;
						shortInd = i;
					}
				}
			}
			if(shortInd == -1)
			{
				currTime++;
				continue;
			}
			proc[shortInd].rt--;
			currTime++;
			if(proc[shortInd].rt == 0)
			{
				remProcc++;
				cout << "Process:"<<proc[shortInd].id<<" completed in:"<<currTime<<endl;
			}
		}
	}
};

class process{
    int arrivalTime,burstTime,processId,priority;
    bool completedFlag;
    public:
    process(){
        arrivalTime=burstTime=0;
        processId=-1;
        priority=10;
        completedFlag=false;
    }
    process(int at,int bt ,int id,int prior){
      arrivalTime=at;burstTime=bt;processId=id;priority=prior;
      completedFlag=false;
    }
    int getAT(){return arrivalTime;}
    int getPriority(){return priority;}
    friend class Scheduling;
};
bool compare(process &P1 ,process &P2){
    if(P1.getAT()<P2.getAT())
      return true;
    return false;
}
class Scheduling{
    vector <process> myProcess;
    public:
    Scheduling(){
      // myProcess=NULL;
    }
    Scheduling( vector<process> &p1 ){
        myProcess=p1;
    }
    void nonPreemptive(){
      int current_time=0;
      int process_completed=0;

      sort(myProcess.begin(),myProcess.end(),compare);


      while(process_completed<myProcess.size()){
        int highestPriorityIndex=-1;
        int highestPriority=INT_MAX;//highestPrio is actually numerically less
        for(int i=0;i<myProcess.size();i++){

          if(myProcess[i].arrivalTime<=current_time && myProcess[i].completedFlag==false){//i.e its in queue

              if(myProcess[i].getPriority()<highestPriority){
                  highestPriority=myProcess[i].getPriority();
                  highestPriorityIndex=i;
              }
          }
        }
        if(highestPriorityIndex==-1){
          //no process yet recieved for this current time value
          current_time++;
        }
        else{
          current_time+=myProcess[highestPriorityIndex].burstTime;
          // if(myProcess[leastTimeIndex].remainTime==0){//completed process
          cout<<"Process "<<myProcess[highestPriorityIndex].processId<<" Completed at t="<<current_time<<endl;
          myProcess[highestPriorityIndex].completedFlag=true;
          process_completed++;
          // }
        }
      }
    }

};
class RoundRobin
{
	vector<Process> proc;
	int n;
	public: RoundRobin()
	{
		//proc = NULL;
		n = 0;
	}
	void getData()
	{
		cout <<"Enter number of processes"<<endl;
		cin >> n;
		for(int i = 0;i<n;i++)
		{
			int id,a,b;
			cout << "Enter id,arrival time and burst time:"<<endl;
			cin >> id >> a >> b;
			Process p(id,a,b);
			proc.push_back(p);
		}
	}
	void Schedule()
	{
		int currTime = 0;
		int remProcc = 0;
		sort(proc.begin(),proc.end(),compareAt);
		int tq = 5;
		while(remProcc < n)
		{
			for(int i = 0;i<n;i++)
			{
				if(proc[i].rt <=tq && proc[i].comp == false)
				{
					proc[i].comp = true;
					currTime += proc[i].rt;
					proc[i].rt = 0;
					cout << "Process:"<<proc[i].id<<"completed in time:"<<currTime<<endl;
					remProcc++;
				}
				else if(proc[i].rt > tq && proc[i].comp == false)
				{
					proc[i].rt -= tq;
					currTime+=tq;
				}
			}
		}
	}
};
int main()
{
//    FCFS obj(4);
//    cout << "\n==========FCFS==========" << endl;
//
//    obj.input_at();
//    obj.input_bt();
//    obj.calCompletion();
//    obj.calTAT();
//    obj.calWaitTime();
//    obj.displayOp();

//	SJF s1;
//	s1.getData();
//	s1.schedule();

	RoundRobin r1;
	r1.getData();
	r1.Schedule();

    return 0;
}
//0
//1
//2
//3
//4
//5
//2
//6

//4
// 0 0 5
// 1 1 5
// 2 2 2
// 3 3 6

// 7
// 0 2 0 3
// 1 6 2 5
// 2 3 1 4
// 3 5 4 2
// 4 7 6 9
// 5 4 5 4
// 6 10 7 10

//6
//1 0 7
//2 1 4
//3 2 15
//4 3 11
//5 4 20
//6 4 9


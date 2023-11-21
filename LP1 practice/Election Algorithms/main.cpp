#include <iostream>
#include <vector>

#define MAX 20
using namespace std;

bool status[MAX];
int n, coordinator;

void display()
{
    int i;

    cout << "\n--------------------------------------------------------\n";
    // processes
    cout << "Process: ";
    for (int i = 1; i <= n; i++)
    {
        cout << i << "\t";
    }
    cout << "\nStatus:  ";
    for (int i = 1; i <= n; i++)
    {
        cout << status[i] << "\t";
    }

    cout << "\n--------------------------------------------------------\n";
    cout << "Coordinator: " << coordinator << endl;
}

void bully()
{
    int choice2, crash, activate, i, gid, flag, subcoordinator;
    // crash = id of process to be crashed
    // activate = id of process to be activated
    // gid = id of process that initiates election (generator id)
    // flag = false if initiator is to be elected as coordinator (gid is highest active node)
    // subcoordinator = highest id till current iteration

    do
    {
        cout << "\n--------------------------------------------------------\n";
        cout << "1. Crash \n2. Activate \n3. Display \n4. Exit";
        cout << "\n--------------------------------------------------------\n";

        cout << "Enter your choice: ";
        cin >> choice2;

        switch (choice2)
        {
        case 1: // crash
            // manually crash a process
            cout << "Enter process id to crash: ";
            cin >> crash;

            // set status to dead if prcoess was alive
            if (status[crash])
            {
                status[crash] = false;
            }
            else
            {
                cout << "Process " << crash << " is already dead!\n";
                break;
            }

            // select generator/ initiator node
            do
            {
                // enter generator id
                cout << "Enter election generator id: ";
                cin >> gid;
                if (gid == coordinator || status[gid] == false)
                {
                    cout << "Please enter a valid generator id\n";
                }

            } while (gid == coordinator || status[gid] == false);

            flag = 0;

            // find new coordinator if current coordinator has crashed
            if (crash == coordinator)
            {
                // election initiator process (gid) sends msg to all higher processes
                for (i = gid + 1; i <= n; i++)
                {
                    cout << "\nElection msg sent from Process " << gid << " to Process " << i << endl;
                    // if the higher process is alive, it will respond
                    if (status[i])
                    {
                        subcoordinator = i;
                        cout << "Response msg recieved by Process " << gid << " from Process " << i << endl;
                        flag = 1;
                    }
                }

                // elect highest responding process as coordinator
                if (flag == 1)
                {
                    coordinator = subcoordinator;
                }

                // elect generator process as coordinator if no higher process is alive
                else
                {
                    coordinator = gid;
                }
            }
            display();
            break;

        case 2: // activate
            // manually activate a process
            cout << "Enter a process id to activate: ";
            cin >> activate;

            // check if it is already active, otherwise make it
            if (!status[activate])
            {
                status[activate] = true;
            }

            else
            {
                cout << "Process " << activate << " is already active!" << endl;
                break;
            }

            flag = 0;
            // else, activated process send msg to all higher processes
            for (i = activate + 1; i <= n; i++)
            {
                cout << "\nElection msg sent from Process " << activate << " to Process " << i << endl;

                // if higher process is alive then it responds
                if (status[i])
                {
                    subcoordinator = i;
                    cout << "Response msg recieved by Process " << activate << " from Process " << i << endl;
                    flag = 1;
                }
            }

            // elect highest responding process as coordinator
            if (flag == 1)
            {
                coordinator = subcoordinator;
            }

            // otherwise, generator process is the coordinator
            else
            {
                coordinator = activate;
            }

            display();
            break;

        case 3: // Display
            display();
            break;

        case 4: // Exit
            break;

        default: // Forced exit
            choice2 = 4;
            break;
        }

    } while (choice2 != 4);
}

void ring()
{
    int choice2, crash, activate, i, gid, subcoordinator;
    vector<int> activeList;
    // crash = id of process to be crashed
    // activate = id of process to be activated
    // gid = id of process that initiates election (generator id)
    // subcoordinator = highest id till current iteration

    do
    {
        cout << "\n--------------------------------------------------------\n";
        cout << "1. Crash \n2. Activate \n3. Display \n4. Exit";
        cout << "\n--------------------------------------------------------\n";

        cout << "Enter your choice: ";
        cin >> choice2;

        switch (choice2)
        {
        case 1: // crash
            // manually crash a process
            cout << "Enter process id to crash: ";
            cin >> crash;

            // set status to dead if prcoess was alive
            if (status[crash])
            {
                status[crash] = false;
            }
            else
            {
                cout << "Process " << crash << " is already dead!\n";
                break;
            }

            // select generator/ initiator node
            do
            {
                // enter generator id
                cout << "Enter election generator id: ";
                cin >> gid;
                if (gid == coordinator || status[gid] == false)
                {
                    cout << "Please enter a valid generator id\n";
                }

            } while (gid == coordinator || status[gid] == false);

            // find new coordinator if current coordinator has crashed
            if (crash == coordinator)
            {
                subcoordinator = 1;
                for (i = 0; i < (n + 1); i++)
                {
                    int pid = (i + gid) % (n + 1);
                    if (pid != 0) // since process id starts from 1 (to n)
                    {
                        if (status[pid] && subcoordinator < pid)
                        {
                            subcoordinator = pid;
                        }
                        if (status[pid])
                        {
                            cout << "Election message sent from " << pid << ": #Msg " << subcoordinator << endl;
                        }
                    }
                }

                coordinator = subcoordinator;
            }
            display();
            break;

        case 2: // activate
            // manually activate a process
            cout << "Enter a process id to activate: ";
            cin >> activate;

            // check if it is already active, otherwise make it
            if (!status[activate])
            {
                status[activate] = true;
            }

            else
            {
                cout << "Process " << activate << " is already active!" << endl;
                break;
            }

            // elect the coordinator
            subcoordinator = activate;
            for (i = 0; i < n + 1; i++)
            {
                int pid = (i + activate) % (n + 1);

                if (pid != 0)
                {
                    if (status[pid] && subcoordinator < pid)
                    {
                        subcoordinator = pid;
                    }
                    if (status[pid])
                    {
                        cout << "Election message sent from " << pid << ": #Msg " << subcoordinator << endl;
                    }
                }
            }

            coordinator = subcoordinator;

            display();
            break;

        case 3: // Display
            display();
            break;

        case 4: // Exit
            break;

        default: // Forced exit
            choice2 = 4;
            break;
        }

    } while (choice2 != 4);
}

int main()
{

    int choice1;

    cout << "Enter no. of processes: ";
    cin >> n;

    // Get status of each process and select initial coordinator
    for (int i = 1; i <= n; i++)
    {
        cout << "Enter process " << i << " is alive(1) or not(0): ";
        cin >> status[i];

        if (status[i])
        {
            coordinator = i;
        }
    }

    display();

    do
    {
        cout << "\n--------------------------------------------------------\n";
        cout << "1. Bully \n2. Ring \n3. Display \n4. Exit";
        cout << "\n--------------------------------------------------------\n";

        cout << "Enter your choice: ";
        cin >> choice1;

        switch (choice1)
        {
        case 1: // Bully
            bully();
            break;

        case 2: // Ring
            ring();
            break;

        case 3: // Display
            display();
            break;

        case 4: // Exit
            exit(1);
            break;

        default: // Forced exit
            exit(1);
            break;
        }

    } while (choice1 != 4);

    return 0;
}
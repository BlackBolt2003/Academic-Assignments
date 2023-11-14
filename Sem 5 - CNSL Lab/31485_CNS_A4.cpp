#include<bits/stdc++.h>
#include<iostream>
#include<ctime>

#define ll long long int
using namespace std;

void transmission(ll & i, ll & N, ll & total_frames, ll & total_time) {
  while (i <= total_frames) {
    int z = 0;
    for (int k = i; k < i + N && k <= total_frames; k++) {
       _sleep(2);
      cout << "Sending Frame " << k << "..." << endl;
      total_time++;
    }
    for (int k = i; k < i + N && k <= total_frames; k++) {
      int f = rand() % 2;
      if (!f) {
        cout << "Acknowledgment for Frame " << k << "..." << endl;
        _sleep(2);
        z++;
      } else {
        cout << "Timeout!! Frame Number : " << k << " Not Received" << endl;
        _sleep(2);
        cout << "Retransmitting Window..." << endl;
        break;
      }
    }
    cout << "\n";
    i = i + z;
  }
}

int main() {
  ll total_frames, N, total_time = 0;
  srand(time(NULL));
  cout << "Enter the Total number of frames : ";
  cin >> total_frames;
  cout << "Enter the Window Size : ";
  cin >> N;
  ll i = 1;
  transmission(i, N, total_frames, total_time);
  cout << "Total number of frames which were sent and resent are : " << total_time <<
    endl;
  return 0;
}
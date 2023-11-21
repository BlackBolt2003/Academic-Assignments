#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void displayCache(char *cache, int cacheSize, bool hit)
{
    for (int i = 0; i < cacheSize; i++)
    {
        cout << cache[i] << " ";
    }
    string msg = (hit) ? ("Hit") : ("*");
    cout << " : " << msg << endl;
}

void FCFS(string refString, int n)
{
    // n = buffer size
    int hit = 0, miss = 0;
    char *frames = new char[n];
    for (int i = 0; i < n; i++)
    {
        frames[i] = 'x';
    }

    int frameNo = 0;

    cout << "\nFCFS:\n";

    for (int ptr = 0; ptr < refString.size(); ptr++)
    {
        char page = refString[ptr];
        bool isPresent = false;

        // check for page in cache
        for (int f = 0; f < n; f++)
        {
            if (frames[f] == page)
            {
                hit++;
                isPresent = true;
                break;
            }
        }

        // not present in cache
        if (!isPresent)
        {
            // replace in FIFO manner
            frames[frameNo] = page;
            frameNo++;
            frameNo = frameNo % n;
            miss++;
        }

        displayCache(frames, n, isPresent);
    }

    cout << "\nHits: " << hit << endl;
    cout << "Page Faults: " << miss << endl;
    cout << "Hit Ratio: " << hit * 1.0 / refString.size() << endl;
    cout << "Fault Ratio: " << miss * 1.0 / refString.size() << endl;
}

void LRU(string refString, int n)
{
    // n = buffer size
    cout << "\nLRU:\n";

    int hit = 0, miss = 0;
    char *frames = new char[n];
    for (int i = 0; i < n; i++)
    {
        frames[i] = 'x';
    }

    int frameIndex = 0;
    unordered_map<int, int> LRIndexes;

    for(int i=0; i<refString.size(); i++){
        char page = refString[i];
        bool isPresent = false;

        // check if already present
        for(int f=0; f<n; f++){
            if(frames[f] == page){
                hit++;
                isPresent = true;
                break;
            }
        }

        // empty frame in cache
        if(i < n && !isPresent){
            miss++;
            frames[frameIndex] = page;
            frameIndex++;
            frameIndex = frameIndex % n;
        }

        // replacement
        else if(!isPresent){
            miss++;
            int leastRecentIndex = 999;
            int cacheEntry = 0;

            for(int f=0; f<n; f++){
                if(LRIndexes[frames[f]] < leastRecentIndex){
                    leastRecentIndex = LRIndexes[frames[f]];
                    cacheEntry = f;
                }
            }
            frames[cacheEntry] = page;
        }

        LRIndexes[page] = i;
        displayCache(frames, n, isPresent);
    }


    cout << "\nHits: " << hit << endl;
    cout << "Page Faults: " << miss << endl;
    cout << "Hit Ratio: " << hit * 1.0 / refString.size() << endl;
    cout << "Fault Ratio: " << miss * 1.0 / refString.size() << endl;
}

int predictFarthest(string refString, int refPtr, char *frames, int frameSize)
{
    int farthestFrame = -1;
    int farthestDistance = refPtr;

    for (int f = 0; f < frameSize; f++)
    {
        int j;

        // search for first occurrance of a frame
        for (j = refPtr; j < refString.size(); j++)
        {
            if (refString[j] == frames[f])
            {
                // compare with currently assumed farthest frame
                if (j > farthestDistance)
                {
                    farthestDistance = j;
                    farthestFrame = f;
                }
                break;
            }
        }

        // frame not found in future
        if (j == refString.size())
        {
            return f;
        }
    }

    return (farthestFrame == -1) ? (0) : (farthestFrame);
}

void Optimal(string refString, int n)
{
    // n = buffer size
    cout << "\nOptimal:\n";

    int hit = 0, miss = 0;
    char *frames = new char[n];
    for (int i = 0; i < n; i++)
    {
        frames[i] = 'x';
    }

    int FrameIndex = 0;

    for (int i = 0; i < refString.size(); i++)
    {
        char page = refString[i];
        bool isPresent = false;

        // check if already present in cache
        for (int f = 0; f < n; f++)
        {
            if (frames[f] == page)
            {
                hit++;
                isPresent = true;
                break;
            }
        }

        // empty frame in cache
        if (i < n && !isPresent)
        {
            frames[FrameIndex] = page;
            miss++;
            FrameIndex++;
            FrameIndex = FrameIndex % n;
        }

        // page not present in cache
        else if (!isPresent)
        {
            int toReplace = predictFarthest(refString, i + 1, frames, n);
            frames[toReplace] = page;
            miss++;
        }

        displayCache(frames, n, isPresent);
    }

    cout << "\nHits: " << hit << endl;
    cout << "Page Faults: " << miss << endl;
    cout << "Hit Ratio: " << hit * 1.0 / refString.size() << endl;
    cout << "Fault Ratio: " << miss * 1.0 / refString.size() << endl;
}

int main()
{
    string refString;
    cout << "Enter input stream: ";
    cin >> refString;

    int size;
    cout << "Enter cache size: ";
    cin >> size;

    // 701203042303120
    FCFS(refString, size);

    // 70120304230321201701
    LRU(refString, size);

    // 70120304230321201701
    Optimal(refString, size);

    return 0;
}
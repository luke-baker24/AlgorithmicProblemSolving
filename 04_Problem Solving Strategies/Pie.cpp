#include <iostream>
#include <vector>

using namespace std;

int main() {
    int testCases;
    cin >> testCases;

    //Solution is going to be to iterate through all of the pies. For each pie, try to cut a certain slice size out.
    //If we can't, go to the next pie. If we can, remove it, and keep trying to cut slices.
    //If the number of slices we can cut is greater than the number of people eating, then increase the volume.
    //If it's less than the number of people eating, then decrease the volume.
    //If it is equal, there is probably still more optimization to be done, and we keep trying to approach the value
    //where there isn't enough pie left until we settle on a value with 10^(-3) accuracy.

    for (int i = 0; i < testCases; i++) {
        int pies, friends;
        cin >> pies >> friends;
        friends++;

        float totalVolume = 0.0f;
        std::vector<float> pieVolumes;

        for (int j = 0; j < pies; j++) {
            int radius;
            std::cin >> radius;

            float thisPieVolume = radius * radius * 3.1415926f;

            totalVolume += thisPieVolume;
            pieVolumes.push_back(thisPieVolume);
        }
        
        float min = 0.0f;
        float max = totalVolume / (float)friends;
        float guess = (max + min) / 2.0f;

        while (true) {
            int friendsServed = 0;
            for (int j = 0; j < pies; j++)
                friendsServed += (int)(pieVolumes.at(j) / guess);
            
            if (max - min < 0.0001) 
                break;
            
            if (friendsServed < friends)
                max = guess;
            else
                min = guess;
            
            guess = (max + min) / 2.0f;
        }
        
        cout << guess << endl;
    }
}

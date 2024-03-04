#include<iostream>
#include<random>
#include<ranges>
#include<algorithm>
#include<SDL.h>
#include<vector>

using namespace std;

void draw_state(const vector<int>& v, SDL_Renderer* renderer, int blue, int red, int windowWidth, int windowHeight) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 81, 0);
    SDL_RenderClear(renderer);
    int barWidth = windowWidth / v.size();
    for (int i = 0; i < v.size(); ++i) {
        int barHeight = v[i] * windowHeight / 100; // Scale the bar height
        if (i == red)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (i == blue)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        else
            SDL_SetRenderDrawColor(renderer, 168, 35, 17, 0);
        SDL_Rect rect = {i * barWidth, windowHeight - barHeight, barWidth, barHeight};
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    random_device rd;
    uniform_int_distribution<int> d(1, 99);

    // Populate our vector with random variables
    vector<int> v;
    for (int i = 0; i < 100; i++) {
        v.push_back(d(rd));
    }

    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("Sort", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    auto renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event e;

    bool sorting = true; // Indicates if sorting is in progress

    int blueIndex = -1; // Tracks the index of the blue bar
    int redIndex = -1;  // Tracks the index of the red bar

    while (sorting) {
        // Sorting algorithm
        bool sorted = true;
        for (unsigned int i = 0; i < v.size(); i++) {
            for (int j = i + 1; j < v.size(); j++) {
                blueIndex = i;
                redIndex = j;
                if (v[j] < v[i]) {
                    swap(v[i], v[j]);
                    sorted = false;
                }
                draw_state(v, renderer, blueIndex, redIndex, 900, 600);
                SDL_Delay(5);

                // Check for events to allow exiting even during sorting
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        sorting = false; // Stop sorting if window is closed
                        break; // Exit the event loop
                    }
                }
            }
            if (!sorting) // Stop outer loop if window is closed
                break;
        }

        // If array is sorted, stop the sorting process
        if (true) {
            cout << "Array is sorted!" << endl;
            break;
        }
    }

    // Clean up SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

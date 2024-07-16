#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "SDL2.lib") // Подключение библиотеки SDL
#include <SDL.h> // Включение заголовочного файла SDL
#undef main

#define BOARD_SIZE 8

int queens[BOARD_SIZE];
int cellWidth = 800 / BOARD_SIZE;
int cellHeight = 800 / BOARD_SIZE;

struct ChessBoard {
    int** solutions;
    int currentSolutionIndex;
    int numSolutions;

    ChessBoard() : currentSolutionIndex(0), numSolutions(0) {
        solutions = NULL;
    }

    void addSolution(int* solution) {
        solutions = (int**)realloc(solutions, (numSolutions + 1) * sizeof(int*));
        solutions[numSolutions] = (int*)malloc(BOARD_SIZE * sizeof(int));
        for (int i = 0; i < BOARD_SIZE; i++) {
            solutions[numSolutions][i] = solution[i];
        }
        numSolutions++;
    }

    int* getCurrentSolution() const {
        return solutions[currentSolutionIndex];
    }

    int hasNextSolution() const {
        return currentSolutionIndex < numSolutions - 1;
    }

    int hasPreviousSolution() const {
        return currentSolutionIndex > 0;
    }

    void nextSolution() {
        if (hasNextSolution()) {
            currentSolutionIndex++;
        }
    }

    void previousSolution() {
        if (hasPreviousSolution()) {
            currentSolutionIndex--;
        }
    }
};

int isSafe(int row, int col) {
    for (int r = 0; r < row; ++r) {
        if (queens[r] == col || queens[r] - r == col - row || queens[r] + r == col + row) {
            return 0;
        }
    }
    return 1;
}

void printResult(SDL_Renderer* renderer, const ChessBoard* chessBoard) {
    if (chessBoard->solutions == NULL || chessBoard->currentSolutionIndex >= chessBoard->numSolutions) {
        return;
    }

    const int* currentSolution = chessBoard->getCurrentSolution();

    SDL_Surface* queenSurface = SDL_LoadBMP("C:/Users/Alexandr/Desktop/test/Red-Circle.bmp");
    SDL_Texture* queenTexture = SDL_CreateTextureFromSurface(renderer, queenSurface);
    SDL_FreeSurface(queenSurface);

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            SDL_Rect rect = { row * cellWidth, col * cellHeight, cellWidth, cellHeight };
            if ((row + col) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderFillRect(renderer, &rect);

            if (currentSolution[row] == col) {
                printf("Queen %d is at (%d, %d)\n", row + 1, row + 1, col + 1);
                SDL_Rect queenRect = { row * cellWidth, col * cellHeight, cellWidth, cellHeight };
                SDL_RenderCopy(renderer, queenTexture, NULL, &queenRect);
            }
        }
    }
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(queenTexture);
}

void solveQueens(ChessBoard* chessBoard, int row) {
    if (row == BOARD_SIZE) {
        chessBoard->addSolution(queens);
        return;
    }
    for (int col = 0; col < BOARD_SIZE; ++col) {
        if (isSafe(row, col)) {
            queens[row] = col;
            solveQueens(chessBoard, row + 1);
        }
    }
}

int main() {
    int i;
    for (i = 0; i < BOARD_SIZE; i++) {
        queens[i] = 0;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Chess Board", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    ChessBoard chessBoard;

    int quit = 0;
    int newvar = 0;
    int first = 1;
    int spacePressed = 0;

    while (!quit) {
        if (newvar) {
            printResult(renderer, &chessBoard);
            newvar = 0;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    if (!first) {
                        printf("\n");
                    }
                    for (i = 0; i < BOARD_SIZE; i++) {
                        queens[i] = 0;
                    }
                    chessBoard = ChessBoard();
                    solveQueens(&chessBoard, 0);
                    newvar = 1;
                    first = 0;
                    spacePressed = 1;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT && spacePressed) {
                    if (chessBoard.hasNextSolution()) {
                        printf("\n");
                        chessBoard.nextSolution();
                        newvar = 1;
                    }
                }
                else if (event.key.keysym.sym == SDLK_LEFT && spacePressed) {
                    if (chessBoard.hasPreviousSolution()) {
                        printf("\n");
                        chessBoard.previousSolution();
                        newvar = 1;
                    }
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

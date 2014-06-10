#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <map>
#include <stack>
#include <cmath>

using namespace std;

vector<int> deck;

void init() {
    for (int i = 1; i <= 13; ++i) {
        for (int j = 0; j < 4; ++j) {
            deck.push_back(i);
        }
    }
}

vector<int> newDeck() {
    vector<int> unshuffled(deck);
    vector<int> shuffled;
    for (int i = 52; i >= 1; --i) {
        int r = rand() % i;
        shuffled.push_back(unshuffled[r]);
        unshuffled.erase(unshuffled.begin() + r);
    }
    return shuffled;
}

bool run(vector<int> d) {
    // cout << "the deck: ";
    //for (int i = 0; i < d.size(); ++i) {
        //cout << d[i] << " ";
    //}
    //cout << "\n";

    // map of card value to it's position in the winning stack
    map<int,int> val;
    // map of position to it's card value in the winning stack
    vector<int> pos(10, 0);
    // stack for losing cards
    stack<int> loseStack;
    for (int i = 0; i < 52; ++i) {
        int card = d[i];
        //cout << "* CARD = " << card << "\n";
        // is it in the win stack?
        if (val.count(card)) {
            //cout << "card already in there. continuing\n";
            continue;
        }

        // can we place it?
        // find available slots for the card
        int lowPos = -1, highPos = 10;
        int low = 0, high = 14;
        // if val.size() is 0, then all positions are open
        if (val.size()) {
            // find the highest card lower than it
            // run from 0 to the card value - 1, because we will never place
            // the card in a position the same or higher than its value
            for (int j = 0; j < card; ++j) {
                if (pos[j] && pos[j] < card && pos[j] > low) {
                    lowPos = j;
                    low = pos[j];
                }
            }
            // find the lowest card higher than it
            for (int j = 9; j >= 0 && j >= card - 4; --j) {
                if (pos[j] && pos[j] > card && pos[j] < high) {
                    highPos = j;
                    high = pos[j];
                }
            }
        }

        lowPos++;
        highPos--;
        //cout << "lowPos = " << lowPos << "\n";
        //cout << "highPos = " << highPos << "\n";

        if (lowPos > highPos) {
            // cannot place card
            loseStack.push(card);
            //cout << "--could not place\n";
        } else if (highPos == lowPos) {
            // only one spot to place, so place the card
            pos[lowPos] = card;
            val[card] = lowPos;
            //cout << "--placed in " << lowPos << "\n";
        } else {
            // more than one spot to place it, choose where

            // for each position, find the difference of the # of positions
            // divided by the number of cards that can be placed and the
            // same thing on the right side

            int bestPos = lowPos;
            // why 3? 10/4 = 2.5 is the highest possible difference
            double smallestDifference = 3;

            // # of cards that can be placed on the left
            int leftCards = (card - (low + 1));
            //cout << "leftCards = " << leftCards << "\n";

            // # of cards that can be placed on the right
            int rightCards = ((high) - (card + 1));
            //cout << "rightCards = " << rightCards << "\n";
            for (int j = lowPos; j <= highPos; ++j) {
                // use j as a pivot point
                //cout << "position = " << j << "\n";
                // # of positions open on the left
                double leftFactor;
                double leftPositionsOpen = j - lowPos;
                if (leftCards > 0) {
                    leftFactor = leftPositionsOpen / leftCards;
                } else {
                    leftFactor = 3;
                }
                //cout << "leftFactor = " << leftFactor << "\n";
                // # of positions open on the right
                double rightFactor;
                double rightPositionsOpen = highPos - j;
                if (rightCards > 0) {
                    rightFactor = rightPositionsOpen / rightCards;
                } else {
                    rightFactor = 3;
                }
                //cout << "rightFactor = " << rightFactor << "\n";
                double difference = abs(leftFactor - rightFactor);
                //cout << "difference = " << difference << "\n";
                if (difference < smallestDifference) {
                    smallestDifference = difference;
                    bestPos = j;
                }
            }
            pos[bestPos] = card;
            val[card] = bestPos;
            //cout << "best position = " << bestPos << "\n";
            //cout << "--placed in " << bestPos << "\n";
        }

        // have we won?
        if (val.size() >= 10) {
            return true;
        }
        // have we lost?
        if (loseStack.size() >= 6) {
            return false;
        }
    }
    return false;
}

int main(int argc, char const* argv[])
{
    int runs = atoi(argv[1]);
    int wins = 0;
    init();
    srand(time(NULL));
    for (int i = 0; i < runs; ++i) {
        if (run(newDeck())) {
            wins++;
        }
    }
    cout << runs << " runs\n";
    cout << wins << " wins\n";
    cout << (double) wins / runs * 100 << "% win rate\n";
    return 0;
}


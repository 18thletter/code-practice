/**
 * Author: Raymund Lew
 *
 * Challenge is to write an algorithm that would give the positioning of a
 * string within all possible permutations strings sharing the same sequence
 * of letters, order of repeated letters not mattering.
 *
 * I approached this problem by writing out a bunch of strings in
 * lexicographic order and realizing that a way to solve it would be to
 * look at the first letter and figure out how many positions within the
 * ranking that I could "skip."
 *
 * I saw that if I took it one letter at a time, it would break down the
 * problem by mathematical induction, since by removing one letter, the rank
 * of a string reduced the size of the problem by one.
 *
 * I then calculated how many possible permutations there were in any given
 * string, which wasn't too hard after brushing up on some statistics.
 * The number of permutations is n! / (a!b!...), where a and b refer to any
 * letters that are repeated.
 *
 * The challenge was then to figure out how to use that to "skip" ranks
 * looking letter by letter.
 *
 * Here is my solution broken down in an example:
 * BACA
 *
 * which lies within the set of strings
 * AABC (1),
 * AACB (2),
 * ABAC (3),
 * ABCA (4),
 * ACAB (5),
 * ACBA (6),
 * BAAC (7),
 * BACA (8),
 * BCAA (9),
 * CAAB (10),
 * CABA (11),
 * CBAA (12).
 *
 * Two data structures to keep track of while we do this.
 * A map of occurrences of letters:
 * A -> 2
 * B -> 1
 * C -> 1
 *
 * and a list of sorted letters: {A, B, C}
 *
 * First letter: B
 * Can we skip anything? Look at the sorted letters...is B the first in the
 * list? No. We can skip. But how many? We can see A comes before B, but C
 * is after. So we can skip all the words beginning with A.
 * Effectively, this means we're looking at A followed by {A, B, C} in some
 * order. The possible permutations of {A, B, C} are 3!, or (n - 1)! divided
 * by factorials of any repeated letters, which in this case there are none.
 *
 * We can now add this to our final result: 3! and throw away the B.
 * We're now looking at ACA, within
 * AAC (1),
 * ACA (2),
 * CAA (3).
 *
 * Here are the updated data structures reflecting that:
 * A -> 2
 * B -> 0
 * C -> 1
 *
 * {A, C}
 *
 * Next letter: A
 * We cannot skip because there is nothing left of A
 * in the sorted list.
 *
 * Final result = 3! + 0 and throw away the A.
 * We're now looking at CA, within
 * AC (1),
 * CA (2).
 *
 * And the updated data structures:
 * A -> 1
 * B -> 0
 * C -> 1
 *
 * {A, C}
 *
 * Next letter: C
 * We can skip all words beginning with A which in this case is only one (AC).
 *
 * Final result: 3! + 0 + 1! and throw away the C.
 * We're now looking at just A, which is the trivial case.
 * Final result: 3! + 0 + 1! + 0.
 *
 * We're almost done, except that our result only contains a number in which
 * to skip. Since we're looking for the actual ranking, we can now "skip" the
 * result's worth of rankings to the ranking that we desire.
 * This effectively means we can just add 1 to arrive at the ranking we want.
 * Final result: 3! + 0 + 1! + 0 + 1
 * = (3 x 2 x 1) + 1 + 1
 * = 6 + 1 + 1
 * = 8
 *
 * And that is correct!
 */
#include <list>
#include <map>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

unsigned long long factorial(int n) {
    if (n == 0) {
        return 1;
    }

    unsigned long long fact = 1;
    for (int i = 1;i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main(int argc, char *argv[]) {
    // assume argv[1] is the string
    if (argc < 2) {
        cerr << "word plz thx\n";
        return 1;
    }

    int len = strlen(argv[1]);

    // list to hold unique sorted characters
    // note: why list? insertion/deletion is really all this container will
    // be used for. I suppose since n max is only 25, there really isn't
    // much speed savings vs an array, but whatever
    list<char> sorted;
    sorted.insert(sorted.begin(), argv[1], argv[1] + len);
    sorted.sort();
    sorted.unique();

    // map of letters to the number of occurrences in the string
    map<char,int> occurrences;
    for (int i = 0; i < len; i++) {
        occurrences[argv[1][i]]++;
    }

    // for the final result
    unsigned long long result = 1;

    for (int i = 0; i < len - 1; i++) {
        // character in question is argv[1][i]
        list<char>::iterator thisChar = find(sorted.begin(), sorted.end(), argv[1][i]);

        unsigned long long fact = factorial(len - i - 1);
        // run through the characters that are alphabetically before the character in question
        for (list<char>::iterator beforeChar = sorted.begin(); beforeChar != thisChar; ++beforeChar) {
            // used to hold intermediate permutation math
            unsigned long long Pnr = fact;
            for (map<char,int>::iterator occIt = occurrences.begin(); occIt != occurrences.end(); ++occIt) {
                // if the occurrence is 2 or higher, divide by it
                if (occIt->second > 1) {
                    if (occIt->first == *beforeChar) {
                        Pnr /= factorial(occIt->second - 1);
                    } else {
                        Pnr /= factorial(occIt->second);
                    }
                }
            }
            // add the factorial answer to the final result
            result += Pnr;
        }
        // at this point, we're finished with the character in question
        // we can update the occurrences and sorted data structures
        occurrences[*thisChar]--;
        if (occurrences[*thisChar] == 0) {
            // if there are no more occurrences of the character,
            // remove it from the sorted character list
            sorted.erase(thisChar);
        }
    }

    cout << result << "\n";

    return 0;
}


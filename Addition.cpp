//
// Created by sentimental on 08.04.20.
//
#include "Addition.h"

string Hex(int number) {
    vector<pair<int, string>> dictionary = {{0,  "0"},
                                            {1,  "1"},
                                            {2,  "2"},
                                            {3,  "3"},
                                            {4,  "4"},
                                            {5,  "5"},
                                            {6,  "6"},
                                            {7,  "7"},
                                            {8,  "8"},
                                            {9,  "9"},
                                            {10, "A"},
                                            {11, "B"},
                                            {12, "C"},
                                            {13, "D"},
                                            {14, "E"},
                                            {15, "F"}};
    string result = "|";
    if (number == 0)return "|0000|";
    if (number == -1)return "|----|";
    int remainder = number;
    while (remainder != 0) {
        for (int i = 0; i < dictionary.size(); i++) {
            if (remainder % 16 == dictionary[i].first) {
                result.insert(0, dictionary[i].second);
            }
        }
        remainder /= 16;
    }
    for (int i = result.size(); i < 5; i++) {
        result.insert(0, "0");
    }
    result.insert(0, "|");

    return result;
}
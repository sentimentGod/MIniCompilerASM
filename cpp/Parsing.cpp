#include "Parsing.h"

void IfDirectiveWorking() {
    for (int i = 0; i < AllTokens.size(); i++) {
        if (AllTokens[i].empty())continue;

        if (AllTokens[i][0].name == "if") {

            for (auto it: MassOfUser) {
                if(it.name == AllTokens[i][1].name){
                    if(it.size == 0){
                        lexeme Comment;
                        Comment.name = ";";
                        int j = i;
                        while(AllTokens[j][0].name != "endif"){
                            AllTokens[j].insert(AllTokens[j].begin(),Comment);
                            j++;
                        }
                    }
                }
            }

        }
    }
}

bool compareByLength(const User &a, const User &b)
{
    return a.segment.size() > b.segment.size();
}

void FillMassOfUsers() {
    User alone;
    int flagOgSeg = 0;
    for (int i = 0; i < AllTokens.size(); i++) {
        if (AllTokens[i].empty())continue;
        for (int j = 0; j < AllTokens[i].size() - 1; j++) {
            if (AllTokens[i][j].type == label) {
                alone.name = AllTokens[i][j].name;
                alone.type = AllTokens[i][AllTokens[i].size() - 2].type;
                alone.directiveOfThis = AllTokens[i][AllTokens[i].size() - 2].type;
                alone.size = Dec(AllTokens[i][AllTokens[i].size() - 1].name);
                for (auto k = i + 1; k < AllTokens.size(); k++) {
                    for (auto m = 0; m < AllTokens[k].size(); m++) {
                        if (AllTokens[k][m].name == "ends") {
                            alone.segment = AllTokens[k][m - 1].name;
                            flagOgSeg = 1;
                            break;
                        }
                    }
                    if(flagOgSeg)break;
                }
                MassOfUser.push_back(alone);
                flagOgSeg = 0;
            }
            if ((AllTokens[i][j].type == userId) && (AllTokens[i][j + 1].type == directive)) {
                alone.name = AllTokens[i][j].name;
                alone.type = AllTokens[i][AllTokens[i].size() - 1].type;
                alone.directiveOfThis = AllTokens[i][AllTokens[i].size() - 2].name;
                alone.size = Dec(AllTokens[i][AllTokens[i].size() - 1].name);
                if (alone.directiveOfThis == "equ") {
                    alone.segment = "";
                    MassOfUser.push_back(alone);
                }
                else {
                    for (auto k = i + 1; k < AllTokens.size(); k++) {
                        for (auto m = 0; m < AllTokens[k].size(); m++) {
                            if (AllTokens[k][m].name == "ends") {
                                alone.segment = AllTokens[k][m - 1].name;
                                flagOgSeg = 1;
                                break;
                            }
                        }
                        if(flagOgSeg)break;
                    }
                    MassOfUser.push_back(alone);
                }
                flagOgSeg = 0;

            }
        }
    }
    sort(MassOfUser.begin(),MassOfUser.end(), compareByLength);
}

void LoadFromFile(const char *file) {
    string line;
    string solo = "";
    int indicator_of_rows = 0;
    int indicator_of_lexems = 0;
    lexeme one;
    vector<lexeme> one_row;
    ifstream in_for_numbers(file);

    if (in_for_numbers.is_open()) {
        while (getline(in_for_numbers, line)) {
            indicator_of_lexems = 0;
            for (int i = 0; i < line.size(); i++) {
                if ((line[i] == ' ') || (line[i] == '\t'))continue;
                solo += line[i];
                if(line[i] == '[') {
                    IdentifyLexeme(one, solo, indicator_of_rows, indicator_of_lexems);
                    indicator_of_lexems++;
                    one_row.push_back(one);
                    solo.clear();
                }
                if (line[i + 1] == '\0') {
                    IdentifyLexeme(one, solo, indicator_of_rows, indicator_of_lexems);
                    indicator_of_lexems++;
                    one_row.push_back(one);
                    solo.clear();
                }
                if ((line[i + 1] == ' ') || (line[i + 1] == '\t') || (line[i + 1] == ':') || (line[i + 1] == ',')
                    || (line[i + 1] == '[') || (line[i + 1] == ']') || (line[i + 1] == '*')|| (line[i + 1] == '+')) {
                    IdentifyLexeme(one, solo, indicator_of_rows, indicator_of_lexems);
                    indicator_of_lexems++;
                    one_row.push_back(one);
                    solo.clear();
                    if ((line[i + 1] == ':') || (line[i + 1] == ',')
                        || (line[i + 1] == '[') || (line[i + 1] == ']') || (line[i + 1] == '*')|| (line[i + 1] == '+')) {
                        i++;
                        solo += line[i];
                        IdentifyLexeme(one, solo, indicator_of_rows, indicator_of_lexems);
                        indicator_of_lexems++;
                        one_row.push_back(one);
                        solo.clear();
                    }
                    if (line[i+1] == ',') {
                        i++;
                        solo += line[i];
                        IdentifyLexeme(one, solo, indicator_of_rows, indicator_of_lexems);
                        indicator_of_lexems++;
                        one_row.push_back(one);
                        solo.clear();
                    }

                }
            }
            indicator_of_rows++;
            AllTokens.push_back(one_row);
            one_row.clear();
        }
    }

    in_for_numbers.close();

    for (int i = 0; i < AllTokens.size(); i++) {
        for (int j = 1; j < AllTokens[i].size(); j++) {
            if ((AllTokens[i][j].name == ":") && (AllTokens[i][j - 1].type == userId)) {
                AllTokens[i][j - 1].type = label;
            }
        }
    }

    for (int i = 0; i < AllTokens.size(); i++) {
        for (int j = 0; j < AllTokens[i].size(); j++) {
            int flag = 0;
            if (AllTokens[i][j].name == "jz") {
                for (int k = 0; k < i; k++) {
                    for (int l = 0; l < AllTokens[k].size(); l++) {
                        if ((AllTokens[k][l].name == AllTokens[i][j + 1].name) && (AllTokens[k][l].type == label)) {
                            flag = 1;
                            AllTokens[i][j + 1].type = label;
                            break;
                        }
                    }
                }
                if (flag == 0)AllTokens[i][j + 1].type = undefined;
            }
        }
    }
}

void IdentifyLexeme(lexeme &one, string line, int indicator_of_rows, int indicator_of_lexems) {
    one.number_of_lexem = indicator_of_lexems;
    one.number_of_row = indicator_of_rows;
    one.length = line.size();
    bool flag_16const = false;
    bool flag_10const = true;
    bool flag_charconst = false;
    if ((line[0] == '\"') && (line[line.size() - 1] == '\"')) {
        bool flag_charconst = true;
        for (int i = 0; i < line.size(); i++) {
            if (isdigit(line[i])) {
                flag_charconst = false;
            }
        }
        if (flag_charconst) {
            one.name = line;
            one.name.erase(0, 1);
            one.name.erase(one.name.size() - 1, 1);
            one.type = constChar;

            return;
        }
    }
    std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::tolower(c); });
    one.name = line;
    if ((line == ":") || (line == ",") || (line == "[") || (line == "]") || (line == "*")|| (line == "+")) {
        one.type = singleLexeme;
    } else {
        for (auto i : DictionaryOfTokens) {
            for (auto j: i.second) {
                if (line == j) {
                    one.type = i.first;
                    return;
                }
            }

        }
        for (int i = 0; i < line.size(); i++) {
            if (!isdigit(line[i])) {
                flag_10const = false;
            }
            if ((i == line.size() - 1) && (flag_10const == true)) {

                one.type = constDecimal;
                return;
            }
            if ((isdigit(line[0])) && (line[line.size() - 1] == 'h')) {

                one.type = constHex;
                return;
            }
        }
        one.type = userId;
    }
}

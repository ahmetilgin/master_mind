#include "computer.h"
#include <iostream>
computer::computer()
{
    create_set();
    candidate_solutions.insert(candidate_solutions.end(), combinations.begin(), combinations.end());
}

void computer::create_set()
{
    std::vector<int> current(CODE_LENGTH, 0);
    std::vector<int> elements;

    for (int i = 1; i <= NUM_COLOURS; ++i) {
        elements.push_back(i);
    }

    combination_recursive(CODE_LENGTH, 0, current, elements);
}

void computer::combination_recursive(int combinationLength, int position, std::vector<int> &current, std::vector<int> &elements) {

    if (position >= combinationLength) {
        std::map<int, int > res;

        if(current.size() == 4){
            for(auto cur: current){
                if(res.find(cur) == res.end()){
                    res[cur] = 0;
                }
                res[cur]++;
                if(res[cur] > 1){
                    return;
                }
            }
            combinations.push_back(current);
        }


        return;
    }

    for (int j = 0; j < elements.size(); ++j) {
        current[position] = elements[j];
        combination_recursive(combinationLength, position + 1, current, elements);
    }
    return;
}

QString computer::check_code(std::vector<int> guess, std::vector<int> code) {

    QString result;

    //Get black/coloured
    for (int i = 0; i < CODE_LENGTH; ++i) {

        if (guess[i] == code[i]) {
            result.append("B");
            guess[i] *= -1;
            code[i] *= -1;
        }
    }

    //Get white
    for (int i = 0; i < CODE_LENGTH; ++i) {

        if (code[i] > 0) {

            std::vector<int>::iterator it = find(guess.begin(), guess.end(), code[i]);
            int index;
            if (it != guess.end()) {

                index = distance(guess.begin(), it);
                result.append("W");
                guess[index] *= -1;
            }
        }
    }
    return result;
}

int computer::get_max_score(std::map<QString, int> inputMap) {

    int max = 0;
    for (auto elem : inputMap) {
        if (elem.second > max) {
            max = elem.second;
        }
    }

    return max;
}

int computer::get_min_score(std::map<std::vector<int>, int> inputMap) {
    int min = std::numeric_limits<int>::max();
    for (auto elem : inputMap) {
        if (elem.second < min) {
            min = elem.second;
        }
    }

    return min;
}


std::vector<std::vector<int>> computer::minmax() {

    std::map<QString, int> scoreCount;
    std::map<std::vector<int>, int> score;
    std::vector<std::vector<int>> nextGuesses;
    int max, min;

    for (int i = 0; i < combinations.size(); ++i) {

        for (int j = 0; j < candidate_solutions.size(); ++j) {

            QString pegScore = check_code(combinations[i], candidate_solutions[j]);
            if (scoreCount.count(pegScore) > 0) {
                scoreCount.at(pegScore)++;
            } else {
                scoreCount.emplace(pegScore, 1);
            }
        }

        max = get_max_score(scoreCount);
        score.emplace(combinations[i], max);
        scoreCount.clear();
    }

    min = get_min_score(score);

    for (auto elem : score) {
        if (elem.second == min) {
            nextGuesses.push_back(elem.first);
        }
    }

    return nextGuesses;
}

void computer::prune_codes(std::vector<std::vector<int>> &set, std::vector<int> currentCode, QString currentResponse) {

    auto response = currentResponse.split(",");
    QString b_response = "";

    for(int i = 0; i < response[0].toInt();i++){
        b_response.append("B");
    }

    for(int i = 0; i < std::abs(response[1].toInt());i++){
        b_response.append("W");
    }

    int index;
    std::vector<std::vector<int>>::iterator it = set.begin();

    while (it != set.end()) {
        index = distance(set.begin(), it);
        auto res = check_code(currentCode, set[index]);

        if (b_response != res) {
            it = set.erase(set.begin() + index);
        } else {
            it++;
        }
    }
}

void computer::remove_code(std::vector<std::vector<int>> &set, std::vector<int> currentCode) {
    int index;
    for (auto it = set.begin(); it != set.end(); it++) {
        index = distance(set.begin(), it);

        if (set[index] == currentCode) {
            set.erase(set.begin() + index);
            break;
        }
    }
}

void computer::insert_guess(QString code, QString result){
    std::vector <int>guess{code.at(0).digitValue(),code.at(1).digitValue(),code.at(2).digitValue(),code.at(3).digitValue()};
    remove_code(combinations, guess);
    remove_code(candidate_solutions, guess);
    prune_codes(candidate_solutions, guess, result);
}

QString computer::vector_to_qstring(std::vector<int> vec){
    QString response = "";
    for(auto v: vec){
        response.append(QString::number(v));
    }
    return response;
}

QString computer::get_next_guess() {

    std::vector<int> nextGuess;
    next_guesses = minmax();


    for (int i = 0; i < next_guesses.size(); ++i) {
        if (find(candidate_solutions.begin(), candidate_solutions.end(), next_guesses[i]) != candidate_solutions.end()) {
            return vector_to_qstring(next_guesses[i]);
        }
    }
    for (int j = 0; j < next_guesses.size(); ++j) {
        if (find(combinations.begin(), combinations.end(), next_guesses[j]) != combinations.end()) {
            return vector_to_qstring(next_guesses[j]);
        }
    }

    return vector_to_qstring(nextGuess);
}


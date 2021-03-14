#ifndef COMPUTER_H
#define COMPUTER_H

#include <QObject>
#include <vector>
#include <vector>
#include <algorithm>
#include <map>
#define NUM_COLOURS 9
#define CODE_LENGTH 4

class computer: public QObject
{
    Q_OBJECT
public:
    computer();
    void create_set();

public slots:
    QString get_next_guess();
    void insert_guess(QString code, QString result);
private:
    void combination_recursive(int combinationLength, int position, std::vector<int> &current, std::vector<int> &elements);
    void remove_code(std::vector<std::vector<int> > &set, std::vector<int> currentCode);
    void prune_codes(std::vector<std::vector<int> > &set, std::vector<int> currentCode, QString currentResponse);
    std::vector<std::vector<int> > minmax();
    QString vector_to_qstring(std::vector<int> vec);
    QString check_code(std::vector<int> guess, std::vector<int> code);
    int get_max_score(std::map<QString, int> inputMap);
    int get_min_score(std::map<std::vector<int>, int> inputMap);

private:
    std::vector<std::vector<int>> combinations; //Master set of combinations 1111 to 6666
    std::vector<std::vector<int>> candidate_solutions;
    std::vector<std::vector<int>> next_guesses;
    std::vector<int> code;

};

#endif // COMPUTER_H

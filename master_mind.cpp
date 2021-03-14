#include "master_mind.h"
#include <time.h>

master_mind::master_mind()
{
    generate_number_to_guess();
}

int master_mind::get_number_to_guess() const
{
    return m_number_to_guess;
}

void master_mind::set_number_to_guess(int val)
{
    if(val != m_number_to_guess){
        m_number_to_guess = val;
        emit number_to_guess_changed();
    }
}

void master_mind::generate_number_to_guess(){
    QString result = "";
    while(result.length() < 4){
        QString rnd = QString::number(rand() % 10 + 1);
        if(!result.contains(rnd)){
            result.append(rnd);
        }
    }
    set_number_to_guess(result.toInt());
}

QString master_mind::calculate_result(QString input){
    QString result = "";
    bool isInteger = false;
    int i_input = input.toInt(&isInteger);
    if(isInteger){

        if(i_input == m_number_to_guess){
            return "Success";
        }

        auto s_number_to_guess = QString::number(m_number_to_guess);
        int positive = 0;
        int negative = 0;
        for(int i = 0; i < input.size(); i++){
            if(s_number_to_guess.at(i) == input.at(i)){
                positive++;
            }else if (input.contains(s_number_to_guess.at(i))){
                negative--;
            }
        }
        result.append(QString::number(positive) + "," + QString::number(negative));
    }else{
        result = "Only Integers Can Be Accepted";
    }

    return result;
}

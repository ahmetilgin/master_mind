#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <qobject.h>

class master_mind: public QObject{
    Q_OBJECT
    Q_PROPERTY(int number_to_guess READ get_number_to_guess WRITE set_number_to_guess NOTIFY number_to_guess_changed)

public:

    master_mind();
    int get_number_to_guess() const;
    void set_number_to_guess(int number_to_guess);
    void generate_number_to_guess();

public slots:
    QString calculate_result(QString input);
signals:
    void number_to_guess_changed();

private:
    int m_number_to_guess;
};


#endif // MASTERMIND_H

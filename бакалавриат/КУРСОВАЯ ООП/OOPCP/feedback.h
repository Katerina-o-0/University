//feedback.h
#ifndef FEEDBACK_H
#define FEEDBACK_H
#include <QWidget>


class feedback
{
    int id;
    QString fb;
public:
    feedback(int,QString);
    int get_id();
    QString get_fb();
};

#endif // FEEDBACK_H




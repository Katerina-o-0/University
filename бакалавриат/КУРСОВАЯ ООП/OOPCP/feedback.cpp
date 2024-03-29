#include "feedback.h"

feedback::feedback(int id, QString fb)
{
    this->id=id;
    this->fb=fb;
}


int feedback::get_id()
{
    return id;
}

QString feedback::get_fb()
{
    return fb;
}

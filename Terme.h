//
// Created by isen on 04/05/18.
//

#ifndef PROJETC_TERME_H
#define PROJETC_TERME_H

#endif //PROJETC_TERME_H


#include <string>

class Terme {
public:
    public: std::string value;
    public: int type;

    const std::string &getValue() const;

    void setValue(const std::string &value);

    int getType() const;

    void setType(int type);

};

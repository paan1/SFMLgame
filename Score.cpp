#include "Score.h"

Score::Score(std::string name, unsigned long score) {

    this->name = name;
    this->score = score;
}

/**
 * �絪���
 *
 * @param string
 */
void Score::setName(std::string name) {

    this->name = name;
}

/**
 * �֧����
 *
 * @return string
 */
std::string Score::getName() {

    return this->name;
}

/**
 * �絤�ṹ
 *
 * @param int
 */
void Score::setScore(unsigned long score) {

    this->score = score;
}

/**
 * �֧��ṹ
 *
 * @return int
 */
unsigned long Score::getScore() {

    return this->score;
}
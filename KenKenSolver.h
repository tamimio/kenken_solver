#ifndef KENKENSOLVER_H
#define KENKENSOLVER_H

#include <vector>
#include "QString"

/* --------------------------------------------------------------------------- *
 * ------------------------------ KenKen Sections ------------------------------
 * Contains i-j-indices of the elements of the given rule,
 *          rule operation and needed result.
 * Can check if the rule is true.
 * -------------------------------------------------------------------------- */
class KenKenSection
{
    std::vector <unsigned short> ind_i, /* vector of i-indices of elements */
                                 ind_j; /* vector of j-indices of elements */
    char oper;                          /* operation to compute */
    unsigned short res;                 /* expected result */

    // bool isFull();
    // bool isValid();
 public:
    KenKenSection();
    ~KenKenSection(){}
    bool checkRule(std::vector<std::vector<int> > & matrix); /* checks if rule is true */

    friend class KenKenSolver;
};

/* --------------------------------------------------------------------------- *
 * ------------------------------- KenKen Solver -------------------------------
 * Contains sections of rules.
 * Can read task from file, draw field of this task, and solve it.
 * -------------------------------------------------------------------------- */
class KenKenSolver
{
    bool flagTaskLoaded;                  /* is task loaded */
    int fieldSize;                        /* size of the filed */
    std::vector <KenKenSection> sections; /* sections with rules */
    std::vector<std::vector<int> > Field; /* matrix with resulting numbers */

    void parseLine(QString * line, KenKenSection * section); /* parse line with rule*/
    int determSize();                     /* determine the size of the field */
    void fillField();           /* random filling of the resulting matrix */

 public:
    KenKenSolver();
    ~KenKenSolver(){}

    void readTask(QString _filename);          /* read task from text file */
    void solveTask();                          /* solve task */
    std::vector<std::vector<int> > getField(); /* returns resulting matrix */
    int getSize();                             /* returns the size of the field */
    std::pair<std::vector<QString>, std::vector<std::vector<int> > > getRules();
};

#endif // KENKENSOLVER_H

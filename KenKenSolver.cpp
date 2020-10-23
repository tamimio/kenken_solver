#include "KenKenSolver.h"

#include "QDebug"       // tmp
#include "QFile"        // open file
#include "QMessageBox"  // error-window

#include <cmath> // abs(), max(), min()
#include <algorithm>

#include <sstream>


/* --------------------------------------------------------------------------- *
 * ------------------------------ KenKen Sections ------------------------------
 * -------------------------------------------------------------------------- */

/* -------------------------------------------------------------- constructor */
KenKenSection::KenKenSection()
{ res=0; }

/* ---------------------------------------------------------------- checkRule */
bool KenKenSection::checkRule(std::vector<std::vector<int> > & matrix)
{
    int r;                       /* intermidiate results */
    int elem_num = ind_i.size(); /* number of elemets to compute */

    switch(oper)
    {
        case '+' :                              /* SUM */
            r=0;
            for (int i=0; i<elem_num; ++i)
                r += matrix[ind_i[i]][ind_j[i]];
            break;

        case '-' :                              /* SUB */
            r = abs( matrix[ind_i[0]][ind_j[0]]-matrix[ind_i[1]][ind_j[1]] );
            break;

        case '*' :                              /* MUL */
            r=1;
            for (int i=0; i<elem_num; ++i)
                r *= matrix[ind_i[i]][ind_j[i]];
            break;

        case ':' :                              /* DIV */
        case '/' :
            r = std::max(matrix[ind_i[0]][ind_j[0]],matrix[ind_i[1]][ind_j[1]])
              / std::min(matrix[ind_i[0]][ind_j[0]],matrix[ind_i[1]][ind_j[1]]);
            break;

        default:                            /* THIS NUMBER */
            r=matrix[ind_i[0]][ind_j[0]];
            break;
    } /* switch(oper) */

    if (r==res)
        return true;
    else
        return false;
}


/* --------------------------------------------------------------------------- *
 * ------------------------------- KenKen Solver -------------------------------
 * -------------------------------------------------------------------------- */

/* -------------------------------------------------------------- constructor */
KenKenSolver::KenKenSolver()
{ flagTaskLoaded=0; }

/* ----------------------------------------------------------------- readTask */
void KenKenSolver::readTask(QString _filename)
{
    /* open file with task */
    QFile input_file(_filename);
    if (!input_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    /* read each line of the file */
    int i=0;
    while (!input_file.atEnd())
    {
        QString line = input_file.readLine();
        sections.push_back(KenKenSection()); /* 1 line = +1 section */
        try
        {
            parseLine(&line, &sections[i]);
        }
        catch (int err_position)
        {
            sections.clear();
            flagTaskLoaded=0;
            throw i+1; //throw std::make_pair(i, err_position);
        }
        i++;
    } /* while */

    fieldSize = determSize();
    flagTaskLoaded=1;
}

/* ---------------------------------------------------------------- parseLine */
void KenKenSolver::parseLine(QString * line, KenKenSection * section)
{
    enum {init, ind, res_op, err, fin} state;
    state=init;

    int j=0; /* iterate through line */

    while (state!=fin)
    {
        switch (state)
        {
            case init:
                state = ind;

            case ind:                            /* INDICES */
                int tmp1,tmp2;
                qDebug()<<line->mid(j,3).toLatin1();
                sscanf(line->mid(j,3).toLatin1(), "%d,%d", &tmp1, &tmp2);
                if (((tmp1>=1 && tmp1<=9)&&(tmp2>=1 && tmp2<=9))==0)
                {
                    state = err;
                }
                else
                {
                    section->ind_i.push_back(tmp1-1);
                    section->ind_j.push_back(tmp2-1);
                    j+=3;
                    if (line->at(j).toLatin1()==';')
                    {
                        state = ind;
                        j++; /* space after ; */
                    }
                    else
                        state = res_op;
                }
                break;

            case res_op:                   /* OPERATION and RESULT */
                while (line->at(j).toLatin1()==' ') j++;
                qDebug()<<line->mid(j).toLatin1();
                sscanf(line->mid(j).toLatin1(), "%d%c", &section->res, &section->oper);
                state = fin;
                break;

            case err:
                throw 1;

            case fin: break;
        } // switch
        j++; /* move to the next symbol */
    } // while
}


/* --------------------------------------------------------------- determSize */
int KenKenSolver::determSize()
{
    int max_ind = 1;
    for (int i=0; i<sections.size(); ++i)
    {
        max_ind = std::max( max_ind, static_cast<int>(
                    * std::max_element(sections[i].ind_i.begin(), sections[i].ind_i.end()))
                    );
        max_ind = std::max( max_ind, static_cast<int>(
                    * std::max_element(sections[i].ind_j.begin(), sections[i].ind_j.end()))
                    );
    }
    return max_ind+1;
}


/*void KenKenSolver::drawField()
{qDebug()<<"drawField\n";}*/

// random generator function:
int myrandom (int i) { return std::rand()%i;}


void KenKenSolver::fillField()
{
    std::vector<int> one_row; /* row for for the the matrix */
    for (int i=1; i<fieldSize+1; ++i)
        one_row.push_back(i);
    std::random_shuffle(one_row.begin(),one_row.end(),myrandom);
    Field.push_back(one_row);

    for(int i=1; i<fieldSize; ++i)
    {
         bool unique;
         do
         {
             unique = 1;
             std::random_shuffle(one_row.begin(),one_row.end(),myrandom);

             for (int z=0; z<i; ++z) /* check all previous rows */
             {
                 for (int k=0; k<fieldSize; ++k) /* check every element of the row */
                 {
                     if(Field[z][k]==one_row[k])
                     {
                         unique=0;
                         break;
                     }
                 }
             } /*for prev. rows */
         }
         while (unique==false);

         Field.push_back(one_row);
    }
}

/* ---------------------------------------------------------------- solveTask */
void KenKenSolver::solveTask()
{
    if (flagTaskLoaded)
    {
        bool task_solved = 0; /* условие продолжения перебора */
        while(!task_solved)
        {
            task_solved = 1;

            /* - create new matrix - */
            Field.clear();
            fillField();

            /* - check all rules - */
            for(int i=0; i<sections.size(); ++i)
            {
                if(!sections[i].checkRule(Field))
                {
                    task_solved = 0;
                    break;
                }
            }
        }
    }
    else
    {
        throw(1);
    }
}

/* --------------------------------------------------------------------- GETs */
std::vector<std::vector<int> > KenKenSolver::getField()
{ return Field; }

int KenKenSolver::getSize()
{ return fieldSize; }

std::pair<std::vector<QString>, std::vector<std::vector<int> > > KenKenSolver::getRules()
{

    std::vector<QString> rules;
    std::vector<std::vector<int> > elements;
    int k = sections.size(); //!
    for(int i=0; i<sections.size(); ++i)
    {

        QString qstr;
        qstr.sprintf("%d%c", sections[i].res, sections[i].oper);
        rules.push_back(qstr);

        std::vector<int> s;
        for(int j=0; j<sections[i].ind_i.size(); ++j)
            s.push_back(sections[i].ind_i[j]*fieldSize+sections[i].ind_j[j]);
        elements.push_back(s);
    }


    int u=0;
    return std::make_pair<std::vector<QString>, std::vector<std::vector<int> > >
            (rules, elements);
}

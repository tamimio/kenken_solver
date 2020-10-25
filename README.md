# KenKen solver
Following program implements a naive method of solving the KenKen puzzle 3x3 and 4x4 of size.
Folders `examples` and `screens` contain several examples of the puzzle and the way program solved them.
Tested in Win7 x64.

## Start
Base view of the program:
![alt text](https://github.com/tamimio/kenken_solver/screens/prompt.png)

## Load puzzle
First, you need to load puzzle description via "Загрузить" button. It must be in `*.txt` formatted in the following way:
```
1,1; 2,1 3+
1,2; 2,2 5+
1,3 1
3,1; 3,2 4+
2,3; 3,3 5+
```
***./examples/2.txt***

After the task is loaded successfully, the field would be drawn:
![alt text](https://github.com/tamimio/kenken_solver/screens/2_loaded.png)
***./screens/2_loaded.png***

## Solve puzzle
To solve the puzzle it is needed to press "Решить" button. After the task is solved successfully, the field would be filled:
![alt text](https://github.com/tamimio/kenken_solver/screens/2_solved.png)
***./screens/2_solved.png***

Then, you can load another puzzle.
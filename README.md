# Minesweeper
Minesweeper game made with C++
### Introduction
The goal of this game is to flag all the mines and dig up all the other cells. To know where the mines are we will take a look at the number of 
a cell that has aready been dug, the number *n* tells us surround that 3x3 area there will be *n* mines. 

![Mine num](https://user-images.githubusercontent.com/94738674/169289393-7a1fc2df-3062-4ce9-8d31-29ea463ec213.png)

In the above example, the currently selecting cell **must** have a mine since the number *1* above it tells us there is only *1* mine in it's 3x3 
area and since the currently selecting cell is the only cell that hasn't been dug yet so it **must** be a mine.

To move the red cursor around we use **W, A, S, D** or arrow keys, to dig a cell we use **J**, to flag it we use **K**
We have also added a faster way to dig and flag all the remaining cells by pressing **L** on a numbered cell. If all *n* mines around the cell has already
been flagged it will dig up all the remain cells, if the number of *notDigged* cells is less than or equal to *n* and we haven't flagged all the mines
it will flags all of the remain cells. Otherwise it does nothing.

### Currently missing features:

- Leaderboard which will show top players with the shortest time.
- Sound effects, better visual effects.

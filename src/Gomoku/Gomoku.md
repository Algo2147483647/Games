# Gomoku

[TOC]

## Entities

### Board
The game is typically played on a square board with a grid of 15x15 intersections.
$$
\boldsymbol B \in \{Empty, Black, White\}^{15 \times 15}
$$

### Stones
The stones are divided into black and white, with each side holding one color piece in the game.
$$
action = (x, y, color) \in (1:n, 1:n, \{Black, White\})  \tag{棋分黑白}
$$

## Rules

### Actions
- Players take turns placing one stone of their color on an empty intersection on the board.
- The player with the black stones usually goes first.
- After the stone is set, it will no longer move towards other points.

$$
\begin{align*}
  s_{1, c} &= 1  \tag{黑先白后}\\
  \boldsymbol B_0 &= \boldsymbol 0  \tag{空枰开局}\\
  s_{k,c} &= -s_{k-1, c}  \tag{交替落子}\\
  \boldsymbol B_{k} &= \boldsymbol B_{k-1} + (s_{k, c})_{s_{k, x}, s_{k, y}}  \\
  \boldsymbol B_{k-1}[s_{k, x}, s_{k, y}] &= 0
\end{align*}
$$

### Reward: Five-in-a-row

- The main goal is to create an unbroken row of five stones of your color horizontally, vertically, or diagonally on the board.
- The first player to achieve a row of five stones wins the game.

###  Forbidden Moves

These rules are designed to prevent certain unfair or overly advantageous situations.

#### Double Three

Placing two sets of three stones in a line with an open end on each side is often forbidden. This rule prevents players from creating multiple potential winning combinations simultaneously, making the game more strategic.

#### Double Four

Similar to the double-three rule, the double-four rule prohibits a player from creating two sets of four stones in a row with an open end on each side. This prevents situations where a player could win by creating two winning sequences simultaneously.

#### Overline

Creating more than five consecutive stones in a row is typically considered a winning move in Five-in-a-row. However, some variations introduce a forbidden hand rule to limit the length of a winning sequence, preventing players from creating an excessively long row of stones.

### Soosorv-8

1. The first player puts one of the 26 openings.
2. The other player has the right to swap.
3. The white player puts the 4th move anywhere on board and declares whether there will be 1, 2, 3 or 4 fifth moves offered in the game.
4. The other player has a right to swap.
5. The black player puts as many 5th moves on the board as it was declared before. The fifth moves can not be symmetrical.
6. The white player chooses one 5th from these offerings and plays the 6th move


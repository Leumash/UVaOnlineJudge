# Tower of Cubes

Solved the problem with both Topological Sort and Dynamic Programming.

## Dynamic Programming

The method to solve with dynamic programming is to keep an array a[], initially 0, where a[i] is the height of the tallest stack so far with color i being on top. Then for each block, try to stack the block on top of every stack.

### Example

Say a[] currently has the values:

Index:  0 1 2 3 4 5 6
Height: 3 2 5 1 6 4 0

And the next cube c has the colors:

Front:  2
Back:   3
Left:   5
Right:  5
Top:    3
Bottom: 0

For all 6 pairs of sides (front-back, back-front, left-right, right-left, top-bottom, bottom-top), attempt to stack the cube c on top of the current stack.

Consider the front-back pair of 3 0

Then you can stack cube c on the existing stack of cubes at a[0] to achieve a stack of height 4.

The new top is 3.

a[3] currently has a stack of 1 cube. Thus replace a[3] with the new stack of cube c + a[0].

Repeat this for the other 5 pairs.


# Sudoku solver
A simple program for solving 9x9 sudoku problems. No dependencies other than libc.
### File format is plain ascii with spaces between numbers 0-9
- Example:
	0 0 0 8 0 9 0 0 1
	0 0 0 0 1 0 9 3 0
	4 1 0 0 0 3 6 0 8
	6 0 0 3 9 0 2 1 0
	0 8 0 7 0 4 0 6 0
	0 9 5 0 2 1 0 0 4
	9 0 3 1 0 0 0 7 6
	0 7 4 0 3 0 0 0 0
	5 0 0 2 0 7 0 0 0

A typical sudoku uses numbers 1-9. 0 represents empty cells and is recognized by the program as such.
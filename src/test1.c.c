/*
 ============================================================================
 Name        : c.c
 Author      : SaiPraneeth
 Version     :
 Copyright   : self
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Implicit Declaration of functions*/
int loadChessBordStatus();
int* calculatePosition(char position[]);
int getPieceValueAtIndex(char piece[]);
void subString(char denstination[], char source[], int startIndex, int endIndex);
void setPiece(char pieceDetails[]);
int getPieceValue(char pieceName[]);

void moveable();
void copyIntArray(int target[], int* source, int size);
int isKnightMovable(int p1[], int p2[]);
int isKingMovable(int p1[], int p2[]);
int isMovableStraight(int p1[], int p2[]);
int isMovableCross(int p1[], int p2[]);
int isPawnMovable(int p1[], int p2[]);
void move(int p1[], int p2[]);
int validateEqualityInPositions(int row1, int col1, int row2, int col2);
void ischeck(char a[]);
int* calculatePieceLocation(int pieceValue);
int findCheck(char a[], int kingLocaton[]);

int chessBordStatus[8][8]; //chessBordStatus -contains the position of individual pieces

int main() {
	char a[5];

	loadChessBordStatus();
	moveable();
	printf("\n Enter b for black's turn,w for white's turn");
	scanf("%s", a);
	ischeck(a);
	printf("\n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf(" %d\t", chessBordStatus[i][j]);
		}
		printf("\n");
	}
	return 0;
}

/*This Function loads the positions of chess pieces on the chess board*/
int loadChessBordStatus() {
	char bordStatus[170];

	/*	char bordStatus[170] = { ' ', 'W', 'K', 'B', '1', ' ', 'W', 'Q', 'D', '7',
	 ' ', 'W', 'R', 'G', '3', ' ', 'W', 'P', 'A', '2', ' ', 'W', 'P',
	 'B', '2', ' ', 'W', 'P', 'C', '2', ' ', 'W', 'P', 'H', '2', ' ',
	 'B', 'K', 'F', '7', ' ', 'B', 'Q', 'A', '5', ' ', 'B', 'R', 'F',
	 '6', ' ', 'B', 'R', 'F', '8', ' ', 'B', 'P', 'B', '7', ' ', 'B',
	 'P', 'C', '7' };*/
	int noOfPieces = 0;
	printf("Please Enter the Status of Chess Board\n");
	scanf("%d", &noOfPieces);

	scanf("%[^\n]%*c", bordStatus);

	int startIndex = 1; // to remove the first space that is read from console after the number
	for (int k = 0; k < noOfPieces; k++) {
		char pieceDetails[4];
		subString(pieceDetails, bordStatus, startIndex, startIndex + 3);
		// printf("\n Start Index:%d \t End Index %d",startIndex,startIndex+3);
		setPiece(pieceDetails);
		startIndex += 5;
		// printf("\n after Adding Start Index:%d \t End Index %d",startIndex,startIndex+3);
	}
	// printf("%d\n",noOfPieces);
	printf("\n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf(" %d\t", chessBordStatus[i][j]);
		}
		printf("\n");
	}
	return 0;
}

void setPiece(char pieceDetails[]) {
	char squareName[2];
	squareName[0] = pieceDetails[2]; //sets Column
	squareName[1] = pieceDetails[3]; //sets row
	int *pos = calculatePosition(squareName);
//	printf("\n position X:%d\t position Y: %d\n",*(pos),*(pos+1));
	char pieceName[2];
	pieceName[0] = pieceDetails[0];
	pieceName[1] = pieceDetails[1];
	int pieceValue = getPieceValue(pieceName);

	chessBordStatus[*pos][*(pos + 1)] = pieceValue;
}

/* Returns the position array (column,row) in the chess board for the given square name */
int* calculatePosition(char squareName[]) {
	static int position[2] = { 0, 0 };
	int columnPos = squareName[0];
	position[0] = 7 - (squareName[1] - 49); //set row
	position[1] = columnPos - 65; //set column
//	printf("\n %s",squareName);
//	printf("\n In Calc- position X:%d\t position Y: %d\n",position[0],position[1]);
	return position;
}

/* For Simplicity we will assign value to each piece on chess Board
 * Whites:		  	Black:
 * King 	-1	  	King 	-11
 * Queen 	-2	  	Queen 	-12
 * Bishop	-3	  	Bishop	-13
 * Rook		-4 	  	Rook	-14
 * Knight	-5	  	Knight	-15
 * pawn		-6 		pawn	-16
 *
 * Example: Black King will be represented by 11 in our chessBorad
 * Note:The Black pieces can be easily identified if the value of the piece is greater than 10.
 *
 * */
int getPieceValue(char pieceName[]) {
	int pieceValue = 0;
	switch (pieceName[1]) {
	case 'K':
		pieceValue += 1;
		break;
	case 'Q':
		pieceValue += 2;
		break;
	case 'B':
		pieceValue += 3;
		break;
	case 'R':
		pieceValue += 4;
		break;
	case 'N':
		pieceValue += 5;
		break;
	case 'P':
		pieceValue += 6;
		break;
	}
	if (pieceName[0] == 'B') {
		pieceValue += 10; //10 is added to differentiate Black pieces and White pieces
	}
	return pieceValue;
}

/*
 * To identify the piece at the given location
 * Say for example:if given location is B1 and the piece present is Black Queen. Then 12 will be returned by function
 *
 * */

int getPieceValueAtIndex(char squareName[]) {
	int* positionOfPiece;
	positionOfPiece = calculatePosition(squareName);
	return chessBordStatus[*positionOfPiece][*(positionOfPiece + 1)];
}

/* Copies selected part from one array to another
 *
 */

void subString(char denstination[], char source[], int startIndex, int endIndex) {
	int index = 0;
	int destinationIndex = 0;
	while (source[index] != '\0') {
		if (index >= startIndex && index <= endIndex) {
			denstination[destinationIndex] = source[index];
			destinationIndex++;
		}
		index++;

	}
	denstination[destinationIndex] = '\0';
//   printf("\n In SubString Destination:%s \t Origin: %s",denstination,source);
}

/*moveable methods accepts two positions of the chessBoard
 * and it checks whether the position1 can be moved to position2
 * if yes it returns  flag=1
 * else flag=2
 *decidePlayer to tell whom player to play
 *
 */
void moveable() {
	char position1[2], position2[2];

	printf("Enter the two squares on the chess board");
	scanf("%s", position1);
	scanf("%s", position2);
	//printf("\n the position are %s,%s", position1, position2);
	int firstPosition[2];
	int secondPosition[2];
	copyIntArray(firstPosition, calculatePosition(position1), 2);
	copyIntArray(secondPosition, calculatePosition(position2), 2);

	int pieceName = chessBordStatus[firstPosition[0]][firstPosition[1]];
	int flag;
		switch (pieceName % 10) {
		case 1:
			flag = isKingMovable(firstPosition, secondPosition);
			break;
		case 2:
			if (isMovableStraight(firstPosition, secondPosition)
					|| isMovableCross(firstPosition, secondPosition))
				flag = 1;
			else
				flag = 0;
			break;
		case 3:
			flag = isMovableCross(firstPosition, secondPosition);
			break;
		case 4:
			flag = isMovableStraight(firstPosition, secondPosition);
			break;
		case 5:
			flag = isKnightMovable(firstPosition, secondPosition);
			break;
		case 6:
			flag = isPawnMovable(firstPosition, secondPosition);
			break;
		}
		if (flag == 1) {
			printf("\n A can move to B");
			move(firstPosition, secondPosition);
		} else
			printf("\n A cannot be moved to B");
}

/*
 * Copies the content of a pointer Array to another Array
 */
void copyIntArray(int target[], int* source, int size) {
	for (int i = 0; i < size; i++) {
		target[i] = *(source + i);
	}
}

/*
 * p1 and p2 are the position of square 1 and square 2 respectively
 * returns if p1 is movable to p2.
 */

int isKnightMovable(int p1[], int p2[]) {

	int row1 = p1[0];
	int col1 = p1[1];
	int row2 = p2[0];
	int col2 = p2[1];

	if (validateEqualityInPositions(row1 - 1, col1 + 2, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 + 1, col1 + 2, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 - 2, col1 + 1, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 + 2, col1 + 1, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 - 1, col1 - 2, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 + 1, col1 - 2, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 - 2, col1 - 1, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 + 2, col1 - 1, row2, col2))
		return 1;
	else
		return 0;

}

/*
 * Check if movable one step in all directions
 */
int isKingMovable(int p1[], int p2[]) {
	int row1 = p1[0];
	int col1 = p1[1];
	int row2 = p2[0];
	int col2 = p2[1];

	if (validateEqualityInPositions(row1, col1 + 1, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1, col1 - 1, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 + 1, col1, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 - 1, col1, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 + 1, col1 + 1, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 - 1, col1 - 1, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 - 1, col1 + 1, row2, col2))
		return 1;
	else if (validateEqualityInPositions(row1 + 1, col1 - 1, row2, col2))
		return 1;
	else
		return 0;

	return 0;
}

int isMovableStraight(int p1[], int p2[]) {
	int row1 = p1[0];
	int col1 = p1[1];
	int row2 = p2[0];
	int col2 = p2[1];

	if ((row1 != row2) && (col1 != col2)) {
		return 0;
	} else if ((row1 == row2) && (col1 != col2)) {
		if (col2 > col1) {
			for (int i = col1 + 1; i < col2; i++) {
				if (chessBordStatus[row2][i] != 0) {
					return 0;
				}
			}

		} else {
			for (int i = col1 - 1; i > col2; i--) {
				if (chessBordStatus[row2][i] != 0) {
					return 0;
				}
			}
		}
	} else if ((row1 != row2) && (col1 == col2)) {
		if (row2 > row1) {
			for (int i = row1 + 1; i < row2; i++) {
				if (chessBordStatus[i][col2] != 0) {
					return 0;
				}
			}

		} else {
			for (int i = row1 - 1; i > row2; i--) {
				if (chessBordStatus[i][col2] != 0) {
					return 0;
				}
			}
		}
	}
	return 1;
}

/*
 * to move Bishop
 *
 *
 *
 */
int isMovableCross(int p1[], int p2[]) {

	int row1 = p1[0];
	int col1 = p1[1];
	int row2 = p2[0];
	int col2 = p2[1];

	int rowDiff = row1 - row2;
	if (rowDiff < 0)
		rowDiff = -rowDiff;
	int colDiff = col1 - col2;
	if (colDiff < 0)
		colDiff = -colDiff;
	if (rowDiff == colDiff) {
		if (row1 < row2 && col1 < col2) {
			for (int i = 1; i < (rowDiff); i++) {
				if (chessBordStatus[row1 + i][col1 + i] != 0) {
					return 0;
				}
			}
		} else if (row1 < row2 && col1 > col2) {
			for (int i = 1; i < rowDiff; i++) {
				if (chessBordStatus[row1 + i][col1 - i] != 0) {
					return 0;
				}
			}
		} else if (row1 > row2 && col1 > col2) {
			for (int i = 1; i < rowDiff; i++) {
				if (chessBordStatus[row1 - i][col1 - i] != 0) {
					return 0;
				}
			}
		} else if (row1 > row2 && col1 < col2) {
			for (int i = 1; i < rowDiff; i++) {
				if (chessBordStatus[row1 - i][col1 + i] != 0) {
					return 0;
				}
			}
		}
		return 1;
	} else {
		return 0;
	}
}
/*
 *
 * for pawn to move
 *
 */

int isPawnMovable(int p1[], int p2[]) {
	int row1 = p1[0];
	int col1 = p1[1];
	int row2 = p2[0];
	int col2 = p2[1];
	int pieceValue = chessBordStatus[row1][col1];
	if (pieceValue == 16 && row1 == 1 && chessBordStatus[row1 + 1][col1] == 0
			&& chessBordStatus[row1 + 2][col1] == 0) {
		if (validateEqualityInPositions(row1 + 2, col1, row2, col2))
			return 1;
		else if (validateEqualityInPositions(row1 + 1, col1, row2, col2))
			return 1;
		else
			return 0;
	} else if (pieceValue == 6 && row1 == 6
			&& chessBordStatus[row1 - 1][col1] == 0
			&& chessBordStatus[row1 - 2][col1] == 0) {
		if (validateEqualityInPositions(row1 - 2, col1, row2, col2))
			return 1;
		else if (validateEqualityInPositions(row1 - 1, col1, row2, col2))
			return 1;
		else
			return 0;

	} else if (pieceValue == 16) {
		if (validateEqualityInPositions(row1 + 1, col1 - 1, row2, col2))
			return 1;
		else if (validateEqualityInPositions(row1 + 1, col1 + 1, row2, col2))
			return 1;
		else
			return 0;
	} else if (pieceValue == 6) {
		if (validateEqualityInPositions(row1 - 1, col1 - 1, row2, col2))
			return 1;
		else if (validateEqualityInPositions(row1 - 1, col1 + 1, row2, col2))
			return 1;
		else
			return 0;
	}
	return 1;
}

/*
 * validates if the two positions are equal
 */

int validateEqualityInPositions(int row1, int col1, int row2, int col2) {
	if (row1 >= 0 && row1 <= 7 && col1 >= 0 && col1 <= 7) {
		if (row1 == row2 && col1 == col2) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

void move(int p1[], int p2[]) {
	chessBordStatus[p2[0]][p2[1]] = chessBordStatus[p1[0]][p1[1]];
	chessBordStatus[p1[0]][p1[1]] = 0;
}

void ischeck(char a[]) {
	int kingLocation[2];
	if ('b' == a[0]) {
		 printf("\n black turn");
		copyIntArray(kingLocation, calculatePieceLocation(11), 2);
		//	printf("\n black king X position :%d Y position :%d", kingLocation[0],
		//		kingLocation[1]);

	} else {
		printf("\n white turn");
		copyIntArray(kingLocation, calculatePieceLocation(1), 2);
		//printf("\n white king X position :%d Y position :%d", kingLocation[0],
		//			kingLocation[1]);
	}
	if (findCheck(a, kingLocation))
		printf("\n checkmate");
	else
		printf("\n not a checkmate");
}

int findCheck(char a[], int kingLocation[]) {
	int pieceLocation[2] = { 0 };
	int pawnLocation[16] = { 0 };
	int pieceValue = 1;
	int repeat = 0;

	if (a[0] == 'b' || a[0] == 'B') {
		pieceValue = pieceValue + 1;
	} else if (a[0] == 'w' || a[0] == 'W') {
		pieceValue = pieceValue + 10;
	}

	copyIntArray(kingLocation, calculatePieceLocation(pieceValue), 2);
	++pieceValue;
	if (pieceValue % 10 == 2) {
		copyIntArray(pieceLocation, calculatePieceLocation(pieceValue), 2);
		while (repeat != 2) {
			repeat++;
			if (isMovableStraight(kingLocation, pieceLocation)
					|| isMovableCross(kingLocation, pieceLocation)) {
				return 1;
			}
			pieceLocation[0] = pieceLocation[2];
			pieceLocation[1] = pieceLocation[3];
		}
		repeat = 0;
		++pieceValue;
	} else if (pieceValue % 10 == 3) {
		copyIntArray(pieceLocation, calculatePieceLocation(pieceValue), 2);
		while (repeat != 2) {
			repeat++;
			if (isMovableCross(kingLocation, pieceLocation)) {
				return 1;
			}
			pieceLocation[0] = pieceLocation[2];
			pieceLocation[1] = pieceLocation[3];
		}
		repeat = 0;
		++pieceValue;
	}

	else if (pieceValue % 10 == 4) {
		copyIntArray(pieceLocation, calculatePieceLocation(pieceValue), 2);
		while (repeat != 2) {
			repeat++;
			if (isMovableStraight(kingLocation, pieceLocation)) {
				return 1;
			}
			pieceLocation[0] = pieceLocation[2];
			pieceLocation[1] = pieceLocation[3];
		}
		repeat = 0;
		++pieceValue;
	} else if (pieceValue % 10 == 5) {
		copyIntArray(pieceLocation, calculatePieceLocation(pieceValue), 2);
		while (repeat != 2) {
			repeat++;
			if (isKnightMovable(kingLocation, pieceLocation)) {
				return 1;
			}
			pieceLocation[0] = pieceLocation[2];
			pieceLocation[1] = pieceLocation[3];
		}
		repeat = 0;
		++pieceValue;
	} else if (pieceValue % 10 == 6) {
		copyIntArray(pawnLocation, calculatePieceLocation(pieceValue), 16);
		while (repeat != 8) {
			repeat++;
			if (isKnightMovable(kingLocation, pieceLocation)) {
				return 1;
			}
			for (int i = 0; i + 2 < 16; i++)
				pawnLocation[i] = pawnLocation[i + 2];
		}
		repeat = 0;
	}

	return 0;
}

int* calculatePieceLocation(int pieceValue) {
	int i = 0, j = 0;
	static int pieceLocation[4] = { 0 };
	static int pawnLocation[16] = { 0 };
	int pieceCount = 0;
	for (i = 0; i <= 7; i++)
		for (j = 0; j <= 7; j++)
			if (chessBordStatus[i][j] == pieceValue) {
				if (pieceValue < 2) {
					pieceLocation[0] = i;
					pieceLocation[1] = j;
					break;
				} else if (pieceValue > 2 && pieceValue < 6) {
					pieceCount++;
					if (pieceCount == 1) {
						pieceLocation[0] = i;
						pieceLocation[1] = j;
						continue;
					} else if (pieceCount == 2) {
						pieceLocation[2] = i;
						pieceLocation[3] = j;
						break;
					}
				} else {
					pieceCount++;
					if (pieceCount == 1) {
						pawnLocation[0] = i;
						pawnLocation[1] = j;
						continue;
					} else if (pieceCount == 2) {
						pawnLocation[2] = i;
						pawnLocation[3] = j;
						continue;
					} else if (pieceCount == 3) {
						pawnLocation[4] = i;
						pawnLocation[5] = j;
						continue;
					} else if (pieceCount == 4) {
						pawnLocation[6] = i;
						pawnLocation[7] = j;
						continue;
					} else if (pieceCount == 5) {
						pawnLocation[8] = i;
						pawnLocation[9] = j;
						continue;
					} else if (pieceCount == 6) {
						pawnLocation[10] = i;
						pawnLocation[11] = j;
						continue;
					} else if (pieceCount == 7) {
						pawnLocation[12] = i;
						pawnLocation[13] = j;
						continue;
					}

					else if (pieceCount == 8) {
						pawnLocation[14] = i;
						pawnLocation[15] = j;
						break;
					}
				}
			}
	if (pieceValue < 6)
		return pieceLocation;
	else
		return pawnLocation;
}

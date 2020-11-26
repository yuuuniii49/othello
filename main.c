#include <stdio.h> 
#define N 6

char gameboard[N][N];	 

void init_game(void);		// 게임 초기화 함수 선언 
void print_board(void);		// 게임판 출력 함수 선언
int is_gameover(int a);		// 게임의 종료를 판정하는 함수 선언 
int check_board(void);		// 배치 가능한 칸이 있는지 확인하는 함수 선언 
int possible(int x, int y);	// 입력좌표가 적절한지를 판단하는 함수 선언 
int try_flip(int x, int y);	// 뒤집기를 시도하는 함수 선언 
void game_result(void);		// 게임의 결과 확인을 위한 함수 선언 

int main(void)  {
	int user_x, user_y, turn=0, cnt;	// 입력좌표 : user_x, user_y 
	
	init_game(); // 게임 초기화 
	
	while (is_gameover(turn) == 0) {
		print_board();
		if (check_board() == 0) {
			break;
		}
		
		// 어느 돌이 놓을 차례인지를 출력 
		if (turn % 2 == 0) {
			printf("White가 놓을 차례입니다. ");
		}
		else {
			printf("Black이 놓을 차례입니다. ");
		}
		
		printf("놓을 좌표를 입력하세요 : ");
		scanf("%d %d", &user_x, &user_y);
		if (possible(user_x, user_y) == 1) {
			if (turn % 2 == 0) {
				gameboard[user_x][user_y] = 'O';
				cnt = try_flip(user_x, user_y);
				printf("White가 %d개를 뒤집었습니다.\n\n", cnt);
				turn++;	
			}
			else {
				gameboard[user_x][user_y] = 'X';
				cnt = try_flip(user_x, user_y);
				printf("Black이 %d개를 뒤집었습니다.\n\n", cnt);
				turn++;
			}
		}
		else {
			//printf("\n잘못된 입력입니다. 다시 입력하세요.\n\n");
			//continue;
			printf("잘못된 입력으로 패스됩니다.\n");
			turn++;
		}
		
	}
	
	game_result();	 
	
	return 0;
}


// 게임 초기화
void init_game() {
	int i, j;
	printf("======================\n\n");
	printf("  게임을 시작합니다.\n\n");
	printf("======================\n\n");
	for(i=0; i<N; i++) {
		for(j=0; j<N; j++) {
			gameboard[i][j] = ' ';
		}
	}
	gameboard[N/2][N/2] = 'O';
	gameboard[N/2-1][N/2-1] = 'O';
	gameboard[N/2][N/2-1] = 'X';
	gameboard[N/2-1][N/2] = 'X';
	// print_board();
} 

// 보드판 출력 
void print_board(void) {
	int i, j, k=0, s;	// k:상단 숫자출력을 위한 변수 
	int cnt_O=0, cnt_X=0;
	printf(" ");
	for(k=0; k<N; k++) {
		printf(" %d", k);
	}
	printf("\n  ");

	// 게임판의 숫자 아래 가로줄 출력 
	for (s=0; s<2*N; s++) {
		printf("-");
	}
	printf("\n");
	
	for(i=0; i<N; i++) {
		printf("%d|", i);
		// 게임판의 세로줄 출력 
		for(j=0; j<N; j++) {
			printf("%c|", gameboard[i][j]);
		}
		printf("\n  ");
		
		// 게임판의 각 가로줄 출력 
		for (s=0; s<2*N; s++) {
		printf("-");
		}
		printf("\n");
		
	}
	printf("\n");
	
	// 현재 게임판의 상황을 출력 
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			if (gameboard[i][j] == 'O') cnt_O++;
			else if (gameboard[i][j] == 'X') cnt_X++;
		}
	}
	printf("STATUS - White : %d, Black : %d\n\n", cnt_O, cnt_X);
	
}

// 배치 가능한 칸이 있는지 확인
// 가능한 칸이 있다면 1을, 없다면 0을 반환 
int check_board(void)  {
	int i, j, flag=0;
	for(i=0; i<N; i++) {
		for(j=0; j<N; j++) {
			if (gameboard[i][j] == ' ') {
				flag = 1;
				break;
			}
		if (flag == 1) break;
		}
	if (flag == 1) return 1;
	else return 0;
	}
}

int is_gameover(int a) {
	int i, j, blank = 0;
	int cnt_O=0, cnt_X=0;
	int possible=0;
	char stone;
	
	if (a % 2 == 0) stone = 'O';
	else stone = 'X';
	
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			if (gameboard[i][j] == ' ') blank++;
			if (gameboard[i][j] == 'O') cnt_O++;
			if (gameboard[i][j] == 'X') cnt_X++;
			
			// 뒤집을 수 있는 것이 있는지를 판단 
			if ((gameboard[i-2][j-2] == stone) && (gameboard[i-1][j-1] != ' ') && (gameboard[i-1][j-1] != stone)) possible++;
			if ((gameboard[i-2][j] == stone) && (gameboard[i-1][j] != ' ') && (gameboard[i-1][j] != stone)) possible++;
			if ((gameboard[i-2][j+2] == stone) && (gameboard[i-1][j+1] != ' ') && (gameboard[i-1][j+1] != stone)) possible++;
			if ((gameboard[i][j-2] == stone) && (gameboard[i][j-1] != ' ') && (gameboard[i][j-1] != stone)) possible++;
			if ((gameboard[i][j+2] == stone) && (gameboard[i][j+1] != ' ') && (gameboard[i][j+1] != stone)) possible++;
			if ((gameboard[i+2][j-2] == stone) && (gameboard[i+1][j-1] != ' ') && (gameboard[i+1][j-1] != stone)) possible++;
			if ((gameboard[i+2][j] == stone) && (gameboard[i+1][j] != ' ') && (gameboard[i+1][j] != stone)) possible++;
			if ((gameboard[i+2][j+2] == stone) && (gameboard[i+1][j+1] != ' ') && (gameboard[i+1][j+1] != stone)) possible++;
			
		}
	}
	if (blank == 0 || cnt_O == 0 || cnt_X == 0 || possible == 0) return 1;
	else return 0;
}

// 입력좌표가 적절한지를 판단하는 함수
// 적절한 입력이라면 1을, 그렇지 않으면 0을 반환 
int possible(int x, int y) {
	int i, j, flag=0;
	if ((x<0 || x>N) || (y<0 || y>N)) {
		flag = 0;
	}
	else if (gameboard[x][y]==' ') flag = 1;
	else flag = 0;
	
	return flag;
}

// 뒤집기 시도
	
	int try_flip(int x, int y) {
	int cnt=0;
	
	// 왼쪽 위  NW
	if((gameboard[x-2][y-2] == gameboard[x][y]) && (gameboard[x-1][y-1] != ' ') && (gameboard[x-1][y-1] != gameboard[x][y])) {
		if (gameboard[x-1][y-1] == 'O') gameboard[x-1][y-1] = 'X';
		else gameboard[x-1][y-1] = 'O';
		printf("NW:1, ");
		cnt++;
	}
	else printf("NW:0, ");
	
	// 위 N
	if((gameboard[x-2][y] == gameboard[x][y]) && (gameboard[x-1][y] != ' ') && (gameboard[x-1][y] != gameboard[x][y])) {
		if (gameboard[x-1][y] == 'O') gameboard[x-1][y] = 'X';
		else gameboard[x-1][y] = 'O';
		printf("N:1, ");
		cnt++;
	}
	else printf("N:0, ");
	
	// 오른쪽 위 NE
	if((gameboard[x-2][y+2] == gameboard[x][y]) && (gameboard[x-1][y+1] != ' ') && (gameboard[x-1][y+1] != gameboard[x][y])) {
		if (gameboard[x-1][y+1] == 'O') gameboard[x-1][y+1] = 'X';
		else gameboard[x-1][y+1] = 'O';
		printf("NE:1, ");
		cnt++;
	}
	else printf("NE:0, ");
	
	// 왼쪽 W
	if((gameboard[x][y-2] == gameboard[x][y]) && (gameboard[x][y-1] != ' ') && (gameboard[x][y-1] != gameboard[x][y])) {
		if (gameboard[x][y-1] == 'O') gameboard[x][y-1] = 'X';
		else gameboard[x][y-1] = 'O';
		printf("W:1, ");
		cnt++;
	}
	else printf("W:0, ");
	
	// 오른쪽 E 
	if((gameboard[x][y+2] == gameboard[x][y]) && (gameboard[x][y+1] != ' ') && (gameboard[x][y+1] != gameboard[x][y])) {
		if (gameboard[x][y+1] == 'O') gameboard[x][y+1] = 'X';
		else gameboard[x][y+1] = 'O';
		printf("E:1, ");
		cnt++;
	}
	else printf("E:0, ");
	
	// 왼쪽 아래 SW
	if((gameboard[x+2][y-2] == gameboard[x][y]) && (gameboard[x+1][y-1] != ' ') && (gameboard[x+1][y-1] != gameboard[x][y])) {
		if (gameboard[x+1][y-1] == 'O') gameboard[x+1][y-1] = 'X';
		else gameboard[x+1][y-1] = 'O';
		printf("SW:1, ");
		cnt++;
	}
	else printf("SW:0, ");
	
	// 아래 S
	if((gameboard[x+2][y] == gameboard[x][y]) && (gameboard[x+1][y] != ' ') && (gameboard[x+1][y] != gameboard[x][y])) {
		if (gameboard[x+1][y] == 'O') gameboard[x+1][y] = 'X';
		else gameboard[x+1][y] = 'O';
		printf("S:1, ");
		cnt++;
	}	
	else printf("S:0, ");
	
	// 오른쪽 아래 SE
	if((gameboard[x+2][y+2] == gameboard[x][y]) && (gameboard[x+1][y+1] != ' ') && (gameboard[x+1][y+1] != gameboard[x][y])) {
		if (gameboard[x+1][y+1] == 'O') gameboard[x+1][y+1] = 'X';
		else gameboard[x+1][y+1] = 'O';
		printf("SE:1\n");
		cnt++;
	}
	else printf("SE:0\n");
	
	return cnt;
} 

// 게임의 결과 확인을 위한 함수 
void game_result(void) {
	int i, j;
	int cnt_O = 0;
	int cnt_X = 0;
	
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			if (gameboard[i][j] == 'O') cnt_O++;
			else if (gameboard[i][j] == 'X') cnt_X++;
		}
	}
	print_board();
	
	if (cnt_O > cnt_X) printf("The winner is white.\n");
	else if (cnt_O < cnt_X) printf("The winner is black.\n");
	else printf("The Game end in a draw.\n");
}



#include <stdio.h> 
#define N 10
char gameboard[N][N];	 

void init_game(void);		// 게임 초기화 함수 선언 
void print_board(void);		// 게임판 출력 함수 선언
int is_gameover(void);		// 게임의 종료를 판정하는 함수 선언 
int check_board(void);		// 배치 가능한 칸이 있는지 확인하는 함수 선언 
int possible(int x, int y);	// 입력좌표가 적절한지를 판단하는 함수 선언 
int try_flip(int x, int y);	// 뒤집기를 시도하는 함수 선언 
void game_result(void);		// 게임의 결과 확인을 위한 함수 선언 

int main(void)  {
	int user_x, user_y, turn=0, cnt;
	
	init_game(); // 게임 초기화 
	
	while (is_gameover() == 0) {
		print_board();
		if (check_board() == 0) {
			continue;
		}
		printf("놓을 좌표를 입력하세요 : ");
		scanf("%d %d", &user_x, &user_y);
		if (possible(user_x, user_y) == 1) {
			if (turn % 2 == 0) {
				gameboard[user_x][user_y] = 'O';
				cnt = try_flip(user_x, user_y);
				printf("%d개를 뒤집었습니다.\n\n", cnt);
				turn++;	
			}
			else {
				gameboard[user_x][user_y] = 'X';
				cnt = try_flip(user_x, user_y);
				printf("%d개를 뒤집었습니다.\n\n", cnt);
				turn++;
			}
		}
		else {
			printf("\n잘못된 입력입니다. 다시 입력하세요.\n\n");
			continue;
		}
		
	}
	 
	
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
			gameboard[i][j] = '.';
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
	int i, j, k=0;
	printf(" ");
	for(k=0; k<N; k++) {
		printf(" %d", k);
	}
	printf("\n");
	for(i=0; i<N; i++) {
		printf("%d ", i);
		for(j=0; j<N; j++) {
			printf("%c ", gameboard[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// 배치 가능한 칸이 있는지 확인
// 가능한 칸이 있다면 1을, 없다면 0을 반환 
int check_board(void)  {
	int i, j, flag=0;
	for(i=0; i<N; i++) {
		for(j=0; j<N; j++) {
			if (gameboard[i][j] == '.') {
				flag = 1;
				break;
			}
		}
	if (flag == 1) return 1;
	else return 0;
	}
}

int is_gameover(void) {
	return 0;
}

// 입력좌표가 적절한지를 판단하는 함수
// 적절한 입력이라면 1을, 그렇지 않으면 0을 반환 
int possible(int x, int y) {
	int i, j, flag=0;
	if ((x<0 || x>N) || (y<0 || y>N)) {
		flag = 0;
	}
	else if (gameboard[x][y]=='.') flag = 1;
	else flag = 0;
	
	return flag;
}


// 뒤집기 시도
int try_flip(int x, int y) {
	int cnt=0;
	
	// 왼쪽 위  
	if((gameboard[x-2][y-2] == gameboard[x][y]) && (gameboard[x-1][y-1] != '.')) {
		if (gameboard[x-1][y-1] == 'O') gameboard[x-1][y-1] = 'X';
		else gameboard[x-1][y-1] = 'O';
		cnt++;
	}
	
	// 위 
	if((gameboard[x-2][y] == gameboard[x][y]) && (gameboard[x-1][y] != '.')) {
		if (gameboard[x-1][y] == 'O') gameboard[x-1][y] = 'X';
		else gameboard[x-1][y] = 'O';
		cnt++;
	}
	
	// 오른쪽 위 
	if((gameboard[x-2][y+2] == gameboard[x][y]) && (gameboard[x-1][y+1] != '.')) {
		if (gameboard[x-1][y+1] == 'O') gameboard[x-1][y+1] = 'X';
		else gameboard[x-1][y+1] = 'O';
		cnt++;
	}
	
	// 왼쪽 
	if((gameboard[x][y-2] == gameboard[x][y]) && (gameboard[x][y-1] != '.')) {
		if (gameboard[x][y-1] == 'O') gameboard[x][y-1] = 'X';
		else gameboard[x][y-1] = 'O';
		cnt++;
	}
	
	// 오른쪽 
	if((gameboard[x][y+2] == gameboard[x][y]) && (gameboard[x][y+1] != '.')) {
		if (gameboard[x][y+1] == 'O') gameboard[x][y+1] = 'X';
		else gameboard[x][y+1] = 'O';
		cnt++;
	}
	
	// 왼쪽 아래 
	if((gameboard[x+2][y-2] == gameboard[x][y]) && (gameboard[x+1][y-1] != '.')) {
		if (gameboard[x+1][y-1] == 'O') gameboard[x+1][y-1] = 'X';
		else gameboard[x+1][y-1] = 'O';
		cnt++;
	}
	
	// 아래 
	if((gameboard[x+2][y] == gameboard[x][y]) && (gameboard[x+1][y] != '.')) {
		if (gameboard[x+1][y] == 'O') gameboard[x+1][y] = 'X';
		else gameboard[x+1][y] = 'O';
		cnt++;
	}	
	
	// 오른쪽  아래 
	if((gameboard[x+2][y+2] == gameboard[x][y]) && (gameboard[x+1][y+1] != '.')) {
		if (gameboard[x+1][y+1] == 'O') gameboard[x+1][y+1] = 'X';
		else gameboard[x+1][y+1] = 'O';
		cnt++;
	}
	
	
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
	
	if (cnt_O > cnt_X) printf("The winner is O.\n");
	else if (cnt_O < cnt_X) printf("The winner is X.\n");
	else printf("The Game end in a draw.\n");
}



#include <stdio.h> 
#define N 10
char gameboard[N][N];	 

void init_game(void);		// ���� �ʱ�ȭ �Լ� ���� 
void print_board(void);		// ������ ��� �Լ� ����
int is_gameover(void);		// ������ ���Ḧ �����ϴ� �Լ� ���� 
int check_board(void);		// ��ġ ������ ĭ�� �ִ��� Ȯ���ϴ� �Լ� ���� 
int possible(int x, int y);	// �Է���ǥ�� ���������� �Ǵ��ϴ� �Լ� ���� 
int try_flip(int x, int y);	// �����⸦ �õ��ϴ� �Լ� ���� 
void game_result(void);		// ������ ��� Ȯ���� ���� �Լ� ���� 

int main(void)  {
	int user_x, user_y, turn=0, cnt;
	
	init_game(); // ���� �ʱ�ȭ 
	
	while (is_gameover() == 0) {
		print_board();
		if (check_board() == 0) {
			continue;
		}
		printf("���� ��ǥ�� �Է��ϼ��� : ");
		scanf("%d %d", &user_x, &user_y);
		if (possible(user_x, user_y) == 1) {
			if (turn % 2 == 0) {
				gameboard[user_x][user_y] = 'O';
				cnt = try_flip(user_x, user_y);
				printf("%d���� ���������ϴ�.\n\n", cnt);
				turn++;	
			}
			else {
				gameboard[user_x][user_y] = 'X';
				cnt = try_flip(user_x, user_y);
				printf("%d���� ���������ϴ�.\n\n", cnt);
				turn++;
			}
		}
		else {
			printf("\n�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n\n");
			continue;
		}
		
	}
	 
	
	return 0;
}


// ���� �ʱ�ȭ
void init_game() {
	int i, j;
	printf("======================\n\n");
	printf("  ������ �����մϴ�.\n\n");
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

// ������ ��� 
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

// ��ġ ������ ĭ�� �ִ��� Ȯ��
// ������ ĭ�� �ִٸ� 1��, ���ٸ� 0�� ��ȯ 
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

// �Է���ǥ�� ���������� �Ǵ��ϴ� �Լ�
// ������ �Է��̶�� 1��, �׷��� ������ 0�� ��ȯ 
int possible(int x, int y) {
	int i, j, flag=0;
	if ((x<0 || x>N) || (y<0 || y>N)) {
		flag = 0;
	}
	else if (gameboard[x][y]=='.') flag = 1;
	else flag = 0;
	
	return flag;
}


// ������ �õ�
int try_flip(int x, int y) {
	int cnt=0;
	
	// ���� ��  
	if((gameboard[x-2][y-2] == gameboard[x][y]) && (gameboard[x-1][y-1] != '.')) {
		if (gameboard[x-1][y-1] == 'O') gameboard[x-1][y-1] = 'X';
		else gameboard[x-1][y-1] = 'O';
		cnt++;
	}
	
	// �� 
	if((gameboard[x-2][y] == gameboard[x][y]) && (gameboard[x-1][y] != '.')) {
		if (gameboard[x-1][y] == 'O') gameboard[x-1][y] = 'X';
		else gameboard[x-1][y] = 'O';
		cnt++;
	}
	
	// ������ �� 
	if((gameboard[x-2][y+2] == gameboard[x][y]) && (gameboard[x-1][y+1] != '.')) {
		if (gameboard[x-1][y+1] == 'O') gameboard[x-1][y+1] = 'X';
		else gameboard[x-1][y+1] = 'O';
		cnt++;
	}
	
	// ���� 
	if((gameboard[x][y-2] == gameboard[x][y]) && (gameboard[x][y-1] != '.')) {
		if (gameboard[x][y-1] == 'O') gameboard[x][y-1] = 'X';
		else gameboard[x][y-1] = 'O';
		cnt++;
	}
	
	// ������ 
	if((gameboard[x][y+2] == gameboard[x][y]) && (gameboard[x][y+1] != '.')) {
		if (gameboard[x][y+1] == 'O') gameboard[x][y+1] = 'X';
		else gameboard[x][y+1] = 'O';
		cnt++;
	}
	
	// ���� �Ʒ� 
	if((gameboard[x+2][y-2] == gameboard[x][y]) && (gameboard[x+1][y-1] != '.')) {
		if (gameboard[x+1][y-1] == 'O') gameboard[x+1][y-1] = 'X';
		else gameboard[x+1][y-1] = 'O';
		cnt++;
	}
	
	// �Ʒ� 
	if((gameboard[x+2][y] == gameboard[x][y]) && (gameboard[x+1][y] != '.')) {
		if (gameboard[x+1][y] == 'O') gameboard[x+1][y] = 'X';
		else gameboard[x+1][y] = 'O';
		cnt++;
	}	
	
	// ������  �Ʒ� 
	if((gameboard[x+2][y+2] == gameboard[x][y]) && (gameboard[x+1][y+1] != '.')) {
		if (gameboard[x+1][y+1] == 'O') gameboard[x+1][y+1] = 'X';
		else gameboard[x+1][y+1] = 'O';
		cnt++;
	}
	
	
	return cnt;
} 
// ������ ��� Ȯ���� ���� �Լ� 
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



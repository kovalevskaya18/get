#include <iostream>
#include <cstdlib>
#include <clocale>

char matrix[3][3]; /* Игральная доска */

char check(void);
void init_matrix(void);
void get_player_move(void);
void get_computer_move(void);
void disp_matrix(void);
int* predict_winner(void);
bool check_corners(void);
int* check_not_corners(void);

int main(void)
{
	char done;
	setlocale(LC_ALL, "ru");
	std::cout <<"Это - игра в крестики-нолики.\n";
	std::cout <<"Вы (X) будете играть с компьютером (O).\n";
	done = '';
	init_matrix();
	int k = 0;
	do {
		k++;
		disp_matrix();
		get_player_move();
		done = check(); /* Есть ли победитель? */
		if (done != '') break; /* Победитель определен!*/;
		int p1 = predict_winner()[0];/*Находим "опасный" ход соперника и опережаем его*/
		int p2 = predict_winner()[1];
		int c1 = check_not_corners()[0];/*Смотрим, заняты ли неугловые клетки на 2-ом ходе, для нужной стратегии*/
		int c2 = check_not_corners()[1];
		bool f = check_corners();/*Смотрим, выбрал ли соперник стратегию игры через угол*/
		if (k == 1 && f) matrix[1][1] = 'O';
		elseif (k == 2 && f && p1 == -1) matrix[c1][c2] = 'O';
		elseif (p1 != -1) matrix[p1][p2] = 'O';
		else get_computer_move();
		done = check(); /* Есть ли победитель? */
	} while (done == '');
	if (done == 'X') std::cout <<"Вы победили!\n";
	else std::cout <<"Компьютер выиграл!!!!\n";
	disp_matrix(); /* Финальное положение */
	return 0;
}
/* Инициализация матрицы. */
void init_matrix(void)
{
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			matrix[i][j] = '';
}
/* Ход игрока. */
void get_player_move(void)
{
	int x, y;
	std::cout <<"Введите координаты X (1,2,3), Y (1,2,3): ";
	std::cin >> x >> y;
	x--; y--;
	if (matrix[x][y] != '') {
		std::cout <<"Неверный ход, попытайтесь еще.\n";
		get_player_move();
	}
	else matrix[x][y] = 'X';
}
/* Ход компьютера. */
void get_computer_move(void)
{
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			if (matrix[i][j] == '') break;
		if (matrix[i][j] == '') break;
	}
	if (i * j == 9) {
		std::cout <<"Ничья\n";
		exit(0);
	}
	else
		matrix[i][j] = 'O';
}
/* Вывести матрицу на экран. */
void disp_matrix(void)
{
	int t;
	for (t = 0; t < 3; t++) {
		std::cout <<"| "<< matrix[t][0]
			<<" | "<< matrix[t][1] <<" | "
			<< matrix[t][2] <<" |";
		if (t != 2) std::cout <<"\n|---|---|---|\n";
	}
	std::cout <<'\n';
}
/* Проверить, есть ли победитель. */
char check(void)
{
	int i;
	for (i = 0; i < 3; i++) /* Проверка строк */
		if (matrix[i][0] == matrix[i][1] && matrix[i][0] == matrix[i][2])
			return matrix[i][0];
	for (i = 0; i < 3; i++) /* Проверка столбцов */
		if (matrix[0][i] == matrix[1][i] && matrix[0][i] == matrix[2][i])
			return matrix[0][i];
	/* Проверка диагоналей */
	if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2])
		return matrix[0][0];
	if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0])
		return matrix[0][2];
	return'';
}
/*Проверить, является ли игрок потенциальным победителем*/
int* predict_winner(void)
{
	int pos[2];
	bool f = false;
	for (int i = 0; i < 3; i++)/*Проверка строк*/
	{
		int s1 = 0, s2 = 0;
		for (int j = 0; j < 3; j++)
		{
			if (matrix[i][j] == 'X') s1++;
			elseif (matrix[i][j] == '')
			{
				s2++;
				pos[0] = i;
				pos[1] = j;
			}
		}
		if (s1 == 2 && s2 == 1)
		{
			f = true;
			return pos;
		}
	}
	for (int i = 0; i < 3; i++)/*Проверка столбцов*/
	{
		int s1 = 0, s2 = 0;
		for (int j = 0; j < 3; j++)
		{
			if (matrix[j][i] == 'X') s1++;
			elseif (matrix[j][i] == '')
			{
				s2++;
				pos[0] = j;
				pos[1] = i;
			}
		}
		if (s1 == 2 && s2 == 1)
		{
			f = true;
			return pos;
		}
	}
	int s1 = 0, s2 = 0;
	for (int i = 0; i < 3; i++)/*Проверка левой диагонали*/
	{
		if (matrix[i][i] == 'X') s1++;
		elseif (matrix[i][i] == '')
		{
			s2++;
			pos[0] = i;
			pos[1] = i;
		}
		if (s1 == 2 && s2 == 1)
		{
			f = true;
			return pos;
		}
	}
	int k = -1;
	s1 = 0, s2 = 0;
	for (int i = 2; i >= 0; i--)/*Проверка правой диагонали*/
	{
		k++;
		if (matrix[i][k] == 'X') s1++;
		elseif (matrix[i][k] == '')
		{
			s2++;
			pos[0] = i;
			pos[1] = k;
		}
		if (s1 == 2 && s2 == 1)
		{
			f = true;
			return pos;
		}
	}
	if (f) return pos;
	else
	{
		pos[0] = -1;
		pos[1] = -1;
		return pos;
	}
}
/*Проверим, занял ли игрок угловые клетки*/
bool check_corners(void)
{
	bool f = false;
	if (matrix[0][0] == 'X') returntrue;
	elseif (matrix[0][2] == 'X') returntrue;
	elseif (matrix[2][0] == 'X') returntrue;
	elseif (matrix[2][2] == 'X') returntrue;
	return f;
}
/*Проверим какие неугловые клетки свободны*/
int* check_not_corners(void)
{
	int pos[2] = { -1, -1 };
	if (matrix[0][1] == '')
	{
		pos[0] = 0;
		pos[1] = 1;
	}
	elseif (matrix[1][0] == '')
	{
		pos[0] = 1;
		pos[1] = 0;
	}
	elseif (matrix[1][2] == '')
	{
		pos[0] = 1;
		pos[1] = 2;
	}
	elseif (matrix[2][1] == '')
	{
		pos[0] = 2;
		pos[1] = 1;
	}
	return pos;
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
int main()
{
	int vals[4][3] = {
		{ 1, 9, -2 },
		{ 0, 2, 2 },
		{ 9, 1, 2 },
		{ 2, 0, -2 },
	};

	for (int i = 0; i < 4; i++) {
		int res = vals[i][1] - vals[i][0];
		if (abs(res) > 5)
			res = -(10 - abs(res)) * (res / abs(res));
		if (res != vals[i][2])
			printf("[%d] FAIL ==> %d vs %d\n", i, res, vals[i][2]);
	}
	return (0);

}
/**/
int main()
{
	int X = 5, Y = 7, D = 3;

	for (unsigned int i = 0; i < 9; i++) {
		int x, y;
		int x_off = 0;
		int y_off = 0;

		if (i != 0) {
			y_off = (int)(i / sqrt(i));
			x_off = -y_off + i - y_off * y_off;
		}
		if (D > 1) {
			x_off = -x_off;
			y_off = -y_off;
		}
		if (D % 2 == 0) {
			x = X + x_off;
			y = Y + y_off;
		} else {
			x = X + y_off;
			y = Y - x_off;
		}
		printf("%d: %d %d\n", i, x, y);
	}
}

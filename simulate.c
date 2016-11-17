/*

	DecaySimulator: runs Monte Carlo simulations of radioactive decay chains
 	Copyright (C) 2016, K. Sannidhya Shukla

 	This file is part of DecaySimulator.

    DecaySimulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DecaySimulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with DecaySimulator.  If not, see <http://www.gnu.org/licenses/>.
    
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define DEFAULT_ITER 100000
#define DEFAULT_MOL  100000

unsigned rand2(unsigned int);

int main(int argc, char **argv)
{
	unsigned i, j, cell, k1, k2, n_mol = DEFAULT_MOL, n_iter = DEFAULT_ITER;
	bool *state_A, *state_B, *state_C;
	unsigned (*plot)[3], n_A, n_B, n_C;
	
	if (argc < 3) {
		fprintf(stderr, "usage: run k1 k2 [n_iter] [n_mol]\n");
		return 1;
	}
	k1 = atoi(argv[1]);
	k2 = atoi(argv[2]);
	if (argc > 3) {
		n_iter = atoi(argv[3]);
	}
	if (argc > 4) {
		n_mol = atoi(argv[4]);
	}

	n_A = n_mol;
	n_B = n_C = 0;
	
	state_A = malloc((sizeof(bool))*n_mol);
	state_B = malloc((sizeof(bool))*n_mol);
	state_C = malloc((sizeof(bool))*n_mol);
	for (i = 0; i < n_mol; i++) {
		state_A[i] = true;
		state_B[i] = state_C[i] = false;
	}

	plot = malloc((sizeof(int)) * (n_iter) * 3);
	plot[0][0] = n_A;
	plot[0][1] = n_B;
	plot[0][2] = n_C;

	for (i = 0; i < n_iter; i++) {
		for (j = 0; j < k1; j++) {
			cell = rand2(n_mol);
			if (state_A[cell]) {
				state_A[cell] = false;
				state_B[cell] = true;
				n_A--;
				n_B++;
			}
		}
		for (j = 0; j < k2; j++) {
			cell = rand2(n_mol);
			if (state_B[cell]) {
				state_B[cell] = false;
				state_C[cell] = true;
				n_B--;
				n_C++;
			}
		}
		plot[i+1][0] = n_A;
		plot[i+1][1] = n_B;
		plot[i+1][2] = n_C;
	}

	printf("# t\tn_A\tn_B\tn_C\n");
	for (i = 0; i < n_iter + 1; i++) {
		printf("%u\t%u\t%u\t%u\n", i, plot[i][0], plot[i][1], plot[i][2]);
	}

	return 0;
}

unsigned rand2(unsigned n)
{
	unsigned r;
	while ((r = (rand() / (RAND_MAX / n))) >= n)
		;
	return r;
}

#
# 	DecaySimulator: runs Monte Carlo simulations of radioactive decay chains
#	Copyright (C) 2016, K. Sannidhya Shukla
#
#	This file is part of DecaySimulator.
#
#	DecaySimulator is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   DecaySimulator is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with DecaySimulator.  If not, see <http://www.gnu.org/licenses/>.
#

printf "DecaySimulator  Copyright (C) 2016  K. Sannidhy Shukla\n"
printf "This program comes with ABSOLUTELY NO WARRANTY.\n"
printf "This is free software, and you are welcome to redistribute it under certain conditions; see <https://www.gnu.org/licenses/gpl.html> for details.\n\n"

echo -n "Enter the decay constant for A: "
read K1
if [[ -z "${K1// }" ]]; then
	echo "error: invalid value"
	exit
fi
echo -n "Enter the decay constant for B: "
read K2
if [[ -z "${K2// }" ]]; then
	echo "error: invalid value"
	exit
fi
echo -n "Enter the number of iterations to run (default 100000): "
read N_ITER
echo -n "Enter the initial number of molecules of A (default 100000): "
read N_MOL
echo -n "Enter the name of the data file: (default plot.dat)"
read PLOTFILE
echo -n "Enter the name of output file (default MC_Plot.png): "
read OUTFILE

if [[ -z "${N_ITER// }" ]]; then
	N_ITER=100000
fi
if [[ -z "${N_MOL// }" ]]; then
	N_MOL=100000
fi
if [[ -z "${PLOTFILE// }" ]]; then
	PLOTFILE="plot.dat"
fi
if [[ -z "${OUTFILE// }" ]]; then
	OUTFILE="MC_Plot.png"
fi

cc simulate.c -o run
./run "$K1" "$K2" "$N_ITER" "$N_MOL" > "$PLOTFILE"

echo "set term png" > gpscript.p
echo "set xlabel \"No. of iterations\"" >> gpscript.p
echo "set ylabel \"No. of molecules\"" >> gpscript.p
echo "set output \"$OUTFILE\"" >> gpscript.p
echo "set title \"Chain Reaction A -> B -> C (k1=$K1, k2=$K2)\"" >> gpscript.p
echo "set xrange [-10:$N_ITER]" >> gpscript.p
echo "set yrange [-10:$N_MOL]" >> gpscript.p
echo "plot \
\"plot.dat\" u 1:2 w lines t \"n(A)\",\
\"plot.dat\" u 1:3 w lines t \"n(B)\",\
\"plot.dat\" u 1:4 w lines t \"n(C)\"" >> gpscript.p

gnuplot gpscript.p

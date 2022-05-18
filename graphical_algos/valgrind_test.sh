#valgrind --leak-check=full --show-reachable=yes ./graphicengine -l1 \
#>& ./valgrind_output.txt

#valgrind --leak-check=full --show-reachable=yes ./graphicengine -l2 \
#-f lab2in.ps -w 200 -h 200 -o lab2out.xpm \
#>& ./valgrind_output.txt

#valgrind --leak-check=full --show-reachable=yes ./graphicengine -l3 \
#-f lab3in.ps -w 200 -h 200 -wl 50 -wr 150 -wb 150 -wt 50 -o lab3out.xpm \
#>& ./valgrind_output.txt

#valgrind --leak-check=full --show-reachable=yes ./graphicengine -l4 \
#-f lab4in.ps -w 200 -h 200 -o lab4out.xpm -t ./transforms_lab4.tsf \
#>& ./valgrind_output.txt

#valgrind --leak-check=full --show-reachable=yes ./graphicengine -l5 -p1 \
#-f lab5in.pol -w 200 -h 200 -wl 50 -wt 50 -wr 150 -wb 150 -o lab5out.xpm \
#>& ./valgrind_output.txt

valgrind --leak-check=full --show-reachable=yes ./graphicengine -l5 -p2 \
-f lab5in.pol -w 200 -h 200 -wl 50 -wt 50 -wr 150 -wb 150 -o lab5out.xpm \
>& ./valgrind_output.txt

#valgrind --leak-check=full --show-reachable=yes ./graphicengine -l6 -p2 \
#-f lab6in.pol -w 200 -h 200 -wl 50 -wt 50 -wr 150 -wb 150 -o lab6out.xpm \
#>& ./valgrind_output.txt

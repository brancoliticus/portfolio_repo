makefile:
all : banc_test

clean:
	-rm *.o *.vcd

show : output.vcd
	gtkwave $< signals &>/dev/null

output.vcd : banc_test
	ghdl -r banc_test --vcd=$@ --stop-time=300ns

banc_test : banc_test.o
	ghdl -e $@

banc_test.o : banc_test.vhdl bistabil_d.o inmultitor.o mux2x1.o mux2x4.o poarta_and.o poarta_xor.o reg_inc_par.o reg_inc_par_depl_dr.o sum.o
	ghdl -a $<

bistabil_d.o : bistabil_d.vhdl
	ghdl -a $<

inmultitor.o : inmultitor.vhdl
	ghdl -a $<

mux2x1.o : mux2x1.vhdl
	ghdl -a $<

mux2x4.o : mux2x4.vhdl
	ghdl -a $<

poarta_and.o : poarta_and.vhdl
	ghdl -a $<

poarta_xor.o : poarta_xor.vhdl
	ghdl -a $<

reg_inc_par.o : reg_inc_par.vhdl
	ghdl -a $<

reg_inc_par_depl_dr.o : reg_inc_par_depl_dr.vhdl
	ghdl -a $<

sum.o : sum.vhdl
	ghdl -a $<
